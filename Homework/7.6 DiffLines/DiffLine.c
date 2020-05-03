// Author: Thanh Vuong
// CPSC-223C
// Date: 5/2/2020
// Description: Program prints the first lines that differ
// between two files.

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool openfiles(int argc, const char* argv[], FILE** pfin1, FILE** pfin2);

int main(int argc, const char* argv[]) {
	FILE* fin1, * fin2;
	char line1[BUFSIZ], line2[BUFSIZ];

	if (!openfiles(argc, argv, &fin1, &fin2)) { exit(1); }

	while (!feof(fin1) && !feof(fin2) &&
		fgets(line1, BUFSIZ, fin1) != NULL &&
		fgets(line2, BUFSIZ, fin2) != NULL &&
		strcmp(line1, line2) == 0) {
	}

	printf("First different line\n");
	printf("%s\n%s\n", argv[1], line1);
	printf("%s\n%s\n", argv[2], line2);

	fclose(fin1);
	fclose(fin2);

	return 0;
}

bool openfiles(int argc, const char* argv[], FILE** pfin1, FILE** pfin2) {
	if (argc != 3) {
		printf("Usage: diffline file1 file2\n");
		return false;
	}

	fopen_s(pfin1, argv[1], "r");
	fopen_s(pfin2, argv[2], "r");

	if (*pfin1 == NULL) {
		printf("Could not open \"%s\"\n", argv[1]);
		return false;
	}

	if (*pfin2 == NULL) {
		printf("Could not open \"%s\"\n", argv[2]);
		fclose(*pfin1);
		return false;
	}
	return true;
}

