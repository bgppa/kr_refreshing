/* Exercise 1.9:
 * Write a program to copy its input to its output, replacing each string
 * of one or more blanks by a single blank */
#include <stdio.h>

int main(void) {
	int in_space = 0;
	int c;

	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (in_space == 0) {
				putchar(c);
				in_space = 1;
			}
		} else {
			putchar(c);
			if (in_space) {
				in_space = 0;
			}
		}
	}
	return 0;
}
