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

void s_flag(char ch, char previous, int *raise);
void n_flag(char ch, int *common_count, char previous);
void t_flag(char ch);
void b_flag(char ch, char previous, int *common_count);
void e_flag(char ch);
void v_flag(char ch);
void output(char ch);

int main(int argc, char **argv) {
    int option_index, option = 0, new = 1, raise = 0;
    struct fields flags;
    char ch, previous = '\0';
    FILE *file;
    int common_count = 1;
    init_struct(&flags);
    while ((option = getopt_long(argc, argv, "beEnstv", long_option,
                                 &option_index)) != -1) {
        take_flag(option, &flags);
    }
    if (argc > 1) {
        for (int i = 0; argv++ && (i < argc - 1); i++) {
            if ((strlen((*argv)) > 2) && (**(argv) != '-')) {
                if ((file = fopen(*argv, "r")) == NULL) {
                    printf("s21_cat: %s: No such file or directory", *argv);
                    fclose(file);
                } else {
                    while ((ch = getc(file)) != EOF) {
                        previous = ch;
                        if (flags.s) {
                            s_flag(ch, previous, &raise);
                            output(ch);
                        }
                        if (flags.n && !flags.b) {
                            n_flag(ch, &common_count, previous);
                            output(ch);
                        }
                        if (flags.t) {
                            t_flag(ch);
                            output(ch);
                        }
                        if (flags.b) {
                            b_flag(ch, previous, common_count);
                            output(ch);
                        }
                        if (flags.e) {
                            e_flag(ch);
                            output(ch);
                        }
                        if (flags.v) {
                            v_flag(ch);
                            output(ch);
                        }
                    }
                    fclose(file);
                }
            }
        }
    }
    return 0;
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
    } else if (option == 'e') {
        flags->v = 1;
        flags->e = option;
    } else if (option == 'n') {
        flags->n = option;
    } else if (option == 's') {
        flags->s = option;
    } else if (option == 't') {
        flags->v = 1;
        flags->t = option;
    } else if (option == 'v') {
        flags->v = option;
    } else if (option == 'E') {
        flags->e = option;
    } else if (option == 'T') {
        flags->t = option;
    }
}

void s_flag(char ch, char previous, int *raise) {
    if ((ch == '\n') && (previous == '\n')) {
        *raise = 1;
        if (ch != '\n') {
            *raise = 0;
        }
    }
}

void n_flag(char ch, int *common_count, char previous) {
    if (previous == '\n' || ch == '\n') {
        printf("%6d\t", *(++common_count));
    }
}

void t_flag(char ch) {
    if (ch == '\t') {
        printf("^I");
    }
}

void b_flag(char ch, char previous, int *common_count) {
    if (ch == '\n' && previous == '\n') {
    } else
        printf("%6d\t", *(++common_count));
}

void e_flag(char ch) {
    if (ch == '\n') {
        printf('$');
    }
}

void v_flag(char ch) {
    if (ch >= 0 && ch <= 31) {
        printf("^");
    }
}

void output(char ch) { putc(ch, stdout); }
