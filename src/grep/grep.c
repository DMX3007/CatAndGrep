#include <getopt.h>
#include <pcre.h>
#include <stdio.h>
#include <string.h>

#define YES 1
#define NO 0

struct fields {
    int e;
    int i;
    int v;
    int c;
    int l;
    int n;
    int h;
    int s;
    int f;
    int o;
};

typedef struct linked_list {
    char *data;
    struct linked_list *next;
} llist;

void init_flags(struct fields *flags);
void take_flag(char option, struct fields *flags, llist *p);
void re_demption(char *pattern, char *str, int *r_value);

struct linked_list *init_ll();
struct linked_list *addelem(struct linked_list *node, char *text);
void print_ll(struct linked_list *node);
void loop(struct linked_list *temp, struct linked_list *head);
struct linked_list *create_new_node(char *text);
struct linked_list *add_in_end(struct linked_list *prev_node, char *text);
void getopting(int option, int first_call, int argc, char **argv,
               llist *patterns, struct fields *flags);

int main(int argc, char *argv[]) {
    int option = 0, flag = 0, i = 0, first = 1;
    char *str = malloc(sizeof(char)), *pattern = malloc(sizeof(char));
    size_t len = 0;
    ssize_t nread;
    struct fields flags;
    llist *patterns;
    FILE *file;

    init_flags(&flags);
    // printf("\n");
    // print_ll(patterns);

    getopting(patterns, first, argc, argv, patterns, &flags);

    while (argv) {
        if ((file = fopen(argv[i], "r")) == NULL) {
            i++;
        } else {
            while ((getline(&str, &len, file)) != -1) {
                printf("after deleting this - %s\n", argv[i]);
                re_demption(pattern, str, &flag);
            }
        }
    }
    return 0;
}

void init_flags(struct fields *flags) {
    flags->v = 0;
    flags->e = 0;
    flags->i = 0;
    flags->c = 0;
    flags->l = 0;
    flags->v = 0;
    flags->n = 0;
    flags->h = 0;
    flags->s = 0;
    flags->f = 0;
    flags->o = 0;
}

void take_flag(char option, struct fields *flags, llist *p) {
    if (option == 'v') {
        flags->v = option;
    } else if (option == 'e') {
        flags->e = option;
        p = addelem(p, optarg);
    } else if (option == 'n') {
        flags->n = option;
    } else if (option == 's') {
        flags->s = option;
    } else if (option == 'i') {
        flags->i = option;
    } else if (option == 'c') {
        flags->c = option;
    } else if (option == 'h') {
        flags->h = option;
    } else if (option == 'f') {
        flags->f = option;
    } else if (option == 'o') {
        flags->o = option;
    } else if (option == '?') {
        ;
    }
}

void re_demption(char *pattern, char *str, int *r_value) {
    pcre *re;
    int options = 0, erroffset;
    const char *error;
    re = pcre_compile((char *)pattern, options, &error, &erroffset, NULL);
    if (!re) {
        *r_value = NO;
    } else {
        int count = 0, ovector[19683];
        count = pcre_exec(re, NULL, (char *)str, 31, 0, 0, ovector, 19683);
        if (count < 0) {
            printf("No match\n");
            *r_value = NO;
        } else {
            for (int c = 0; c < 2 * count; c += 2) {
                if (ovector[c] < 0) {
                    printf("<unset>\n");
                    *r_value = NO;
                } else {
                    printf("%d\n", ovector[c]);
                    *r_value = YES;
                }
            }
        }
    }
}

struct linked_list *init_ll() {
    llist *head;
    head = malloc(sizeof(llist));
    // head->data = calloc(strlen(text_or_file), sizeof(char));
    head->data = NULL;
    head->next = NULL;
    return head;
}

struct linked_list *addelem(struct linked_list *node, char *text) {
    llist *new_node, *p;
    new_node = malloc(sizeof(llist));
    p = node->next;
    node->next = new_node;
    new_node->data = text;
    new_node->next = p;
    return new_node;
}

void print_ll(struct linked_list *node) {
    llist *temp = node;
    while (temp != NULL) {
        printf("%s\n", temp->data);
        temp = temp->next;
    }
}

void getopting(int option, int first_call, int argc, char **argv,
               llist *patterns, struct fields *flags) {
    int i = 0;
    while (((option = getopt_long(argc, argv, "e:ivclnhf:so", 0, 0)) != -1)) {
        if (first_call) {
            patterns = init_ll();
            first_call--;
        }
        take_flag(option, flags, patterns);
        // memset(argv[i], '\0', strlen(argv[i]));
        i++;
    }
}
