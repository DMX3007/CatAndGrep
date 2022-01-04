#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_sequence(char* flags, char* buffer);
void take_new_flags(char* new_sequence_of_flags, char* buffer);

void gen_pattern() {
    char array[10] = {'\0'};
    FILE *file = fopen("pattern.txt", "w");
    for (int i = 0; i < 1; i++) {
        array[i] = rand() % 65 + 60;
    }
    fprintf(file, "%s", array);
    fclose(file);
}

int main() {
    srand(time(NULL));
    int r = rand() % 1000;
    char buffer[6] = {'\0'};
    char flags[] = {'i', 'e', 'v', 'c', 'l', 'n'};  // e:f:ivclnhso"
    char new_sequence_of_flags[20] = {'\0'};

    FILE* file = fopen("gen_output.txt", "w");
    for (int x = 0; x < r; x++) {
        int z = rand() % 100;
        fprintf(file, "%c", z);
    }
    fclose(file);
    generate_sequence(flags, buffer);
    take_new_flags(new_sequence_of_flags, buffer);
    FILE* newfile = fopen("flags.txt", "w");
    fprintf(newfile, "%s" ,new_sequence_of_flags);
    gen_pattern();
    fclose(newfile);

    return 0;
}

void generate_sequence(char* flags, char* buffer) {
    int i = rand() % 7;
    if (i <= 0) {
        i = rand() % 7;
    }
    if (i == 0) {
        i = 1;
    }
    for (int j = 0; j <= i; j++) {
        int x = rand() % 7;
        buffer[j] = flags[x];
    }
}

void take_new_flags(char* new_sequence_of_flags, char* buffer) {
    int x = rand() % 7;
    for (int i = 0; i < x; i++) {
        sprintf(new_sequence_of_flags, "%s", buffer);
    }
}

