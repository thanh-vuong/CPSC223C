//
//  main.c
//  rpn
//
//  Created by William McCarthy on 192//20.
//  Copyright © 2020 William McCarthy. All rights reserved.
//

// Thanh Vuong
// CPSC 223C
// 02/23/2020
// Reverse Polish Notation calculator with improvements:
//      4.3 Modulus and negative numbers
//      4.4 Peek/duplicate top of stack, swap top 2 of stack
//      4.5 Math library commands: sin, cos, pow...
//      4.6 Using variables


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <cmath>

#define MAXVAL  100
#define MAXOP   100     /* max size of operand/operator */
#define MAXVAR  100
#define NUMBER  '0'     /* signal that a number was found */
#define MATH    '1'     /* signal that a function was found */
#define STACK   '2'
#define VAR     '3'
#define CONST   '4'



size_t sp = 0;   // aka unsigned long -- printf using %zu
double val[MAXVAL];   // stack of values

char buf[BUFSIZ];
size_t bufp = 0;

int getch_(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch_(int c) {
    if (bufp >= BUFSIZ) {
        fprintf(stderr, "ungetch: too many characters\n");
        return;
    }

    buf[bufp++] = c;
}

void buildstr(char* s) {
    int c;
    int i = 0;

    while (isalpha(c = getch_())) {
        s[i++] = tolower(c);
    }

    s[i] = '\0';
}

int getop(char* s) {
    int i, c;
    while ((s[0] = c = getch_()) == ' ' || c == '\t') {}  // skip whitespace
    s[1] = '\0';


    // found math command, grab name
    if (isalpha(c)) {
        buildstr(s);
        return MATH;
    }

    // found stack command (start with '@'), skip over symbol, grab name
    if (c == '@') {
        s++;
        buildstr(s);
        return STACK;
    }

    // found variable command (start with '=' or '?')
    if (c == '=' || c == '?') {
        buildstr(s);
        return VAR;
    }

    // found constant command (start with '_')
    if (c == '_') {
        s++;
        buildstr(s);
        return CONST;
    }

    i = 0;

    // found minus sign
    if (c == '-') {
        c = getch_();
        // if next is digit or fraction point, append to s
        if (isdigit(c) || c == '.') {
            s[++i] = c;
        }
        else {
            if (c != EOF) {
                ungetch_(c);
            }
            // just a subtract operator at this point
            return '-';
        }
    }

    // if not a digit, fraction point, or negative, return
    if (!isdigit(c) && c != '.' && c != '-') {
        return c;
    }

    if (isdigit(c)) {  // get digits before '.'
        while (isdigit(s[++i] = c = getch_())) {}
    }
    if (c == '.') {    // get digits after decimal (if any)
        while (isdigit(s[++i] = c = getch_())) {}
    }
    s[i] = '\0';

    if (c != EOF) {
        ungetch_(c);
    }

    return NUMBER;      // return type is NUMBER, number stored in s
}

double pop(void) {
    if (sp == 0) {
        fprintf(stderr, "stack underflow\n");
        return 0.0;
    }
    return val[--sp];
}

void push(double f) {
    if (sp == MAXVAL) {
        fprintf(stderr, "stack overflow -- can't push %g\n", f);
        return;
    }
    val[sp++] = f;
}

void constfunc(char* s) {
    if (strcmp(s, "pi") == 0) {
        push(3.14159);
    }
    else if (strcmp(s, "e") == 0) {
        push(2.7182818284);
    }
    else {
        fprintf(stderr, "unknown constant: %s\n", s);
    }
}

typedef struct Var {
    char* name;
    double value;
} Var;

int varcount = 0;
Var vars[100];

int indexofvar(char* s) {
    for (int i = 0; i < varcount; i++) {
        if (strcmp(s, vars[i].name) == 0) {
            return i;
        }
    }
    return -1;
}

void varfunc(char* s) {
    int index = indexofvar(s);

    if (s[0] == '=') {
        if (varcount == MAXVAR) {
            fprintf(stderr, "too many variables, can't push %g\n", pop());
            return;
        }
        // update known variable
        if (index != -1) {
            vars[index].value = pop();
        }
        // add new variable
        else {
            varcount++;
            vars[varcount].name = s;
            vars[varcount].value = pop();
        }
    }
    if (s[0] == '?') {
        if (index != -1) {
            fprintf(stderr, "unknown variable: %s\n", s);
        }
        push(vars[index].value);
    }
}

void stackfunc(char* s) {
    double op1, op2;

    if (strcmp(s, "clear") == 0) {
        sp = 0;
        memset(val, 0, sizeof(val[sp]));
        fprintf(stderr, "stack cleared\n");
    }
    else if (strcmp(s, "peek") == 0) {
        op2 = pop();
        printf("\t%.8g\n", op2);
        push(op2);
    }
    else if (strcmp(s, "dup") == 0) {
        op2 = pop();
        push(op2);
        push(op2);
    }
    else if (strcmp(s, "swap") == 0) {
        op2 = pop();
        op1 = pop();
        push(op2);
        push(op1);
    }
    else {
        fprintf(stderr, "Unknown stack function: %s\n", s);
    }
}

void mathfunc(char* s) {
    double op1, op2;

    if (strcmp(s, "pow") == 0) {
        op2 = pop();
        op1 = pop();
        if (-1 < op2 && op2 < 1 && op1 < 0) {
            fprintf(stderr, "mathfunc: root of negative\n");
            return;
        }
        push(pow(op1, op2));
    }
    else if (strcmp(s, "sqrt") == 0) {
        if ((op1 = pop()) < 0) {
            fprintf(stderr, "mathfunc: square root of negative\n");
            return;
        }
        push(sqrt(pop()));
    }
    else if (strcmp(s, "sin") == 0) {
        push(sin(pop()));
    }
    else {
        fprintf(stderr, "Unknown math function: %s\n", s);
    }
}

void rpn(void) {
    int type;
    double op2;
    char s[BUFSIZ];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            push(-(pop() - pop()));
            break;
        case '/':
            if ((op2 = pop()) == 0.0) {
                fprintf(stderr, "divide by zero\n");
                break;
            }
            push(pop() / op2);
            break;
        case '%':
            if ((op2 = pop()) == 0.0) {
                fprintf(stderr, "divide by zero\n");
                break;
            }
            push((int)pop() % (int)(op2));
            break;
        case MATH:
            mathfunc(s);
            break;
        case STACK:
            stackfunc(s);
            break;
        case VAR:
            varfunc(s);
            break;
        case CONST:
            constfunc(s);
            break;
        default:
            fprintf(stderr, "unknown command %s\n", s);
            break;
        }
    }
}

int main(int argc, const char* argv[]) {
    rpn();

    return 0;
}
