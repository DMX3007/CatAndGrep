#include <stdio.h>
#include <getopt.h>

static struct option long_option[] = {
    {"number-nonblank", 0, 0, 'b'}, 
    {"number", 0,0, 'n'},
    {"squeeze-blank", 0, 0, 's'},
    {0,0,0,0}
};

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

int main(int argc, char **argv) {
    char option = '0';
    int option_index = 0;
    struct fields flags;
    init_struct(&flags);
    while ((option = getopt_long(argc, argv, "benstv", long_option, &option_index)) != -1) {
        take_flag(option, &flags);
    }
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
    if(option == 'b') {
        flags->b = option;
    } else if (option == 'e') {
        flags->e = option;
    } else if (option == 'n') {
        flags->n = option;
    } else if (option == 's') {
        flags->s = option;
    } else if (option == 't') {
        flags->t = option;
    } else if (option == 'v') {
        flags->v = option;   
    }
}


