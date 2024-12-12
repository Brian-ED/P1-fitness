#include <stdio.h>

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
