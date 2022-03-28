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
        int ch = rand() % 100;
        fprintf(file, "%c", ch);
    }
    fclose(file);
    generate_sequence(flags, buffer);
    take_new_flags(new_sequence_of_flags, buffer);
    FILE* newfile = fopen("flags.txt", "w");
    fprintf(newfile,"%s", new_sequence_of_flags);
    fclose(newfile);

    return 0;
}

void generate_sequence(char* flags, char* buffer) {
    int i = rand() % 5;
    if (i <= 0) {
        i = 5;
    }
    for (int j = 0; j <= i; j++) {
        int x = rand() % 5;
        buffer[j] = flags[x];
    }
}

void take_new_flags(char* new_sequence_of_flags, char* buffer) {
    int x = rand() % 5;
    if(x == 0) x = 5;
    snprintf(new_sequence_of_flags, 6, "%s", buffer);
}
