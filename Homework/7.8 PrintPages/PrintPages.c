// Author: Thanh Vuong
// CPSC-223C
// Date: 5/2/2020
// Description: Program prints a set of files.
// For each file, print page by page, with
// filename for title and page number.

#include <stdio.h>
#include <stdbool.h>


bool openfile(const char* filename, FILE** pfin);
void printpages(const char* filename, FILE* fp, const size_t pagelen);


int main(int argc, const char* argv[]) {
	size_t pagelen = 50;
	FILE* fin;

	if (argc < 2) {
		printf("Usage: printpages file1 file2 ...\n");
		exit(1);
	}

	for (size_t i = 1; i < argc; ++i) {
		if (!openfile(argv[i], &fin)) { continue; }
		printpages(argv[i], fin, pagelen);
		fclose(fin);
	}

	return 0;
}

bool openfile(const char* filename, FILE** pfin) {
	fopen_s(pfin, filename, "r");

	if (pfin == NULL) {
		printf("Could not open \"%s\"\n", filename);
		return false;
	}

	return true;
}

void printpages(const char* filename, FILE* fp, const size_t pagelen) {
	size_t linecount = 0;
	char line[BUFSIZ];

	while (fgets(line, BUFSIZ, fp) != NULL) {
		if (linecount % pagelen == 0) {
			printf("\n--- %s --- Page %d\n\n", filename, 1 + linecount / pagelen);
		}
		++linecount;
		printf("%s", line);
	}
}
