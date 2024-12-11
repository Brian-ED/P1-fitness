void CreateDefaultProgram() {
  age = 20;
  height = 180;
  weight = 70;
  gender = 'm';
  protein = weight*1.7;
  calorie = 1.5*10*weight + 6.25*height - 5*age + 5;
  program_days = 4;
  node *firstnode = NULL; // First node is the "Why" string

  to_file(firstnode, age, height, weight, gender, protein, calorie);

  free_space(firstnode);
}

// Only cross platform way to check if file exists, according to https://stackoverflow.com/a/29510380
int DataFileExists() {
  FILE *file = fopen("sample.txt","r+");
  if(file != NULL) {
    fclose(file);
  }
  return file != NULL;
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
    printf("Not valid answer");
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

    printf("Not valid answer");
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

    printf("Not valid answer");
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
    printf("Not valid answer");
    exit(1);
}