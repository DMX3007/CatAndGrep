#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generate_sequence(char* flags, char* buffer);
void take_new_flags(char* new_sequence_of_flags, char* buffer);

int main() {
    srand(time(NULL));
    int r = rand() % 1000;
    char buffer[6] = {'\0'};
    char flags[] = {'b', 'e', 'n', 's', 't', 'v'};
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
    fprintf(newfile, new_sequence_of_flags);
    fclose(newfile);

    return 0;
}

void generate_sequence(char* flags, char* buffer) {
    int i = rand() % 5;
    if (i <= 0) {
        i = rand() % 10;
    }
    for (int j = 0; j < i; j++, i--) {
        buffer[j] = flags[i];
    }
}

void take_new_flags(char* new_sequence_of_flags, char* buffer) {
    int x = rand() % 5;
    for (int i = 0; i < x; i++) {
        sprintf(new_sequence_of_flags, "%s", buffer);
    }
}
