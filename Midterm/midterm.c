// Midterm exam – The C Programming Language, Spring 2020
// (Coding section – 52 points)
// POST ALL of this CODE to your ______.github.io portfolio.
// (8 pts) (1) Find any and all mistakes in the following code, and correct them.

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void count() {
    printf("Enter lines of text here: .../n");
    int c, nc = 0, nt = 0, nbackslash = 0, nl = 0;
    while ((c = fgetc(stdin)) != EOF) {
        if (c == '\n') {
            ++nl;
        }
        else if (c == '\t') {
            ++nt;
        }
        else if (c == '\\') {
            ++nbackslash;
        }
        else if (isspace(c)) {
            ++nc;
        }
        printf("lines: %d\n", nl);
        printf("tabs: %d\n", nt);
        printf("backslashes: %d\n", nbackslash);
        printf("alphanumeric: %d\n", nc);
    }
}

int main(int argc, const char* argv[]) {
    count();
    return 0;
}

// The C Standard Library: Identify the standard library functions that do the following…
// (3 pts) (2) Find the first character c in a const char* s: ____strchr_____
// (3 pts) (3) Find the length of the prefix of const char* s that has characters in const char* t: ___strspn______
// (3 pts) (4) Terminate a program immediately ____exit_____
// (3 pts) (5) Open the file “midterm.txt” in read mode: fin = fopen("midterm.txt", "r");

// Using pointers, implement each of the following C standard library functions
char* strcpy_(char* s, const char* t) { // (4 pts) (6)
    char* p = s;

    while ((*s++ = *t++) != '\0') {}

    return p;
}

char* strncat_(char* s, const char* t, size_t n) { // (4 pts) (7)
    char* p = s;
    // Make s point to end of string s
    while (*s != '\0') {
        ++s;
    }
    // Copy n chars from t
    while (n-- > 0 && *t != '\0') {
        *s++ = *t++;
    }
    // Terminate s (n might be less than length of t)
    *s = '\0';

    return p;
}

int strcmp_(const char* s, const char* t) { // (4 pts) (8)
    // Compare char by char, advance pointers, stop at first difference
    while (*s != '\0' && *t != '\0' && *s == *t) {
        ++s;
        ++t;
    }
    return *s - *t;
}

// PART III: SHORT PROGRAM
// (20 pts) (9) Fill in the program code below for the square ADT(abstract data type)

//------ POINT ----------------------------------------------------------------
typedef struct point point;
struct point { double x, y; };
//------ SQUARE -----------------------------------------------------------------
typedef struct square square;
struct square { point ul; double side; };

square* square_init(double ulx, double uly, double side) { // TODO
    square* sq = (square*)malloc(sizeof(square));
    sq->ul.x = ulx;
    sq->ul.y = uly;
    sq->side = side;
    return sq;
}

void square_delete(square* sq) { // TODO
    free(sq);
}

void square_move(square* sq, double x, double y) { // TODO
    sq->ul.x += x;
    sq->ul.y += y;
}

void square_expandby(square* sq, double expandby) { // TODO
    sq->side *= expandby;
}

double square_area(square* sq) { // TODO
    return sq->side * sq->side;
}

//CPSC 223C—Midterm Exam(Coding section – submit code from C file to your github portfolio) page 1 of 2
double square_perimeter(square* sq) { // TODO
    return sq->side * 4;
}

// print location, side, area and perimeter
void square_print(const char* msg, square* sq) { // TODO
    printf("%s[(%.2f, %.2f), %f]\n", msg, sq->ul.x, sq->ul.y, sq->side);
}

void test_square(double ulx, double uly, double side) {
    square* sq = square_init(ulx, uly, side);
    square_print("sq is : ", sq);
    square_move(sq, 2, 2);
    square_print("sq is now : ", sq);
    square_expandby(sq, 10);
    square_print("sq has expanded to : ", sq);
    square_delete(sq);
    printf("\n\n");
}
void tests_square() {
    test_square(0, 0, 10);
    test_square(1, 1, 5);
    // add other tests if you wish // TODO (optional)
}
int main(int argc, const char* argv[]) {
    tests_square();
    return 0;
}

//CPSC 223C—Midterm Exam(Coding section – submit code from C file to your github portfolio) page 2 of 2
