#include <getopt.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int sum;
};

void init_struct(struct fields *flags);
void take_flag(char option, struct fields *flags);
char *take_file(char **string_where_search_file, char *buffer);
void printing_to_output(char *file_name);

int main(int argc, char **argv) {
    int option_index, option = 0, raise = 0;
    struct fields flags;
    char ch, previous = '\0';
    FILE *file;
    int common_count = 0;
    init_struct(&flags);
    while ((option = getopt_long(argc, argv, "benstv", long_option,
                                 &option_index)) != -1) {
        take_flag(option, &flags);
    }
    if (argc > 1) {
        for (int i = 0; argv++ && (i < argc - 1); i++) {
            if ((strlen((*argv)) > 2) && (**(argv) != '-')) {
                if ((file = fopen(*argv, "r")) == NULL) {
                    printf("s21_cat: %s: No such file or directory", *argv);
                } else {
                    while ((ch = getc(file)) != EOF) {
                        if (flags.n) {
                            if (previous == '\0' || previous == '\n') {
                                common_count++;
                                printf("%6d  ", common_count);
                            }
                            previous = ch;
                        }
                        if (flags.b) {
                            if (previous == '\0' || previous == '\n') {
                                common_count++;
                                printf("%6d  ", common_count);
                                previous = ch;
                            }
                        }
                        if (flags.t) {
                            if (ch == '\t') {
                                printf("^I");
                                ch = '\0';
                            }
                        }
                        if (flags.e) {
                            if (ch == '\n') {
                                printf("$");
                            }
                        }

                        if (flags.s) {
                            if ((ch == '\n') && (raise > 0)) {
                                ch = '\0';
                            }
                        }

                        if ((ch == '\n') && (previous == '\n')) {
                            raise++;
                        } else {
                            raise = 0;
                        }

                        previous = ch;
                        putc(ch, stdout);
                    }
                }
            }
        }
    }
}

void init_struct(struct fields *flags) {
    flags->b = 0;
    flags->e = 0;
    flags->n = 0;
    flags->s = 0;
    flags->t = 0;
    flags->v = 0;
    flags->sum = 0;
}

void take_flag(char option, struct fields *flags) {
    if (option == 'b') {
        flags->b = option;
        flags->sum += 1;
    } else if (option == 'e') {
        flags->e = option;
        flags->sum += 1;
    } else if (option == 'n') {
        flags->n = option;
        flags->sum += 1;
    } else if (option == 's') {
        flags->s = option;
        flags->sum += 1;
    } else if (option == 't') {
        flags->t = option;
        flags->sum += 1;
    } else if (option == 'v') {
        flags->v = option;
        flags->sum += 1;
    }
}
