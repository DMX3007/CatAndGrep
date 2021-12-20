#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>
#include <string.h>

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

void take_flags(int option, struct flags *flag, llist *head, llist *new_node) {
    static llist *temp;
    switch(option) {
        case 'e':
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
        take_flags(option ,flag, head, new_node);
    }
}

// int re_demption() { // HERE SHOULD BE STRING
//     int result = 0;
//     regex_t re;
//     regcomp(&re, optarg, 0);
//     result = regexec(&re, string, (size_t)0, NULL, 0);
//     regfree(&re);
//     if(result != 0) return 0;
//     return 1;
// }

int main (int argc, char**argv) {
    struct flags flag;
    llist *new_node = malloc(sizeof(llist));
    llist *head = malloc(sizeof(llist));
    // regex_t re;
    // int status = 0;
    init_flags(&flag);
    getopting(argc, argv, &flag, head, new_node);
#ifdef T1
    print_ll(head);
    printf("\ne - %d\nf - %d\ni - %d\nv - %d\nc - %d\nl - %d\nn - %d\nh - %d\ns - %d\no - %d\n", flag.e,flag.f,flag.i,flag.v,flag.c,flag.l,flag.n,flag.h,flag.s,flag.o);
#endif  //T1

    return 0;

}
