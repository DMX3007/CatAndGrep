#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#define OFFSET_ASCII 64
#define YES 1
#define NO 0

static struct option long_option[] = {{"number-nonblank", 0, 0, 'b'},
                                      {"number", 0, 0, 'n'},
                                      {"squeeze-blank", 0, 0, 's'},
                                      {0, 0, 0, 0}};

struct fields {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
};

void init_struct(struct fields *flags);
void take_flag(char option, struct fields *flags);

void s_flag(char ch, char previous, int *raise, int *PRINT);
void n_flag(int *common_count, char previous);
void t_flag(char ch, int *PRINT);
void b_flag(char ch, char previous, int *common_count);
void e_flag(char ch);
void v_flag(char ch, int *PRINT);
void output(char ch);

#endif  //  SRC_CAT_S21_CAT_H_
