#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>
#include <string.h>

#define MATCH 0
#define NO_MATCH 1

struct linked_list {
    char *data;
    struct linked_list *next;
};

typedef struct linked_list llist;

llist *init_ll(char *string, llist *head) {
    head->data = string;
    head->next = NULL;
    return (head);
}

llist *addelem(llist *node, char *string) {
    llist *new_node, *p;
    new_node = malloc(sizeof(llist));
    p = node->next;
    node->next = new_node;
    new_node->data = string;
    new_node->next = p;
    return (new_node);
}

void print_ll(llist *node) {
    llist *temp = node;
    while (temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

struct flags {
    int e;
    int f;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int o;
};

void take_patterns (int option, llist *head, llist *new_node, struct flags *flag, char **argv) {
    static llist *temp;
    if (option == 'e') {
    flag->e += option;
        if(flag->e == 'e') head = init_ll(optarg, head);
        else {
            if(flag->e == 'e' * 2) {
            new_node = head;
            new_node = addelem(new_node, optarg);
            temp = new_node;
            }
            else {
                temp = addelem(temp, optarg);
            }
        }
    }
    else {
        head = init_ll(argv[optind], head);
    }
}

void init_flags(struct flags *flag) {
    flag->e = 0;
    flag->f = 0;
    flag->i = 0;
    flag->v = 0;
    flag->c = 0;
    flag->l = 0;
    flag->n = 0;
    flag->h = 0;
    flag->s = 0;
    flag->o = 0;
}

void take_flags(int option, struct flags *flag, llist *head, llist *new_node, char **argv) {
    switch(option) {
        case 'e':
        take_patterns(option, head, new_node, flag, argv);
        break;
        case 'f':
        flag->f = option;
        break;
        case 'i':
        flag->i = option;
        break;
        case 'v':
        flag->v = option;
        break;
        case 'c':
        flag->c = option;
        break;
        case 'l':
        flag->l = option;
        break;
        case 'n':
        flag->n = option;
        break;
        case 'h':
        flag->h = option;
        break;
        case 's':
        flag->s = option;
        break;
        case 'o':
        flag->o = option;
        break;
        default:
        break;
    }
}

void getopting(int argc, char** argv, struct flags *flag, llist *head, llist *new_node) {
    int option = 0;
    while((option = getopt_long(argc,argv, "e:f:ivclnhso", 0 , 0)) != -1) {
        take_flags(option ,flag, head, new_node, argv);
        if(!flag->e) {
            take_patterns(option, head, new_node, flag, argv);
        }
    }
}

int re_demption(char *str, char *pattern, struct flags *flag) {
    int result = -1;
    regex_t re;
        if(flag->i) regcomp(&re, pattern, REG_ICASE);
        else {
            regcomp(&re, pattern, 0);
        }
        result = regexec(&re, str, (size_t)0, NULL, 0);
#ifdef T1
        printf("\nthis is string from re_demption - %s", str);
        printf("\tthis is result - %d\n", result);
#endif // T1
    regfree(&re);
    if(result != MATCH) return NO_MATCH;
    return MATCH;
}

void printing(char *str, struct flags *flag) {
    if(flag->e || flag->i || flag->v) {
        printf("%s", str);
    }
}

void add_nl(int lenght) {
    if(lenght != -1) {
        printf("\n");
    }
}

int processing (char *str, FILE *file, llist *head, struct flags *flag) {
    size_t size = 0, r_val = 0;
    int lenght = 0, len = -1;
    llist *temp;
    while ((lenght = getline(&str, &size, file)) != -1) {
        temp = head;
        int status = -1;
        while (temp != NULL) {
            status = re_demption(str, temp->data, flag);
            if(status == MATCH && !(flag->v)) {
                printing(str, flag);
                if (!(strchr(str, '\n'))) len = lenght;
                r_val += 1;
                break;
            }
            if(status == NO_MATCH || flag->v) {
                if((status == NO_MATCH) && (flag->v)) {
                    printing(str, flag);
                    if (!(strchr(str, '\n'))) len = lenght;
                    r_val += 1;
                    break;
                } else {
                    temp = temp->next;
                }
            }
        }
    }
    add_nl(len);
    return r_val;
}

void add_c(int new_line, struct flags *flag) {
    if (flag->c) printf("%u\n", new_line);
}

int main (int argc, char**argv) {
    struct flags flag;
    llist *new_node = malloc(sizeof(llist)), *head = malloc(sizeof(llist));
    FILE *file;
    int counter = 0, new_line = 0;
    char *str = NULL;
    init_flags(&flag);
    getopting(argc, argv, &flag, head, new_node);
    counter = optind;
    do {
        if((file = fopen(argv[counter], "r")) != NULL) {
        int temp = 0;
#ifdef T1
        printf("current file - %s", argv[counter]);
#endif
        new_line += processing(str, file, head, &flag);
        if ((new_line != temp) && (flag.l)) printf("%s\n", argv[counter]);
        fclose(file);
        counter++;
        }
        else counter++;
    } while (counter != argc);
    add_c(new_line, &flag);
    free(str);
#ifdef T1
    print_ll(head);
    printf("\ne - %d\nf - %d\ni - %d\nv - %d\nc - %d\nl - %d\nn - %d\nh - %d\ns - %d\no - %d\n", flag.e,flag.f,flag.i,flag.v,flag.c,flag.l,flag.n,flag.h,flag.s,flag.o);
#endif  //T1

    return 0;
}
