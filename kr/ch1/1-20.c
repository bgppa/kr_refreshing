/* Exercise 1.20
 * Write a program detad that replaces tabs in the input with the proper
 * number of blanks to space to the next tab stop. Assume a fixed set of tab
 * stops. */
#include <stdio.h>
#define TABSPACE 4

int main (void) {
    int c;
    int i;
    while ((c = getchar()) != EOF) {
        if (c == '\t') {
            for (i = 0; i < TABSPACE; ++i) {
                putchar(' ');
            }
        } else {
            putchar(c);
        }
    }
    return 0;
}
    
