/* Exercise 1: implementing cat by onlu using UNIX API, no stdio */
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>


/* Instead of FILE *, work with file descriptors; Unix api */
int filecopy (int fdin, int fdout)
{
    char c;
    /* Write a character as long we read one valid character */
    /* REMARK: c can be char. Indeed, if EOF is read, read() returns 0.
     * there is no issue like with the getchar() function */
    while (read(fdin, &c, 1) == 1) {
        write(fdout, &c, 1);
    }

    return 1;
}

int main (int argc, char *argv[]) {
    /* Key point: use of file descriptors (ints) instead of file pointers.
     * Memento: 0, 1, 2 are usually used for stdin, stdout, stderr;
     * (to check: still in 2021? Current standard?) */
    int fd;
    int i = 0;
    if (argc == 1) {
        /* In this case, copy standard input to standard output */
        filecopy (0, 1);
    } else {
        while (++i < argc) {
            /* Open a file with read-only status. No special argument needed */
            fd = open(argv[i], O_RDONLY, 0);
            if (fd > 0) {
                filecopy(fd, 1);
            }
            close(fd);
        }
    }

    return 0;
}
