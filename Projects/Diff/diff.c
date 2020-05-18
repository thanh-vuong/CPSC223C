//
//  diff.c
//  diff
//
//  Created by William McCarthy on 4/29/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#pragma warning (disable: 4996)

#include "diff.h"

void help(void) {
    printf("-v, --version 	Output version information and exit.\n");
    printf("-q, --brief 	Produce output only when files differ. If there are no differences, output nothing.\n");
    printf("-i, --ignore-case 	Ignore case differences in file contents.\n");
    printf("-s, --report-identical-files 	Report when two files are the same.\n");
    printf("-y, --side by side 	Format output in two columns.\n");
    printf("--left-column 	Output only the left column of common lines.\n");
    printf("--suppress-common-lines 	Do not output lines common between the two files.\n");
    printf("-c, -C NUM, --context[=NUM] 	Provide NUM (default 3) lines of context.\n");
    printf("-u, -U NUM, --unified[=NUM] 	Provide NUM (default 3) lines of unified context.\n");
    printf("--help 	Display a help message and exit.\n");
}

void version(void) {
    printf("\n\n\ndiff (CSUF diffutils) 1.0.0\n");
    printf("Copyright (C) 2014 CSUF\n");
    printf("This program comes with NO WARRANTY, to the extent permitted by law.\n");
    printf("You may redistribute copies of this program\n");
    printf("under the terms of the GNU General Public License.\n");
    printf("For more information about these matters, see the file named COPYING.\n");
    printf("Written by William McCarthy, and Thanh Vuong\n\n");
}

void todo_list(void) {
    printf("\n\n\nTODO: check line by line in a paragraph, using '|' for differences");
    printf("\nTODO: this starter code does not yet handle printing all of fin1's paragraphs.");
    printf("\nTODO: handle the rest of diff's options\n");
}


int showversion = 0, showbrief = 0, ignorecase = 0, report_identical = 0, showsidebyside = 0;
int showleftcolumn = 0, showunified = 0, showcontext = 0, suppresscommon = 0, diffnormal = 0;
int showhelp = 0;

int count1 = 0, count2 = 0, different = 0;

char* file_modtime(const char* filename) {
    struct stat fileinfo;
    if (stat(filename, &fileinfo) != 0) {
        fprintf(stderr, "Unable to get stats of %s\n", filename);
        return NULL;
    }
    static char str[BUFLEN];
    if (strftime(str, BUFLEN, "%Y-%m-%d %X %Z", gmtime(&fileinfo.st_mtime)) == 0){
        fprintf(stderr, "Unable to get access time of %s\n", filename);
        return NULL;
    }
    return str;
}

void loadfiles(const char* filename1, const char* filename2) {
    memset(buf, 0, sizeof(buf));
    memset(strings1, 0, sizeof(strings1));
    memset(strings2, 0, sizeof(strings2));

    FILE* fin1 = openfile(filename1, "r");
    FILE* fin2 = openfile(filename2, "r");
    
    // Read each line from file into strings array, count lines
    while (!feof(fin1) && fgets(buf, BUFLEN, fin1) != NULL) { strings1[count1++] = _strdup(buf); }  fclose(fin1);
    while (!feof(fin2) && fgets(buf, BUFLEN, fin2) != NULL) { strings2[count2++] = _strdup(buf); }  fclose(fin2);

    // Different files if different num lines or different line found
    if (count1 != count2) { different = 1;  return; }
    for (int i = 0, j = 0; i < count1 && j < count2; ++i, ++j) {
        if (strcmp(strings1[i], strings2[j]) != 0) { different = 1;  return; }
    }
}

void print_option(const char* name, int value) { printf("%17s: %s\n", name, yesorno(value)); }

void diff_output_conflict_error(void) {
    fprintf(stderr, "diff: conflicting output style options\n");
    fprintf(stderr, "diff: Try 'diff --help' for more information.)\n");
    exit(CONFLICTING_OUTPUT_OPTIONS);
}

void setoption(const char* arg, const char* s, const char* t, int* value) {
    if ((strcmp(arg, s) == 0) || ((t != NULL && strcmp(arg, t) == 0))) {
        *value = 1;
    }
}

