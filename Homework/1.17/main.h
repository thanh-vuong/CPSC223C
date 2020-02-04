/*
Thanh Vuong
CPSC 223C
02/03/2020
Exercise 1.17
Program to read a set of text lines, then
prints the lines longer than 80 characters.
*/

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);

/* print the longest input line */
int main(int argc, const char* argv[]) {
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */

	while ((len = getline(line, MAXLINE)) > 0) {
		if (len > 80) {
			printf("%s\n", line);
		}
	}

	return 0;
}

/* getline: read a line into s, return length */
int getline(char s[], int lim) {
	int c, i;
	for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
	}

	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
