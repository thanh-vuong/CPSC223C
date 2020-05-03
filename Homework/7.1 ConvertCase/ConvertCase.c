// Author: Thanh Vuong
// CPSC 223C
// Date: 5/2/2020
// Description: Program converts input into upper
// or lower case

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, const char* argv[]) {
	int c;

	if (strcmp(argv[1], "upper") == 0) {
		while ((c = getchar()) != EOF) { putchar(toupper(c)); }
	}
	else if (strcmp(argv[1], "lower") == 0) {
		while ((c = getchar()) != EOF) { putchar(tolower(c)); }
	}
	else {
		printf("Usage: convertcase upper/lower, then type text\n");
	}

	return 0;
}
