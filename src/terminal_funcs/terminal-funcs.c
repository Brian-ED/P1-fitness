#define WEEKS_TO_SECONDS (60.0*60.0*24.0*7.0)

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

    char *workout_filename = PATH_TO_DATA "workout_plan.txt";
    char *workout_default_filename = PATH_TO_DATA "workout_plan_default.txt";
    FILE *workout_file = fopen(workout_filename, "r+");
    if (workout_file == NULL) {
        copyFile(workout_default_filename, workout_filename);
        workout_file = openSafe(workout_filename, "r");
    }

    user_why = firstnode;
}

// Cross platform way to check if file exists, according to https://stackoverflow.com/a/29510380
int DoesDataFileExist() {
    FILE *file;

    file = fopen(PATH_TO_DATA "User_Data","r+");
    if (file == NULL) return 0;
    fclose(file);

    file = fopen(PATH_TO_DATA "workout_plan.txt","r+");
    if(file == NULL) return 0;
    fclose(file);

    return 1;
}

int DoesUserWantToChangeDaysPerWeek() {
    char m[4] = "";

    printf("Do you want to change the amount of workout days per week? Please type 'yes' or 'no'");
    scanf("%s", m);
    m[3] = '\0';

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
    char m[4] = "";
    printf("Would you like to measure weight today? Please type 'yes' or 'no'");
    scanf("%s", m);
    m[3] = '\0';

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
        change_workout_program();
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
    char m[4] = "";
    printf("Do you want to change the workout? Please type 'yes' or 'no'");
    scanf("%s", m);
    m[3] = '\0';

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
    char m[4] = "";
    printf("Do you want to change any options? Please type 'yes' or 'no'");
    scanf("%s", m);
    m[3] = '\0';

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
    char m[4] = "";

    printf("Do you want to start a workout? Please type 'yes' or 'no'\n");
    scanf("%s", m);
    m[3] = '\0';

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
    system("notepad " PATH_TO_DATA "User_Data");
}
