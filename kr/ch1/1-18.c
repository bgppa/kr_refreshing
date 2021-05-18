/* Exercise 1.18
 * Write a program to remove trailing blanks and tabs from each line
 * of input, and to delete entirely blank lines */
#include <stdio.h>

int main (void) {

    int c = 0;
    int prev_was_newline = 0;

    while ((c = getchar()) != EOF) {
        if (c == '\n') {
            if (!prev_was_newline) {
                    prev_was_newline = 1;
                    putchar(c);
            }
        } else {
            prev_was_newline = 0;
            if (c != ' ' && c != '\t') {
                putchar(c);
            }
        }
    }

    return 0;
}
