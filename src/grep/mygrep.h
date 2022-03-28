#ifndef SRC_GREP_MYGREP_H_
#define SRC_GREP_MYGREP_H_

#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATCH 0
#define NO_MATCH 1

struct linked_list {
    char *data;
    struct linked_list *next;
};

typedef struct linked_list llist;

struct flags {
    int e;
    int f;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int o;
    int fn;
};

#endif  //  SRC_GREP_MYGREP_H_
