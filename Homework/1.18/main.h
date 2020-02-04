/*
Thanh Vuong
CPSC 223C
02/03/2020
Exercise 1.18
Program to read a set of text lines, then
removes trailing tabs/blanks, and empty lines.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000 /* maximum input line length */

int getline(char line[], int maxline);

int main(int argc, const char* argv[]) {
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */

	FILE* outFile;
	
	if (fopen_s(&outFile, "out.txt", "w") != 0) {
		printf("Could not open \"out.txt\" for writing\n");
		exit(1);
	}

	/* Read lines */
	while ((len = getline(line, MAXLINE)) > 0) {
		/* Ignore blank lines (contaning only '\n') */
		if (len > 1) {
			/* Iterate from char before null at end of line */
			for (int i = len - 2; i >= 0; i--) {
				/* Replace spaces and tabs with null */
				if (line[i] == ' ' || line[i] == '\t') {
					line[i] = '\0';
				}
				/* On first non space/tab, stop, go to next line */
				else {
					break;
				}
			}
			fprintf(outFile, "%s", line);
		}
	}

	fclose(outFile);

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
