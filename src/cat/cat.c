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
    int option_index, option = 0,
                      raise = 0; /*, number_of_files = 0, num_old = 0;*/
    struct fields flags;
    char ch, previous = '\0';
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
                    fclose(file);
                } else {
                    // number_of_files++;
                    // if (num_old != number_of_files) {
                    //     printf("\n");
                    // }
                    while ((ch = getc(file)) != EOF) {
                        if (flags.n) {
                            if (previous == '\0' || previous == '\n') {
                                common_count++;
                                printf("%6d\t", common_count);
                            }
                            previous = ch;
                        }
                        if (flags.b) {
                            if ((previous == '\0' || previous == '\n') &&
                                (ch != '\n')) {
                                common_count++;
                                printf("%6d\t", common_count);
                                previous = ch;
                            }
                        }
                        if (flags.t) {
                            if (ch == '\t') {
                                printf("^I");
                                ch = '\0';
                            }
                        }
                        if (flags.s) {
                            if ((ch == '\n') && (previous == '\n')) {
                                raise++;
                            } else if (ch != '\n') {
                                raise = 0;
                            }
                        }
                        if (flags.v) {
                            if (((ch >= 0 && ch <= 31) || ch == 127) &&
                                (ch != 10 && ch != 9)) {
                                if (ch == 127) {
                                    printf("^?");
                                } else {
                                    printf("^%c", ch + 64);
                                }
                            }
                        }
                        previous = ch;
                        if (raise >= 2) {
                            ;
                        } else {
                            if (flags.e) {
                                if (ch == '\n') {
                                    printf("$");
                                }
                            }
                            putc(ch, stdout);
                        }
                    }
                    // num_old = number_of_files;
                }
            }
        }
        fclose(file);
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
