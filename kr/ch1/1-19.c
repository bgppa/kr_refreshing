/* Exercise 1.19:
 * Write a function reverse(s) that reverses the character string s.
 * Use it to write a program that reverse its input a line at a time */
#include <stdio.h>
#define MAXLEN 20


void clearline (char s[], int maxlen)
{
    for (int i = 0; i < maxlen; ++i) {
        s[i] = 0;
    }
}


int reverse (char s[])
{
    int p = 0;
    while (s[p] != '\0' && s[p] != '\n') {
        ++p;
    }
    --p;
    while (p >= 0) {
        putchar(s[p--]); 
    }
    putchar('\n');
    return p;
}


int my_getline (char s[], int maxlen)
{
    int c = 0;
    int i = 0;
    while (i < maxlen - 1 && (c = getchar()) != EOF && c != '\n') {
        s[i++] = c;
    }   
    if (i < maxlen - 1 && c == '\n') {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}


int main (void) {
    int c = 0;
    char line[MAXLEN];
    clearline(line, MAXLEN);
    while (my_getline(line, MAXLEN) > 0) {
        reverse(line);
        clearline(line, MAXLEN);
    }
    return 0;
}
