#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct forms {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int E;
    int T;
    int error;
    int verFiles;
};
void init(struct forms *p);
void parse_flags(int argcount, struct forms *p, char *argument[]);
static struct option long_options[] = {{"number", 0, 0, 'n'},
                                       {"number-nonblank", 0, 0, 'b'},
                                       {"squeeze-blank", 0, 0, 's'},
                                       {0, 0, 0, 0}};
void find_flags(struct forms *p, int *number, int *check);
void op_fle_nd_print(int argcount, char *argument[], struct forms *p);
void file_was_open(FILE *file, struct forms *p, int *cntr_ln, int *cntr_null);
void flags_on_txt(int *now, int *prev, struct forms *p, int *cntr_ln, int *cntr_null, int *new_file);
void output(struct forms *p, int *symbol);
void print_unprintable(int *now);
#endif  //  SRC_CAT_S21_CAT_H_
