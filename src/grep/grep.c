#include <getopt.h>
#include <stdio.h>

struct fields {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
    int sum;
};

void init_struct(struct fields *flags);
void take_flag(char option, struct fields *flags);

int main(int argc, char *argv[]) {
    /*first of all we should take the flags and file from stdin then we should
    analyze our flags and checked our file third we should format our text with
    the parametrs of flags */
    int option = 0;
    struct fields flags;
    while (((option = getopt(argc, argv, "eivclnhfso")) != -1)) {
        printf("%d", option);
        take_flag(option, &flags);
    }
    return 0;
}

void init_struct(struct fields *flags) {
    flags->v = 0;
    flags->e = 0;
    flags->i = 0;
    flags->c = 0;
    flags->l = 0;
    flags->v = 0;
    flags->n = 0;
    flags->h = 0;
    flags->s = 0;
    flags->f = 0;
    flags->o = 0;
    flags->sum = 0;
}

void take_flag(char option, struct fields *flags) {
    if (option == 'v') {
        flags->v = option;
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
    } else if (option == 'i') {
        flags->i = option;
        flags->sum += 1;
    } else if (option == 'c') {
        flags->c = option;
        flags->sum += 1;
    } else if (option == 'h') {
        flags->h = option;
        flags->sum += 1;
    } else if (option == 'f') {
        flags->f = option;
        flags->sum += 1;
    } else if (option == 'o') {
        flags->o = option;
        flags->sum += 1;
    }
}
