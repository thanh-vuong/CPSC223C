/*
Thanh Vuong
CPSC 223C
02/04/2020
Exercise 1.19
Program to read and reverse each input line.
*/

#include <stdio.h>

#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);
void reverse(char *line, int len);

int main(int argc, const char* argv[]) {
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */

	/* Read and print reversed lines */
	while ((len = getline(line, MAXLINE)) > 0) {
		reverse(line, len);
		printf("%s", line);
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

/* reverse(): reverse line of characters */
void reverse(char *line, int len) {
	char temp;

	for (int i = 0; i < len / 2; i++) {
		temp = line[i];
		line[i] = line[len - 1 - i];
		line[len - 1 - i] = temp;
	}
}
