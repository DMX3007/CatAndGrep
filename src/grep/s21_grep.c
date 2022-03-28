#include "./s21_grep.h"

void inithead(llist *head) {
    head->data = NULL;
    head->next = NULL;
}

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

// void print_ll(llist *node) {
//     llist *temp = node;
//     while (temp != NULL) {
//         printf("%s\n", temp->data);
//         temp = temp->next;
//     }
// }

void freeList(llist *head) {
    llist *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void take_patterns(int option, llist *head, llist *new_node, struct flags *flag, char **argv) {
    static llist *temp;
    if (option == 'e') {
        flag->e += option;
        if (flag->e == 'e') {
            head = init_ll(optarg, head);
        } else {
            if (flag->e == 'e' * 2) {
                new_node = head;
                new_node = addelem(new_node, optarg);
                temp = new_node;
            } else {
                temp = addelem(temp, optarg);
            }
        }
    } else {
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
    flag->fn = 0;
}

void take_flags(int option, struct flags *flag, llist *head, llist *new_node, char **argv) {
    switch (option) {
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

void getopting(int argc, char **argv, struct flags *flag, llist *head, llist *new_node) {
    int option = 0;
    while ((option = getopt_long(argc, argv, "e:f:ivclnhso", 0, 0)) != -1) {
        take_flags(option, flag, head, new_node, argv);
        if (!flag->e) {
            take_patterns(option, head, new_node, flag, argv);
        }
    }
}

int re_demption(char *str, char *pattern, struct flags *flag) {
    int result = -1;
    regex_t re;
    if (flag->i) {
        regcomp(&re, pattern, REG_ICASE);
    } else {
        regcomp(&re, pattern, 0);
    }
    result = regexec(&re, str, (size_t)0, NULL, 0);
    regfree(&re);
    if (result != MATCH) {
        return NO_MATCH;
    } else {
        return MATCH;
    }
}

void printing(char **argv, int counter, char *str, struct flags *flag, int cc) {
    static int num = 0;
    if (flag->fn && (!flag->l) && (!flag->c))
        printf("%s:", argv[counter]);
    if ((flag->e || flag->i || flag->v) && (!flag->l && !flag->n)) {
        printf("%s", str);
    } else if ((num != counter) && (flag->l)) {
        printf("%s\n", argv[counter]);
        num = counter;
    }
    if (flag->n) {
        printf("%d:%s", cc, str);
    }
}

void add_nl(int lenght, struct flags *flag) {
    if (lenght > -1 && (!flag->l && !flag->c)) {
        printf("\n");
    }
}

void add_c(int new_line, struct flags *flag, char **argv, int counter) {
    if (flag->c && flag->fn && (*argv[counter] != '/')) {
        printf("%s:%u\n", argv[counter], new_line);
    } else if (flag->c && !(flag->l) && (*argv[counter] != '/')) {
        printf("%u\n", new_line);
    }
}

void processing(FILE *file, llist *head, struct flags *flag, char **argv, int counter) {
    size_t size = 0, r_val = 0;
    int lenght = 0, len = -1, cmmncnt = 0;
    llist *temp = NULL;
    char *str = NULL;
    while ((lenght = getline(&str, &size, file)) != -1) {
        cmmncnt += 1;
        temp = head;
        int status = -1;
        while (temp != NULL) {
            status = re_demption(str, temp->data, flag);
            if (status == MATCH && !(flag->v)) {
                r_val += 1;
                printing(argv, counter, str, flag, cmmncnt);
                if (!(strchr(str, '\n')))
                    len = lenght;
                break;
            }
            if (status == NO_MATCH || flag->v) {
                if ((status == NO_MATCH) && (flag->v)) {
                    r_val += 1;
                    printing(argv, counter, str, flag, cmmncnt);
                    if (!(strchr(str, '\n')))
                        len = lenght;
                    break;
                } else {
                    temp = temp->next;
                }
            }
        }
    }
    add_c(r_val, flag, argv, counter);
    add_nl(len, flag);
    free(str);
}

int main(int argc, char **argv) {
    struct flags flag;
    llist *new_node = malloc(sizeof(llist));
    llist *head = malloc(sizeof(llist));
    inithead(head);
    FILE *file;
    int counter = 0;
    init_flags(&flag);
    getopting(argc, argv, &flag, head, new_node);
    counter = optind;
    if ((flag.e && ((argc - counter) > 1)) || (!flag.e && (argc - counter) > 2)) {
        flag.fn = 1;
    }
    if (argc > 3) {
        do {
            if ((file = fopen(argv[counter], "r")) != NULL) {
                processing(file, head, &flag, argv, counter);
                fclose(file);
                counter++;
            } else {
                counter++;
            }
        } while (counter != argc);
    }
    free(new_node);
    freeList(head);
    return 0;
}
