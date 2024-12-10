#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define LONG_STR_SIZE 5000
#define MAX_EXERCISES 12
#define MAX_SETS 12
#define MAX_DAYS 5

typedef struct {
    char name[STR_SIZE];
    char musclegroup[STR_SIZE];
    char equipment[STR_SIZE];
    char type[STR_SIZE];
    char level[STR_SIZE];
    float rating;
    char alternative_exercises[9][STR_SIZE];
    char* exercise_info;     // Pointer for dynamic allocation

} Exercise;

int print(int r);
void resolve_backslash(char text[5000]);
void resolve_newline(char text[5000]);
void print_exercises(Exercise exercise);
int compareByRating(const Exercise* a, const Exercise* b);
int compareByName(const Exercise* a, const Exercise* b);
void merge(Exercise arr[], int left, int mid, int right, int (*cmp)(const Exercise*, const Exercise*));
void mergeSort(Exercise arr[], int left, int right, int (*cmp)(const Exercise*, const Exercise*));
int compare(const void *s1, const void *s2);

void read_exercises() {
    FILE* exercise_file = fopen("out copy.txt", "r");
    if (exercise_file == NULL) {
        perror("Error opening file");
        return;
    }

    int exercise_index = 0;
    Exercise exercise[1000] = {0}; // Array of exercises
    int ex_read;
    while(1){

        // Allocate memory for large fields dynamically
        exercise[exercise_index].exercise_info = calloc(5000, sizeof(char));
        
        // Ensure malloc succeeded
        if (!exercise[exercise_index].exercise_info) {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        // Read the data from the file
        if (print(fscanf(exercise_file,
            "%99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %f | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %99[^|] | %4999[^\n]",
            exercise[exercise_index].name,
            exercise[exercise_index].musclegroup,
            exercise[exercise_index].equipment,
            exercise[exercise_index].type,
            exercise[exercise_index].level,
            &exercise[exercise_index].rating,
            exercise[exercise_index].alternative_exercises[0],
            exercise[exercise_index].alternative_exercises[1],
            exercise[exercise_index].alternative_exercises[2],
            exercise[exercise_index].alternative_exercises[3],
            exercise[exercise_index].alternative_exercises[4],
            exercise[exercise_index].alternative_exercises[5],
            exercise[exercise_index].alternative_exercises[6],
            exercise[exercise_index].alternative_exercises[7],
            exercise[exercise_index].alternative_exercises[8],
            exercise[exercise_index].exercise_info)) == 16) {

            print_exercises(exercise[exercise_index]);
            ex_read++;

            // Break the loop if fscanf doesn't read all fields
            // Free dynamically allocated memory for each exercise
            free(exercise[exercise_index].exercise_info);
        }else{
            break;
        }

        exercise_index++;
        if (exercise_index >= 1000) {
            printf("Maximum number of exercises reached.\n");
            break;
        }
    }
    printf("%d", ex_read);
    fclose(exercise_file);

}

int print(int r){
    printf("%d\n",r);
    return r;
}


void print_exercises(Exercise exercise){
    // Print and free the data

    resolve_backslash(exercise.exercise_info);

    resolve_newline(exercise.exercise_info);


        printf("%s\n%s\n%s\n%s\n%s\n%f\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            exercise.name,
            exercise.musclegroup,
            exercise.equipment,
            exercise.type,
            exercise.level,
            exercise.rating,
            exercise.alternative_exercises[0],
            exercise.alternative_exercises[1],
            exercise.alternative_exercises[2],
            exercise.alternative_exercises[3],
            exercise.alternative_exercises[4],
            exercise.alternative_exercises[5],
            exercise.alternative_exercises[6],
            exercise.alternative_exercises[7],
            exercise.alternative_exercises[8],
            exercise.exercise_info);
}


void resolve_backslash(char text[5000]){
    char e[5000];
    strcpy(e,text);
    int a_index = 0;
    int e_index = 0;
    while (e[e_index]) {
        if (e[e_index]=='\\' && e[e_index + 1]=='n') {
            e[a_index] = '\n';
            e_index++;
        } else {
            e[a_index] = e[e_index];
        }
        a_index++;
        e_index++;
    }
    e[a_index] = '\0';
    strcpy(text, e);
}
void resolve_newline(char text[5000]){
    char e[5000];
    strcpy(e,text);
    int a_index = 0;
    int e_index = 0;
    int char_count = 0;
    while (e[e_index]) {
        if (char_count > 130 && e[e_index]==' ') {
            e[a_index] = '\n';
            char_count = 0;
        } else {
            if (e[e_index]=='\n') {
                char_count = 0;
            }
            e[a_index] = e[e_index];
            char_count++;
        }
        a_index++;
        e_index++;
    }
    a_index = 0;
    e_index = 0;
    char_count = 0;
    strcpy(text, e);
}

int compareByRating(const Exercise* a, const Exercise* b) {
    if (a->rating < b->rating) return -1;
    if (a->rating > b->rating) return 1;
    return 0; // Equal ratings
}

int compareByName(const Exercise* a, const Exercise* b) {
    return strcmp(a->name, b->name);
}

int compare(const void *s1, const void *s2)
{
//  struct Exercise *e1 = (struct Exercise *)s1;
//  struct Exercise *e2 = (struct Exercise *)s2;
//  int gendercompare = strcmp(e1->gender, e2->gender);
//  if (gendercompare == 0)  /* same gender so sort by id */
//    return e1->id - e2->id;
//  else
//    return -gendercompare;
}



void merge(Exercise arr[], int left, int mid, int right, int (*cmp)(const Exercise*, const Exercise*)) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Exercise* L = (Exercise*)malloc(n1 * sizeof(Exercise));
    Exercise* R = (Exercise*)malloc(n2 * sizeof(Exercise));

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (cmp(&L[i], &R[j]) <= 0) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(Exercise arr[], int left, int right, int (*cmp)(const Exercise*, const Exercise*)) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid, cmp);
        mergeSort(arr, mid + 1, right, cmp);

        merge(arr, left, mid, right, cmp);
    }
}
