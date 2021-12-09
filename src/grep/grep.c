#include <getopt.h>
#include <pcre.h>
#include <stdio.h>

#define YES 1
#define NO 0

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
};

void init_struct(struct fields *flags);
void take_flag(char option, struct fields *flags);
void re_demption(char *pattern, char *str, int *r_value);

int main(int argc, char *argv[]) {
    char pattern[4096] = {'\0'}, *str = NULL;
    size_t len = 0;
    ssize_t nread;
    int option = 0, flag = 0;
    struct fields flags;
    FILE *file;
    while (((option = getopt_long(argc, argv, "e:i:v:c:l:n:h:f:s:o:", 0, 0)) !=
            -1)) {
        take_flag(option, &flags);
    }
    for (int i = 0; argv++ && (i < argc - 1); i++) {
        if ((strlen((*argv)) > 2) && (**(argv) != '-')) {
            if ((file = fopen(*argv, "r")) == NULL) {
                continue;
            } else {
                while ((getline(&str, len, file)) != -1) {
                    re_demption(pattern, str, &flag);
                }
            }
        }
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
}

void take_flag(char option, struct fields *flags) {
    if (option == 'v') {
        flags->v = option;
    } else if (option == 'e') {
        flags->e = option;
    } else if (option == 'n') {
        flags->n = option;
    } else if (option == 's') {
        flags->s = option;
    } else if (option == 'i') {
        flags->i = option;
    } else if (option == 'c') {
        flags->c = option;
    } else if (option == 'h') {
        flags->h = option;
    } else if (option == 'f') {
        flags->f = option;
    } else if (option == 'o') {
        flags->o = option;
    } else if (option == '?') {
        ;
    }
}

void re_demption(char *pattern, char *str, int *r_value) {
    pcre *re;
    int options = 0, erroffset;
    const char *error;
    re = pcre_compile((char *)pattern, options, &error, &erroffset, NULL);
    if (!re) {
        *r_value = NO;
    } else {
        int count = 0, ovector[19683];
        count = pcre_exec(re, NULL, (char *)str, 31, 0, 0, ovector, 19683);
        if (count < 0) {
            printf("No match\n");
            *r_value = NO;
        } else {
            for (int c = 0; c < 2 * count; c += 2) {
                if (ovector[c] < 0) {
                    printf("<unset>\n");
                    *r_value = NO;
                } else {
                    printf("%d\n", ovector[c]);
                    *r_value = YES;
                }
            }
        }
    }
}
