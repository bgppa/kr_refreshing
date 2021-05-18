/* Exercise 1.13
 * Write a program to print a histogram of the length of words is its input.
 * It is easy to draw the histogram with the bars horizontal; a vertical
 * orientation is more challenging */

/* (I implemented the vertical orientation) */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Check if my array contains all zeroes */
int isZeroArray (const int* v, int N) {
	for (int i = 0; i < N; ++i) {
		if (v[i] != 0) {
			return 0;
		}
	}
	return 1;
}

/* Return the max value in an array, linear research */
int findMax (const int* v, int N) {
	int max = v[0];
	if (N > 0) {
		for (int i = 0; i < N; ++i) {
			if (v[i] > max) {
				max = v[i];
			}
		}
	}
	return max;
}

/* Just a simple output of the results */
int printResults (const int* v, int N) {
	for (int i = 0; i < N; ++i) {
		printf("%c %d%c", 'a' + i, v[i], (i+1) % 4 == 0 ? '\n' : '\t');
	}
	printf("\n");
	return 1;
}


/* Print a histogram with vertical bars. 
 * Key idea: check the indeces with current max value, print '*' in that
 * position, blank in all the others. Then decrease such max value -1.
 * Print a newline and repeat until the array becomes full of all zeros. */
int printHisto (const int* v, int N) {
	int* cp_v = malloc (sizeof(int) * N);
	int i = 0;
	for (i = 0; i < N; ++i) { cp_v[i] = v[i]; }

	while (!isZeroArray(cp_v, N)) {
		int m = findMax(cp_v, N);
		for (i = 0; i < N; ++i) {
			if (cp_v[i] == m) {
				printf("*  ");
				cp_v[i] -= 1;
			} else 
				printf("   ");
		}
		printf("\n");
	}

	for (i = 0; i < N; ++i) {
		printf("%c  ", 'a' + i);
	}
	printf("\n");
	for (i = 0; i < N; ++i) {
		printf("%.2d ", v[i]);
	}
	printf("\n");
}



int main (void) {
	printf("Inserire testo (tasto INVIO per terminare):\n");
	const int az = 'z' - 'a' + 1;
	int array[az];
	for (int i = 0; i < az; ++i) { array[i] = 0; };
	int c;

	while ((c = tolower(getchar())) != '\n') {
		if (c >= 'a' && c <= 'z') {
			++array[c - 'a'];
		}
	}
	printf("Analisi dei caratteri:\n");
//	printResults(array, az);
	printHisto(array, az);
	return 0;
}



