#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for exercises
typedef struct {
    char imgname[200];
    char name[100];
    char muscleTargeted[100];
    char equipmentType[100];
    float rating;
    char average[10];
} Exercise;

// Function to read exercises from file
int readExercises(const char *filename, Exercise exercises[], int maxExercises) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }

    char line[256];
    int exerciseCount = 0;

    while (fgets(line, sizeof(line), file) && exerciseCount < maxExercises) {
        // Read image name
        strcpy(exercises[exerciseCount].imgname, line);
        strtok(exercises[exerciseCount].imgname, "\n"); // Remove newline

        // Read exercise name
        fgets(line, sizeof(line), file);
        strcpy(exercises[exerciseCount].name, line);
        strtok(exercises[exerciseCount].name, "\n"); // Remove newline

        // Read muscle targeted
        fgets(line, sizeof(line), file);
        sscanf(line, "Muscle Targeted: %[^\n]", exercises[exerciseCount].muscleTargeted);

        // Read equipment type
        fgets(line, sizeof(line), file);
        sscanf(line, "Equipment Type: %[^\n]", exercises[exerciseCount].equipmentType);

        // Read rating
        fgets(line, sizeof(line), file);
        exercises[exerciseCount].rating = atof(line);

        // Read average
        fgets(line, sizeof(line), file);
        strtok(line, "\n"); // Remove newline
        strcpy(exercises[exerciseCount].average, line);

        exerciseCount++;
    }

    fclose(file);
    return exerciseCount;
}

// Function to print exercises
void printExercises(Exercise exercises[], int count) {
    for (int i = 0; i < count; i++) {
        printf("Imgname = %s\n", exercises[i].imgname);
        printf("Name = %s\n", exercises[i].name);
        printf("Muscle Targeted = %s\n", exercises[i].muscleTargeted);
        printf("Equipment Type = %s\n", exercises[i].equipmentType);
        printf("Rating = %.1f\n", exercises[i].rating);
        printf("Average = %s\n", exercises[i].average);
        printf("\n");
    }
}
// Function to write exercises to a new file
void writeExercisesToFile(const char *filename, Exercise exercises[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s | %s | %s | %.1f\n",
                exercises[i].name,
                exercises[i].muscleTargeted,
                exercises[i].equipmentType,
                exercises[i].rating);
    }

    fclose(file);
    printf("Exercises successfully written to %s\n", filename);
}
void writeExercisesToFile1(const char *filename, Exercise exercises[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n", exercises[i].name);
    }

    fclose(file);
    printf("Exercises successfully written to %s\n", filename);
}