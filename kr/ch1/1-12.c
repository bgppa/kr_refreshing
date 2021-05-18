/* Exercise 1.12.
 * Write a program that prints its input one word per line. */
#include <stdio.h>

int main (void) {

	int IN = 1;	/* status if I am in or out the body of a word */
	int c;
	int nc, nw, ns;
	nc = nw = ns = 0;

	while ((c = getchar()) != EOF) {
		/* Checking if the first in char is blank, to determine
		 * if we start inside or outside a word */
		if (nc == 0) {
			if (c == ' ' || c == '\n' || c == '\t') {
				IN = 0;
			}
		} 
		++nc;
		/* */
		if (IN) {
			if (c == ' ' || c == '\n' || c == '\t') {
				++ns;
				IN = 0;
				putchar('\n');
				++nw;
			} else {
				putchar(c);
			}
		} else {
			/* I am outside the body of a word */
			if (c == ' ' || c == '\n' || c == '\t') {
				++ns;
			} else {
				putchar(c);
				IN = 1;
			}
		}
	}
	printf("%d characters, %d words, %d spaces\n", nc, nw, ns);
	return 0;
}
