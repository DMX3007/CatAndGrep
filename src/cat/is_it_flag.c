#include <stdio.h>
#include <string.h>

int is_it_flag(char* string_argv_num) {
    size_t counter = 0, size = strlen(string_argv_num);
    char *array_of_flags = "benst";
    int result = 0;
    
    for (int i = 0; i < size; i++) {
        if ((*(string_argv_num + i)) == '-') {
            char flag = *(string_argv_num + i + 1);
            if (strchr(array_of_flags, flag) != NULL) {
                result = 1;
                counter++;
            }
        }
    }
    return result;
}
