#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "s21_cat.h"

// void openfile();

int main(int argc, char **argv) {
    
    int i = 1, res = 0;
    char buffer[10] = {'\0'};
    while (i < argc) {
        res = is_it_flag(argv+i, buffer);
        i++;
    }
    return 0;
}

//     // argv[num];
//     // start_processing();
//     // return 0;
// }

// void start_processing(char *string, int flag) {
//     // if (no_flags) {
//     //     printing_to_output(string);
//    /* } else*/ if (flag) {
//         define_formate();
//         printing_in_file();
//     }
// }

// void define_formate(char *original_string, char *flags_string, int flag) {
//     if (flag == 'e') add_dollars(original_string);
//     // if (flag == 'n') add_numbers();
//     // if (flag == 'b') add_numbers(), remove_blanc();
//     // if (flag == 't') add_stick();
// }

// void add_dollars(char *original_string) {
//     char *buffer = "$";
//     while (original_string != '\n') original_string++;
//     strcat(original_string, buffer);
// }

// void printing_to_output(char *string) {
//     FILE *file = NULL;
//     file = fopen(string, "r");
//     int i = 0;
//         while (i != EOF) {
//             putc(i, stdout);
//             i = getc(file);
//     }
// }

// void loop() {
//     while (argv) {
//         if (is_it_flag(argv);
//     }
// }