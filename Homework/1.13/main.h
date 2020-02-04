/*
Thanh Vuong
CPSC 223C
02/04/2020
Program to print a histogram of the lengths of words
in its input
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define OUT_OF_WORD	0
#define IN_WORD		1
#define MAX_WORD_LENGTH 25

int main(int argc, const char* argv[]) {
	long char_count = 0;
	long line_count = 0;
	long word_count = 0;
	int state = OUT_OF_WORD;

	int c;

	int words_at_length[MAX_WORD_LENGTH];
	memset(words_at_length, 0, sizeof(words_at_length));

	int word_length = 0;
	int max_count_at_length = 0;

	while ((c = getchar()) != EOF) {
		++char_count;

		if (c == '\n') {
			++line_count;
		}

		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT_OF_WORD;
		} else if (state == OUT_OF_WORD) {
			state = IN_WORD;
			++word_count;
		}

		if (isalpha(c) || c == '-') {
			word_length++;
		}
		else {
			words_at_length[word_length]++;
			if (word_length > max_count_at_length) {
				max_count_at_length = word_length;
			}
			 if ((c = getchar()) != EOF)
				word_length = 0;
		}


	}

	printf("There were %ld characters, %ld words, and %ld lines\n", char_count, word_count, line_count);

	/* create histogram of word lengths */

	printf("lengths: ");
	for (int i = 0; i < MAX_WORD_LENGTH; i++) {
		printf("%d ", words_at_length[i]);
	}
	printf("\n");

	printf("Word lengths histogram:\n");

	for (int i = 0; i < MAX_WORD_LENGTH; i++) {
		printf("%4d: ", i);
		for (int j = 0; j < words_at_length[i]; j++) {
			printf("*");
		}
		for (int k = words_at_length[i]; k < max_count_at_length; k++) {
			printf("-");
		}
		printf("\n");
	}

	return 0;
}
