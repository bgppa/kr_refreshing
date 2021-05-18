/* Exercise 8.2-3-4 Re-writing part of stdio.h to interface unix files,
 * and doing that using bit-fields structures rather than enum flags */
#define my_NULL 0
#define my_EOF (-1)
#define my_BUFSIZE 10
#define my_OPEN_MAX 20

/* Struct for the file flags */
struct f_flags {
    unsigned int READ    : 1;
    unsigned int WRITE   : 1;
    unsigned int UNBUF   : 1;
    unsigned int FEOF    : 1;
    unsigned int ERR     : 1;
};

/* Defining the FILE structure: buffers and file descriptors */
typedef struct my_iobuf {
    int cnt;                /* #remaining chars to process, in the buffer*/
                            /* The interpretation strongly depends on the
                             * mode in which the file is elaborated.
                             * WRITE: #empy spaces available in the buffer;
                             * READ:  #chars stored in the buffer, to read */
    char *ptr;              /* points to the next buffer char to process */
    char *base;             /* buffer starting address */
    struct f_flags flags;   /* flags */
    int fd;                 /* UNIX file descriptior */
} my_FILE;

/* Array containing all the files that will be processed */
extern my_FILE my_iob[my_OPEN_MAX];

/* 0, 1, 2 are the in/our/err descriptors under unix */
#define my_stdin    (&my_iob[0])
#define my_stdout   (&my_iob[1])
#define my_stderr   (&my_iob[2])

/* Other functions to implement: they constitute the exercises #2, 3, 4 */
int my_fillbuf (my_FILE *);
int my_flushbuf (int x, my_FILE *);

my_FILE *my_fopen (char*, char*);
int my_fclose (my_FILE * fp);
int my_fflush (my_FILE * fp);
int my_fseek(my_FILE *, long, int);

/* Remaining part are macros; always a good idea ext. ( ) to prioritize */
#define my_feof(p)      ((((p)->flags)->FEOF) ? 1 : 0)
#define my_ferror(p)    ((((p)->flags)->ERR) ? 1 : 0)
#define my_fileno(p)    ((p)->fd)           

/* getc and putc */
/* if the buffer is still available, return a character from it.
 * otherwise refill the buffer, and return the first char in this new one
 * (that's the job of my_fillbuf(p)
 * Note the use of cnt as counter for the remaining characters to extract
 * from the buffer */
#define my_getc(p)     (--(p)->cnt >= 0 ? \
                        (unsigned char) *(p)->ptr++ : my_fillbuf(p))

#define my_getchar()   my_getc(my_stdin)

/* Similar implementation for putchar. Note the use of the counter cnt
 * as "number of spaces still empty in the buffer", instead of the
 * interpretation given when using getc */
#define my_putc(x, p)  (--(p)->cnt >= 0 ? \
                        *(p)->ptr++ = (x) : my_flushbuf((x), p))

#define my_putchar(x) my_putc((x), my_stdout)
