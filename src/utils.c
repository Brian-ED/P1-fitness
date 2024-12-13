#include <stdio.h>
#define BUF_SIZE 65536

FILE *openSafe(char *filename, char *mode) {
    if (filename == NULL) {
        printf("ERROR: openSafe: filename was NULL pointer\n");
        exit(EXIT_FAILURE);
    }
    if (mode == NULL) {
        printf("ERROR: openSafe: mode was NULL pointer\n");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(filename, mode);
    if (file == NULL) {
        printf("ERROR: openSafe: Cannot find file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

FILE *openCreate(char *filename, char *mode) {
    if (filename == NULL) {
        printf("ERROR: openSafe: filename was NULL pointer\n");
        exit(EXIT_FAILURE);
    }
    if (mode == NULL) {
        printf("ERROR: openSafe: mode was NULL pointer\n");
        exit(EXIT_FAILURE);
    }
    FILE *file = fopen(filename, mode);
    if (file != NULL) return file;

    fclose(fopen(filename, "ab+"));

    file = fopen(filename, mode);
    if (file == NULL) {
        printf("ERROR: openSafe: Cannot find file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    return file;
}

void copyFile(char *from_filepath, char *to_filepath) {
    FILE *from = openSafe(from_filepath, "r+");
    FILE *to   = openSafe(to_filepath, "w+");
    char c;
    while ((c = fgetc(from)) != EOF) {
        fputc(c, to);
    }
    fclose(from);
    fclose(to);
}

// count_lines implementation found at https://stackoverflow.com/a/70708991
int count_lines(FILE* file)
{
    char buf[BUF_SIZE];
    int counter = 0;

    while (!feof(file)) {
        size_t res = fread(buf, 1, BUF_SIZE, file);
        if (ferror(file))
            return -1;

        for(int i = 0; i < res; i++)
            if (buf[i] == '\n')
                counter++;

    }
    rewind(file);
    return counter;
}
