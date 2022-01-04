#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *text = fopen("text.txt", "w");
    srand(time(NULL));
    int s_r_num = rand() % 100000;
        for (int i = 0; i < s_r_num; i++) {
            int ra_num = rand() % 126;
            if(ra_num > 32 && ra_num < 127 && (ra_num == 10 || ra_num == 11)) {
                putc(ra_num, text);
        }
    }
    putc('\0', text);
    fclose(text);
return 0;
}



// echo TEST 1
//     grep -$(flags) $(pattern) $(textfile) >> stdfile
//     ./grep -$(flags) $(pattern) $(textfile) >> myfile
//     diff stdfile myfile
