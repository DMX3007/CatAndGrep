#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double PRNG() {
    srand48(time(NULL));
    unsigned int seed = lrand48();
    seed = (8253729 * seed + 2396403);
    return seed % 32768;
}

void gentext(char *argv) {
    FILE *text = fopen(argv, "w");
    unsigned int s_r_num = PRNG();
    s_r_num %= 10000;
    unsigned int ra_num = PRNG();
    for (int i = 0; i < s_r_num; i++) {
        ra_num += 1;
        ra_num %= 126;
        if ((ra_num > 32) && (ra_num < 127)) {
            putc(ra_num, text);
        }
    }
    fclose(text);
}

void genflags(char *argv) {
    char flags2[] = {'e', 'i', 'v', 'c', 'l', 'n'};
    FILE *flags = fopen(argv, "w");
    int num = 1;
    unsigned int x = PRNG();
    for (int i = 0; i < num; i++) {
        x += 1;
        x %= 5;
        putc(flags2[x], flags);
    }
    fclose(flags);
}

void genpattern(char *argv) {
    FILE *pattern = fopen(argv, "w");
    unsigned int s_r_num = PRNG();
    s_r_num %= 2;
    if (s_r_num <= 0)
        s_r_num = 1;
    int max = 126;
    int min = 32;
    for (int i = 0; i < s_r_num; i++) {
        unsigned int ra_num = PRNG();
        ra_num = min + (ra_num % (max - min));
        if ((ra_num > 32) && (ra_num < 127) &&
            (ra_num != 10 && ra_num != 11) &&
            (ra_num != 42 && ra_num != 92 &&
             ra_num != 93 && ra_num != 91)) {
            putc(ra_num, pattern);
        } else {
            putc('f', pattern);
        }
    }
}

int main(int argc, char **argv) {
    int counter = argc;
    gentext(argv[1]);
    genflags(argv[2]);
    genpattern(argv[3]);
    return 0;
}
