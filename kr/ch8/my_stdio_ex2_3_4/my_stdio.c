#include "my_stdio.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#define OKPERMS 0666

/* The first three files are stdin, stdout, stderr. The others are default-
 * initialized to zero/nulls, and are available to the user */
my_FILE my_iob[my_OPEN_MAX] = {
    {0, 0, 0, {1, 0, 1}, 0},    /* stdin: descriptor 0, read flag to 1 */
    {0, 0, 0, {0, 1, 1}, 1},    /* stdout: descriptor 1, write to 1, unbuf */
    {0, 0, 0, {0, 1}, 2}        /* same with stderr */
};
    
/* Here we have to implement the following functions: */

/* fillbuf: allocate the buffer for a file, return first character there */
int my_fillbuf (my_FILE *fp)
{
    /* value of the first character in the buffer; will be returned */
    int first_character;

    /* Check that the file can be open in read mode */
    if (fp->flags.READ != 1 || fp->flags.FEOF == 1) {
        return my_EOF;
    }

    /* maximum amount of characters than can be read from file */
    int actual_bufsize = (fp->flags.UNBUF) ? 1 : my_BUFSIZE;

    /* if the buffer is unallocated, create one */
    if (fp->base == my_NULL) {
        if((fp->base = malloc(sizeof(char)*actual_bufsize)) == NULL) {
            return my_EOF;
        }
    }

    /* anyway, reset the counter and the buffer at the beginning */
    fp->ptr = fp->base;
    /* read a max of actual_bufsize chars, store into base */
    fp->cnt = read(fp->fd, fp->base, actual_bufsize);
    /* recall that read() gives zero when EOF, -1 when error */
    if (fp->cnt == 0) {
        fp->flags.FEOF = 1;
        return my_EOF;
    } else if (fp->cnt == -1) {
            fp->flags.ERR = 1;
            return my_EOF;
    }

    first_character = *fp->ptr;
    fp->ptr++;
    fp->cnt--;
    return first_character;
}


/* Move buf into file; if x non-zero, copy as first char in the new buffer */
int my_flushbuf (int x, my_FILE *fp) {

    /* Check that we can write on the target file */
    if (fp->flags.WRITE == 0){
        return -1;
    }

    int actual_bufsize = fp->flags.UNBUF? 1 : my_BUFSIZE;

    /* In case, allocate the buffer (e.g. file first time opened) */
    if (fp->base == my_NULL) {
        /* Here because first time allocate the buffer. Just set variables  */
        if ((fp->base = malloc(sizeof(char) * actual_bufsize)) == NULL) {
            return -1;
        }
    } else {
        /* The buffer already exist. May or may be not be full
         * (e.g. a call from fflush, forcing the flush.
         * Therefore, copy #bytes as "buffer - used" */
        write(fp->fd, fp->base, actual_bufsize - fp->cnt);
    }

    fp->cnt = actual_bufsize;
    fp->ptr = fp->base;
    /* If inserted a non-empty character, put it into the first buf space
     * an empty char can be used to force a flush with no writing  */
    if (x != 0) {
        fp->cnt--;
        *fp->ptr++ = (char) x;
    }
    return 1;
}


/* Re-writing fopen, which actually just initialize the pointer.
 * DOE NOT take care about the buffer: it's done by fillbuf */ 
my_FILE *my_fopen (char *fname, char *mode)
{
    int i = 0;
    int fd;
    my_FILE * fp;
    int fmode;
    int to_append = 0;

    printf("Checking file modes...\n");
    /* Check that the opening mode is legal */
    if (*mode == 'w') {
        fmode = O_WRONLY;
    } else if (*mode == 'r') {
        fmode = O_RDONLY;
    } else if (*mode == 'a') {
        fmode = O_WRONLY;
        to_append = 1;
    } else {
        return my_NULL;
    }
   
    printf("Checking if space is available...\n"); 
    /* Check if the system still has free slots for managing files */
    /* (i = 0, 1, 2 are already reserved for stdin, stdout, stderr) */
    for (i = 3; i < my_OPEN_MAX; ++i) {
        if(my_iob[i].flags.READ == 0 && my_iob[i].flags.WRITE == 0) {
            fp = my_iob + i;
            break;
        }
    }
    if (i >= my_OPEN_MAX) {
        printf("system filex exceeded (%d)\n", i);
        return my_NULL;
    }

    /* Else, we successfully found an available slot. */
    printf("Opening according to the various cases...\n");
    /* If just write, create the file. */
    if (fmode == O_WRONLY) {
        /* if not to append: just create a new file */
        if (to_append == 0) {
            if ((fd = creat(fname, OKPERMS)) == -1 ) {
                return my_NULL;
            }
        } else { /* write, append */
            if ((fd = open(fname, O_WRONLY, 0)) == -1) {
                /* If failed to open, create a new one */
                    if ((fd = creat(fname, OKPERMS)) == -1) {
                        return my_NULL;
                    }
            } else {
                /* Correctly opened, go to the end */
                if (lseek(fd, 0L, 2) < 0) {
                    return my_NULL;
                }
            }
        }
        fp->flags.WRITE = 1;
    }   /* end of the write modus */ 
        else if (fmode == O_RDONLY) {
        /* reading a file: must successfully open in  */
        if ((fd = open(fname, O_RDONLY, 0)) == -1 ){
                return my_NULL;
        }
        fp->flags.READ = 1;
    }
  
    printf("Final initialization\n"); 
    fp->cnt = 0;
    fp->ptr = NULL;
    fp->base = NULL;
    fp->fd = fd;
    printf("Exiting from my_fopen...\n");
    return fp;
} 
    

int my_fclose (my_FILE * fp)
{
    /* basically free the buffer and flush the buffer if write */
    if(fp->flags.WRITE == 1) {
        my_fflush(fp);
    }

    if (fp->base != NULL) {
        free(fp->base);
    }

    fp->ptr = NULL;
    fp->flags.READ = 0;
    fp->flags.WRITE = 0;
    close(fp->fd);
    
    return 1;
}

int my_fflush (my_FILE * fp)
{
    /* Assume the file is open and is WRITE */
    /* Just write eof and empty the buffer */
    return my_flushbuf (my_EOF, fp);
}    
    
    
int my_fseek(my_FILE *fp, long offset, int origin)
{
    /* If writing pendind buffering, flush */
    if (fp->flags.WRITE == 1) {
        printf("file in scrittura\n");
        /* Note the use of 0, so that the buffer is flushed but its first
         * element is not initialized */
        my_flushbuf(0, fp);
    }
    /* Use the UNIX interface to go to the desired file offset */
    if (lseek(fp->fd, offset, origin)) {
        return 1;
    } else {
        return -1;
    }
}
