/* Exercise 1.17
 * Write a program to print all input lines that are longer than 80 characters */
#include <stdio.h>
#define MAXLEN 10


int clearline (char s[], int maxlen) 
{
    for (int i = 0; i < maxlen; ++i) {
        s[i] = 0;
    }
    return maxlen;
}


int printline (char s[], int maxlen) 
{
    int i = 0;
    int c;
    int first_exceed = 1;
    int flag_newline = 0;
    while ((!flag_newline) && (c = getchar()) != EOF) {

        if (c == '\n') {
            flag_newline = 1;
        }

        if (i < maxlen - 1) {
            s[i] = c;
            ++i;
        } else {
            if (first_exceed) {
                first_exceed = 0;
                s[maxlen - 1] = '\0';
                printf("%s", s);
            }
                putchar(c);
        }

    }
    return i;
}


int main (void) {
    char line[MAXLEN];
    do {
        clearline(line, MAXLEN);
    } while (printline(line, MAXLEN) > 0);
    return 0;
}    
