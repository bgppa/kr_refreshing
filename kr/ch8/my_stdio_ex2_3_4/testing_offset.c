#include "my_stdio.h"
#include <stdio.h>

int main (void) {
    int c = 0;
    char *name = "prova3.txt";
    my_FILE *f = my_fopen(name, "a");
    if (f == NULL) {
        printf("null file!\n");
    } else {
        my_fseek(f, 0L, 0);
        while ((c = my_getchar()) != EOF) {
            my_putc(c, f);
        }
    }
    my_fclose(f);
    return 0;
}