void showoptions(const char* file1, const char* file2) {
    printf("diff options...\n");
    print_option("diffnormal", diffnormal);
    print_option("show_version", showversion);
    print_option("show_brief", showbrief);
    print_option("ignorecase", ignorecase);
    print_option("report_identical", report_identical);
    print_option("show_sidebyside", showsidebyside);
    print_option("show_leftcolumn", showleftcolumn);
    print_option("suppresscommon", suppresscommon);
    print_option("showcontext", showcontext);
    print_option("show_unified", showunified);
    print_option("showhelp", showhelp);

    printf("file1: %s,  file2: %s\n\n\n", file1, file2);

    printline();
}


void init_options_files(int argc, const char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./diff [options] file1 file2\n");
        help();
        exit(0);
    }

    int cnt = 0;
    const char* files[2] = { NULL, NULL };

    while (argc-- > 0) {
        const char* arg = *argv;
        setoption(arg, "-v", "--version", &showversion);
        setoption(arg, "-q", "--brief", &showbrief);
        setoption(arg, "-i", "--ignore-case", &ignorecase);
        setoption(arg, "-s", "--report-identical-files", &report_identical);
        setoption(arg, "--normal", NULL, &diffnormal);
        setoption(arg, "-y", "--side-by-side", &showsidebyside);
        setoption(arg, "--left-column", NULL, &showleftcolumn);
        setoption(arg, "--suppress-common-lines", NULL, &suppresscommon);
        setoption(arg, "-c", "--context", &showcontext);
        setoption(arg, "-u", "--unified", &showunified);
        setoption(arg, "--help", NULL, &showhelp);

        if (arg[0] != '-') {
            if (cnt == 2) {
                fprintf(stderr, "This version of diff only handles two files\n");
                fprintf(stderr, "Usage: ./diff [options] file1 file2\n");
                exit(TOOMANYFILES_ERROR);
            }
            else { files[cnt++] = arg; }
        }
        ++argv;   // DEBUG only;  move increment up to top of switch at release
    }

    // showoptions(files[0], files[1]); // for debug

    if (!showcontext && !showunified && !showsidebyside && !showleftcolumn) {
        diffnormal = 1;
    }

    if (showhelp) { help(); exit(0); }
    if (showversion) { version(); exit(0); }

    if (((showsidebyside || showleftcolumn) && (diffnormal || showcontext || showunified)) ||
        (showcontext && showunified) || (diffnormal && (showcontext || showunified))) {
        diff_output_conflict_error();
    }

    loadfiles(files[0], files[1]);

    if (showcontext) {
        printf("*** %s %s\n", files[0], file_modtime(files[0]));
        printf("--- %s %s\n", files[1], file_modtime(files[1]));
        printf("********************************\n");
    }

    if (report_identical && !different) { printf("The files are identical.\n\n"); exit(0); }

    if (showbrief && different) { printf("The files are different.\n\n"); exit(0); }
}


int main(int argc, const char* argv[]) {
    init_options_files(--argc, ++argv);

    //  para_printfile(strings1, count1, printleft);
    //  para_printfile(strings2, count2, printright);

    // Get first paras
    para* p = para_first(strings1, count1);
    para* q = para_first(strings2, count2);

    int foundmatch = 0;

    para* qlast = q;
    while (p != NULL) {
        qlast = q;
        foundmatch = 0;
        // Find first different para in file2
        while (q != NULL && (foundmatch = para_equal(p, q, ignorecase)) == 0) {
            q = para_next(q);
        }
        q = qlast;

        if (foundmatch) {
            // Find next different para in file2, print right
            while ((foundmatch = para_equal(p, q, ignorecase)) == 0) {
                para_print(q, printright);
                q = para_next(q);
                qlast = q;
            }
            // If not suppressed, print common on left or both
            if (!suppresscommon) { 
                para_print(q, showleftcolumn ? printleft : printboth); 
            }
            p = para_next(p);
            q = para_next(q);
        }
        else {
            para_print(p, printleft);
            p = para_next(p);
        }
    }
    // End of file1, print rest of file2
    while (q != NULL) {
        para_print(q, printright);
        q = para_next(q);
    }

    return 0;
}
