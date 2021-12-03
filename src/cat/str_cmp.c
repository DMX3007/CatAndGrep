#include <stdio.h>
#include <string.h>

int main() {
    FILE *file = fopen("stand_out_cat.txt", "r");
    FILE *secfile = fopen("myoutput.txt", "r");
    char y = 0;
    char x = 0;
    for (int i = 0; x == y && (x != EOF || y != EOF); i++) {
        x = getc(file);
        y = getc(secfile);
        if (x != y) {
            printf("this is number of sym that doesn't equal  - %d\n", i);
            printf(" Should be %c\n", x);
            printf(" We have %c\n", y);
        }
    }
    fclose(file);
    fclose(secfile);
}
