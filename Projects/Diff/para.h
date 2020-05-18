//
//  para.h
//  diff
//
//  Created by William McCarthy on 5/9/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#ifndef para_h
#define para_h

#include <stdio.h>

#define BUFLEN 256

typedef struct para para;
struct para {
    char** base;    // ptrs to strs in whole file
    int filesize;   // num of lines in whole file
    int start;      // starting line num of current para
    int stop;       // stopping line num of current para (only has \n)
    char* firstline;   // DEBUG only
    char* secondline;
};

para* para_make(char* base[], int size, int start, int stop);
para* para_first(char* base[], int size);
para* para_next(para* p);
size_t para_filesize(para* p);
size_t para_size(para* p);
char** para_base(para* p);
char* para_info(para* p);
int para_equal(para* p, para* q, int ignorecase);
void para_print(para* p, void (*fp)(const char*));
void para_printfile(char* base[], int count, void (*fp)(const char*));


#endif /* para_h */
