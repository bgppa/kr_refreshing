#include "my_stdio.h"
#include <stdio.h>

int main (void) {
    int c = 0;
    char *name = "prova3.txt";
    my_FILE *f = my_fopen(name, "r");
    if (f == NULL) {
        printf("null file!\n");
    } else {
        while ((c = my_getc(f)) != EOF) {
            my_putchar(c);
        }
    }
    return 0;
}

