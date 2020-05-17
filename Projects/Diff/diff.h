#pragma once

#ifndef diff_h
#define diff_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

#include "para.h"
#include "util.h"

#define ARGC_ERROR 1
#define TOOMANYFILES_ERROR 2
#define CONFLICTING_OUTPUT_OPTIONS 3

#define MAXSTRINGS 1024
#define MAXPARAS 4096
#define HASHLEN 200

char buf[BUFLEN];
char* strings1[MAXSTRINGS], * strings2[MAXSTRINGS];

void help(void);
void version(void);
void todo_list(void);
char* file_accesstime(const char* filename);
void loadfiles(const char* filename1, const char* filename2);
void print_option(const char* name, int value);
void diff_output_conflict_error(void);
void setoption(const char* arg, const char* s, const char* t, int* value);
void showoptions(const char* file1, const char* file2);
void init_options_files(int argc, const char* argv[]);

#endif // !diff_h
