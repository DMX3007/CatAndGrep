#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "s21_cat.h"


char is_it_flag(char** string_argv_num, char *buffer) {
    int i = 1, result = 0;
    char *array_of_flags = "benst";
    size_t size = strlen(*string_argv_num);
    while (size--) {
        if (*(*(string_argv_num)) == '-') {
            char flag = **(string_argv_num + 1);
            if (strchr(array_of_flags, flag) != NULL) {
                *buffer++ = flag;
                printf("%s", buffer);
                result++;
            } else {
                // fprintf(stderr, "%s", "No such flag");
                // exit(0);
            }
        } else {
            if(is_it_file(string_argv_num)) break;
        }
        string_argv_num++;
    }
    return result;
}

int is_it_file(char** string_argv_num) {
    int result = 0;
    FILE *file;
    if (fopen(*string_argv_num, "r") != NULL) {
        result = 1;
    } else {
        ;
    }
    fclose(file);
    return result;
}