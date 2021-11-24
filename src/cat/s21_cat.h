#ifndef _SRC_CAT_S21_CAT_H_INCLUDED
#define _SRC_CAT_S21_CAT_H_INCLUDED

struct flags {
    int blank;
    int enter;
    int number;
    int squeeze;
    int tabs;
};

char is_it_flag(char** string_argv_num, char *array_of_flags);
int is_it_file(char** string_argv_num);

#endif  //  _SRC_CAT_S21_CAT_H_INCLUDED