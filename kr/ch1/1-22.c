/* Exercise 1.22.
 * Write a program to fold long inputs lines into two or more shorter lines
 * after the last non-blank character that occurs before the n-th column of
 * input. Make sure your program does something intelligent with very long lines
 * and if there are no blanks or tabs before the specified column */
#include <stdio.h>
#define MAXCOL 10

int main (void) {
    int c = 0;
    int i = 0;
    int cblanks = 0;
    
    while ((c = getchar()) != EOF) {
        if (i == MAXCOL || c == '\n') {
            putchar('\n');
            i = 0;
            cblanks = 0;
        } else {
            /* if blank space, wait before print: maybe do just newline */
            if (c == ' ') {
                ++cblanks;
                ++i;
            } else {
                /* if blank spaces pending, and ok in column, print all of them */
                while (cblanks > 0) {
                    putchar(' ');
                    cblanks--;
                }
                putchar(c);
                ++i;
            }
        }
    }

    return 0;
}
