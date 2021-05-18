/* Exercise 1.10
 * Write a program to copy its input to its output, replacing each
 * tab by \t, each backspace by \b and each backslash by \\.
 * This makes tabs and backspaces visibles in an unambiguous way. */
#include <stdio.h>

int main (void) {
	int c;
	while ((c = getchar()) != EOF) {
		if (c == '\t') {
			putchar('\\');
			putchar('t');
		} else if (c == '\b') {
			putchar('\\');
			putchar('b');
		} else if (c == '\\') {
			putchar('\\');
			putchar('\\');
		} else {
			putchar(c);
		}
	}
	return 0;
}