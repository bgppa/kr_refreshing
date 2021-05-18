/* Exercise 1.23:
 * write a program to remove all comments from a C program.
 * Don't forget to handle quoted strings and character constants properly.
 * C comments don't nest */

/* COMMENT: well...I actually forgot to handle quotes, " and '.
 * ...but I did well in the next exercise, 1.24, which authomatically
 * improved what done here */
#include <stdio.h>

int main (void) {
    int was_slsh = 0;
    int was_astk = 0;
    int in_comment = 0;
    int c = 0;

    while ((c = getchar()) != EOF) {
        if (in_comment) {
            /* if the previous char was an asterisk: */
            if (was_astk) {
                if (c == '/') {
                    /* Exit from the comment, reset the flags */
                    in_comment = 0;
                    was_astk = 0;
                    was_slsh = 0;
                }
            }
            /* if not an exit combination, store only the star case */
            if (c == '*') {
                was_astk = 1;
            }
        } else {
            /* If NOT in a comment */
            if (c != '*' && c != '/') {
                /* first, if pending special chars, print them */
                if (was_astk) {
                    putchar('*');
                    was_astk = 0;
                }
                if (was_slsh) {
                    putchar('/');
                    was_slsh = 0;
                }
                /* then print c, since it's not a special char */
                putchar(c);
            }
            if (c == '*') {
                /* check if a comment is activated */
                if (was_slsh) {
                    /* activate the comment, reset all variables */
                    was_astk = 0;
                    was_slsh = 0;
                    in_comment = 1;
                } else {
                /* otherwise is just a simple char to print */
                    putchar(c);
                }
            }
            if (c == '/') {
                /* if there was already a slash, print it */
                if (was_slsh) {
                    putchar(c);
                }
                was_slsh = 1;
            }
        }
    }

    return 0;
}
