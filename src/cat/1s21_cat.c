#include "1s21_cat.h"

int main(int argc, char *argv[]) {
    if (argc > 1) {
        struct forms new;
        init(&new);
        parse_flags(argc, &new, argv);
        if (!new.error) {
            op_fle_nd_print(argc, argv, &new);
        }
    }
    return 0;
}

void init(struct forms *p) {
    p->b = 0;
    p->e = 0;
    p->n = 0;
    p->s = 0;
    p->t = 0;
    p->v = 0;
    p->E = 0;
    p->T = 0;
    p->error = 0;
    p->verFiles = 0;
}

void parse_flags(int argcount, struct forms *p, char *argument[]) {
    int check = 1, option_index = 0;
    while (check) {
        int c = getopt_long(argcount, argument, "benstvET", long_options,
                            &option_index);
        find_flags(p, &c, &check);
    }
}

void find_flags(struct forms *p, int *number, int *check) {
    if (*number == -1) {
        *check = 0;
    } else {
        if (*number == 'b') {
            p->b = 1;
        } else if (*number == 'e') {
            p->e = 1;
        } else if (*number == 'n') {
            p->n = 1;
        } else if (*number == 's') {
            p->s = 1;
        } else if (*number == 't') {
            p->t = 1;
        } else if (*number == 'v') {
            p->v = 1;
        } else if (*number == 'E') {
            p->E = 1;
        } else if (*number == 'T') {
            p->T = 1;
        }
        if (*number == '?') {
            p->error = 1;
        }
    }
}

void op_fle_nd_print(int argcount, char *argument[], struct forms *p) {
    FILE *file;
    int i = 1, check = 1;
    int cntr_ln = 1, new_file = 1;
    while (check) {
        char flag = (char)**(argument + i);
        if (flag != '-') {
            char *name = *(argument + i);
            if ((file = fopen(name, "r")) == NULL) {
                printf("cat: %s: No such file or directory\n", name);
            } else {
                file_was_open(file, p, &cntr_ln, &new_file);
                fclose(file);
            }
        }
        if (++i == argcount) {
            check = 0;
        }
    }
}

void file_was_open(FILE *file, struct forms *p, int *cntr_ln, int *new_file) {
    int now = '\0', prev = '\0';
    int cntr_null = 0;
    while ((now = getc(file)) != EOF) {
        flags_on_txt(&now, &prev, p, cntr_ln, &cntr_null, new_file);
    }
    if (prev == '\n') {
        *new_file = 1;
    }
}

void flags_on_txt(int *now, int *prev, struct forms *p, int *cntr_ln,
                  int *cntr_null, int *new_file) {
    if (p->b) {
        if ((*prev == '\n' || *cntr_ln == 1 || *new_file) && *now != '\n') {
            printf("%6d\t", *cntr_ln);
            *cntr_ln = *cntr_ln + 1;
            *new_file = 0;
        }
        *prev = *now;
    }
    if (p->n && !p->b) {
        if (*prev == '\n' || *cntr_ln == 1 || *new_file) {
            printf("%6d\t", *cntr_ln);
            *cntr_ln = *cntr_ln + 1;
            *new_file = 0;
        }
        *prev = *now;
    }
    if (*now == '\n') {
        *cntr_null += 1;
    } else {
        *cntr_null = 0;
    }
    if (p->v || p->t || p->e) {
        print_unprintable(now);
    }
    if (p->t || p->T) {
        if (*now == '\t') {
            printf("^I");
            *now = '\0';
        }
    }
    if (p->s) {
        if (*cntr_null < 3) {
            output(p, now);
        }
    } else {
        output(p, now);
    }
    *prev = *now;
}

void output(struct forms *p, int *symbol) {
    if (p->e || p->E) {
        if (*symbol == '\n') {
            printf("$");
        }
    }
    printf("%c", *symbol);
}

void print_unprintable(int *now) {
    if ((*now >= 0 && *now <= 31 && *now != 10 && *now != 9) || *now == 127) {
        if (*now == 127) {
            printf("^?");
        } else {
            printf("^%c", *now + 64);
        }
        *now = '\0';
    }
}
