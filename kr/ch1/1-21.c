/* Exercise 1.21
 * Write a program Entab that replaces strings of blanks by the minimum
 * number of tabs and blanks to achieve the same spacing.
 * (in other words: replace blanks with tabs) */
#include <stdio.h>
#define INTAB 4

int main (void) {
    int i = 0;
    int c = 0;
    int inspaces = 0;

    while ((c = getchar()) != EOF) {
        if (c != ' ') {
            /* The number of previous blanks is not enough
             * to form a tab; just print all of them */
            while (inspaces > 0) {
                --inspaces;
                putchar(' ');
            }
            putchar(c);
        } else {
            /* Start counting the blank spaces, and check if enough for a TAB */
            ++inspaces;
            if (inspaces == INTAB) {
                putchar('\t');
                inspaces = 0;
            }
        }
    }

    return 0;
}        
