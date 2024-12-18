#define WEEKS_TO_SECONDS (60.0*60.0*24.0*7.0)

node *user_why;

void GetDate(void) {
    time_t t = time(NULL);
    week_number = ((double)t)/WEEKS_TO_SECONDS;

    struct tm *tm = localtime(&t);
    day_of_the_week = tm->tm_wday;
}

void CreateDefaultProgram() {
    age = 20;
    height = 180;
    weight = 70;
    gender = 'm';
    protein = weight*1.7;
    calorie = 1.5*10*weight + 6.25*height - 5*age + 5;
    program_days = 4;
    node *firstnode = scaningwhy(); // First node is the "Why" string

    to_file(firstnode, age, height, weight, gender, protein, calorie);

    char *workout_filename = "workout_plan.txt";
    char *workout_default_filename = "workout_plan_default.txt";
    FILE *workout_file = fopen(workout_filename, "r+");
    if (workout_file == NULL) {
        copyFile(workout_default_filename, workout_filename);
        workout_file = openSafe(workout_filename, "r");
    }

    user_why = firstnode;
}

// Only cross platform way to check if file exists, according to https://stackoverflow.com/a/29510380
int DoesDataFileExist() {
    FILE *file;

    file = fopen("User_Data","r+");
    if (file == NULL) return 0;
    fclose(file);

    file = fopen("workout_plan.txt","r+");
    if(file == NULL) return 0;
    fclose(file);

    return 1;
}

int DoesUserWantToChangeDaysPerWeek() {
    char m[3] = "";
    printf("Do you want to change the amount of workout days per week? Please type 'yes' or 'no'");
    scanf("%s", m);

    if (!strcmp(m, "yes")) {
        return 1;
    }
    if (!strcmp(m, "no")) {
        return 0;
    }
    printf("Not valid answer\n");
    exit(1);
}

int DoesUserWantToAddNewWeight() {
    char m[3] = "";
    printf("Would you like to measure weight today? Please type 'yes' or 'no'");
    scanf("%s", m);

    if (!strcmp(m, "yes")) {
        return 1;
    }
    if (!strcmp(m, "no")) {
        return 0;
    }
    printf("Not valid answer\n");
    exit(1);
}

void ChangeWorkoutViaAskingQuestions() {

    if (DoesUserWantToChangeDaysPerWeek()) {
        // How many days a week
        program(); // Also calculates calories needed and protein goals
    }
    if (change_exercises_or_not()) {
        // LikeOrDislikeCertainExercises();
    }
}

void EndApp() {
    if (NULL != user_why) {
        free_space(user_why);
    }
    printf("App closing...\n");
}

void AskForWeight(void) {
    printf("What is your current weight(kg)? :");
    scanf("%d",&weight);
}

int DoesUserWantToChangeWorkout(void) {
    char m[3] = "";
    printf("Do you want to change the workout? Please type 'yes' or 'no'");
    scanf("%s", m);

    if (!strcmp(m, "yes")) {
        return 1;
    }
    if (!strcmp(m, "no")) {
        return 0;
    }

    printf("Not valid answer\n");
    exit(1);
}

int DoesUserWantToChangeOptions(void) {
    char m[3] = "";
    printf("Do you want to change any options? Please type 'yes' or 'no'");
    scanf("%s", m);

    if (!strcmp(m, "yes")) {
        return 1;
    }
    if (!strcmp(m, "no")) {
        return 0;
    }

    printf("Not valid answer\n");
    exit(1);
}


int DoesUserWantToStartAWorkoutSession(void) {
    char m[3] = "";
    printf("Do you want to start a workout? Please type 'yes' or 'no'");
    scanf("%s", m);

    if (!strcmp(m, "yes")) {
        return 1;
    }
    if (!strcmp(m, "no")) {
        return 0;
    }
    printf("Not valid answer\n");
    exit(1);
}

void SaveUserOptionsToFile() {
    to_file(user_why, age, height, weight, gender, protein, calorie);
}

// Defined but does nothing.
// File saving is currently happening during workout, not all in one go.
// Should probably be changed to be all in one go, since that would be safer
void WriteChangedWorkoutToFile() {}

void ReadInDataFile() {
    char *why;
    char genderText[8];
    int days;

    FILE *file = fopen("User_Data", "r+");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    fscanf(file, " --- Your Very Own Document ---\n");
    fscanf(file, "\n");
    fscanf(file, "\n");
    fscanf(file, "User's Why: ");

    node *firstnode = NULL, *currentnode = NULL;
    int index = 0;
    char c;
    while ((c=fgetc(file)) == '\n') {} // Clearing newlines still present in stdin
    do {
        if (!currentnode || index == SIZE_NO_LIMIT - 1) { //The element of the list starts from 0, there for it is important to minus 1.
            node *node2 = (node *)malloc(sizeof(node));
            if (!node2) {
                printf("Can't allocate memory");
                exit(EXIT_FAILURE);
            }
            node2 -> nextnode = NULL;
            if (!firstnode) {
                firstnode = node2;
            } else {
                currentnode -> nextnode = node2;
            }
            currentnode = node2;
            index = 0;
        }
        currentnode -> your_why[index++] = c;
    } while ((c=fgetc(file)) != '\n' && c != EOF);

    fscanf(file, "Personal Information:\n");
    fscanf(file, "Age: %d\n", &age);
    fscanf(file, "Height: %d cm\n", &height);
    fscanf(file, "Weight: %d kg\n", &weight);
    fscanf(file, "Gender: %s\n", genderText);
    fscanf(file, "\n");
    fscanf(file, "Training:\n");
    fscanf(file, "Days: %d\n", &days);
    fscanf(file, "\n");
    fscanf(file, "Nutritional Needs:\n");
    fscanf(file, "Protein Requirement: %f grams/day\n", &protein);
    fscanf(file, "Calorie Requirement: %f calories/day\n", &calorie);
    if (!strcmp(genderText, "Male")) {
        gender = 'm';
    } else if (!strcmp(genderText, "Female")) {
        gender = 'f';
    }
    if (user_why != NULL) {
        free_space(user_why);
    }
    user_why = firstnode;
}

