/* Exercise 1.8
 * Write a program to count blanks, tabs and newlines */
#include <stdio.h>

int main (void) {
	int c;
	int count = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\n' || c == '\t') {
			++count;
		}
	}
	printf("%d\n", count);
	return 0;
}
