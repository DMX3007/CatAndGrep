#include "s21_cat.h"

int main(int argc, char **argv) {
    int option_index, option = 0, raise = 0, PRINT;
    struct fields flags;
    char ch, previous = '\n';
    FILE *file;
    int common_count = 0;
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
                } else {
                    while ((ch = getc(file)) != EOF) {
                        PRINT = YES;
                        if (flags.s) {
                            s_flag(ch, previous, &raise, &PRINT);
                        }
                        if (flags.n && !flags.b) {
                            n_flag(&common_count, previous);
                        }
                        if (flags.b) {
                            b_flag(ch, previous, &common_count);
                        }
                        if (flags.t) {
                            t_flag(ch, &PRINT);
                        }
                        if (flags.e) {
                            e_flag(ch);
                        }
                        if (flags.v) {
                            v_flag(ch, &PRINT);
                        }
                        if (PRINT) {
                            putc(ch, stdout);
                        }
                        previous = ch;
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

void s_flag(char ch, char previous, int *raise, int *PRINT) {
    if ((ch == '\n') && (previous == '\n')) {
        *raise += 1;
    }
    if (ch != '\n') {
        *raise = 0;
        *PRINT = YES;
    }
    if (*raise > 1) {
        *PRINT = NO;
    }
}

void n_flag(int *common_count, char previous) {
    if (previous == '\n') {
        printf("%6d\t", *common_count += 1);
    }
}

void t_flag(char ch, int *PRINT) {
    if (ch == '\t') {
        printf("^I");
        *PRINT = NO;
    }
}

void b_flag(char ch, char previous, int *common_count) {
    if (ch != '\n' && previous == '\n') {
        printf("%6d\t", *common_count += 1);
    }
}

void e_flag(char ch) {
    if (ch == '\n') {
        printf("$");
    }
}

void v_flag(char ch, int *PRINT) {
    if (ch >= 0 && ch <= 31 && ch != '\n' && ch != '\t') {
        printf("^%c", ch + OFFSET_ASCII);
        *PRINT = NO;
    }
    if (ch > 127 && ch <= 255) {
        printf("M-%c", ch - OFFSET_ASCII);
        *PRINT = NO;
    }
    if (ch == 127) {
        printf("^?");
        *PRINT = NO;
    }
}
