#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gentext(char *argv) {
    FILE *text = fopen(argv, "w");
    srand(time(NULL));
    int s_r_num = rand() % 100000;
    for (int i = 0; i < s_r_num; i++) {
        int ra_num = rand() % 126;
        if (((ra_num > 32) && (ra_num < 127)) || (ra_num == 10 || ra_num == 11)) {
            putc(ra_num, text);
        }
    }
    fclose(text);
}

void genflags(char *argv) {
    char flags2[] = {'e', 'i', 'v', 'c', 'l', 'n'};
    FILE *flags = fopen(argv, "w");
    srand(time(NULL));
    int num = 1; // e:f:ivclnhso
    for (int i = 0; i < num; i++) {
        int x = rand() % 6;
        putc(flags2[x], flags);
    }
    fclose(flags);
}

void genpattern(char *argv) {
    FILE *pattern = fopen(argv, "w");
    srand(time(NULL));
    int s_r_num = rand() % 2;
    int max = 126;
    int min = 32;
    for (int i = 0; i < s_r_num; i++) {
        int ra_num = min + rand() % (max - min);
        if ((ra_num > 32) && (ra_num < 127)) {
            putc(ra_num, pattern);
        } else
            putc('f', pattern);
    }
}

int main(int argc, char **argv) {
    int counter = argc;
    gentext(argv[1]);
    genflags(argv[2]);
    genpattern(argv[3]);
    return 0;
}

// echo TEST 1
//     grep -$(flags) $(pattern) $(textfile) >> stdfile
//     ./grep -$(flags) $(pattern) $(textfile) >> myfile
//     diff stdfile myfile