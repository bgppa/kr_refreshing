/* Exercise 1.16
 * Printing the longest line, + a warning if the lentgh limit is overcome */
#include <stdio.h>
#define MAXLEN 10

int my_getline (char line[], int maxlen) {
    int i = 0;
    int c = 0;
    int exceeded = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
        if (i < maxlen - 1) {
            line[i++] = c;
        } else {
            exceeded = 1;
        }
    }
    if (exceeded) {
        printf("Limit surpassed!\n");
    }
    if (c == '\n' && i < maxlen - 1) {
        line[i] = '\n';
        ++i;
    }
    line[i] = '\0';
    printf("(read len %d, excluding 0)\n", i);
    return i;
}

int copy (char to[], char from[]) {
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
    return i;
}

int main (void) {
    int c = 0;
    printf("MAXLEN = %d, including newline and 0\n", MAXLEN);
    char line[MAXLEN];
    char longer[MAXLEN];
    int max = 0;
    int len = 0;

    while ((len = my_getline(line, MAXLEN)) > 0) {
        if (len > max) {
            max = len;
            copy(longer, line);
        }
    }
    if (max > 0) {
        printf("Longest (len %d) : %s", max, longer);
    }
    return 0;
}
