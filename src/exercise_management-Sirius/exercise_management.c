int n = 0;



typedef struct {
    char* s1;
    char* Compound_or_Isolation;
    char* Recommended;
} Exercise;


typedef struct {
    Exercise exercise1, exercise2;
    Exercise exercise3, exercise4;
    Exercise exercise5, exercise6;
}Program_Exercises;

#define cp "Compound"
#define i "Isolation"
#define r "recommended"



#define Length_Of_Exercise_Legs 20
Exercise a [Length_Of_Exercise_Legs] = {
    (Exercise){"Barbell Lunge",             cp},
    (Exercise){"Barbell Walking Lunges",    cp},
    (Exercise){"Bulgarian Split Squats",    cp},
    (Exercise){"Barbell Squat",             cp,r},
    (Exercise){"Deadlift",                  cp},
    (Exercise){"Dumbbell Squat",            cp},
    (Exercise){"Dumbbell Squat",            cp},
    (Exercise){"Front Squat",               cp},
    (Exercise){"Goblet Squat",              cp},
    (Exercise){"Hack Squat Machine",        cp},
    (Exercise){"Hip Adduction Machine",     i},
    (Exercise){"Landmine Hack Squat",       cp},
    (Exercise){"Landmine Squat",            cp},
    (Exercise){"Leg Extensions",            i},
    (Exercise){"Leg Press",                 cp},
    (Exercise){"Lying Leg Curl",            i},
    (Exercise){"Romanian Deadlift",         cp,r},
    (Exercise){"Safety Bar Squat",          cp},
    (Exercise){"Smith Machine Bulgarians",  cp},
    (Exercise){"Smith Machine Squat",       cp},

};

#define Length_Of_Exercise_Calves 4
Exercise b [Length_Of_Exercise_Calves] = {
    (Exercise){"Barbell Standing Calf raises",    i},
    (Exercise){"Donkey Calf Raises",              i},
    (Exercise){"Seated Calf Raises",              i,r},
    (Exercise){"Standing Calf Raises",            i},
};

#define Length_Of_Exercise_Biceps 11
Exercise c [Length_Of_Exercise_Biceps] = {
    (Exercise){"Barbell Curl",                i},
    (Exercise){"Preacher Curls",              i},
    (Exercise){"Bayesian Curls",              i},
    (Exercise){"Cable Curl With Bar",         i},
    (Exercise){"Cable Curl With Rope",        i},
    (Exercise){"Concentration Curl",          i},
    (Exercise){"Dumbbell Curl",               i,r},
    (Exercise){"Dumbbell Preacher Curl",      i},
    (Exercise){"Hammer Curl",                 i},
    (Exercise){"Incline Dumbbell Curl",       i},
    (Exercise){"Spider Curl",                 i},
};

#define Length_Of_Exercise_Triceps 8
Exercise d [Length_Of_Exercise_Triceps] = {
    (Exercise){"Dips",                                   cp},
    (Exercise){"Seated Dips",                            cp,r},
    (Exercise){"Crossbody Cable Triceps Extensions",     i},
    (Exercise){"Dumbbell Lying Triceps Extensions",      i},
    (Exercise){"Dumbbell Standing Triceps Extensions",   i},
    (Exercise){"Overhead Cable Triceps Extensions",      i},
    (Exercise){"Tricep Pushdown With Bar",               i},
    (Exercise){"Tricep Pushdown With Rope",              i},
};

#define Length_Of_Exercise_Chest 18
Exercise e [Length_Of_Exercise_Chest] = {
    (Exercise){"Bench Press",                              cp,r},
    (Exercise){"Cable Chest Press",                        cp},
    (Exercise){"Close Grip Bench Press",                   cp},
    (Exercise){"Decline Bench Press",                      cp},
    (Exercise){"Dumbbell Chest Fly",                       i},
    (Exercise){"Dumbbell Chest Press",                     cp},
    (Exercise){"Dumbbell Decline Chest Press",             cp},
    (Exercise){"Dumbbell Floor Press",                     cp},
    (Exercise){"Dumbbell Pullover",                        i},
    (Exercise){"Incline Bench Press",                      cp},
    (Exercise){"Incline Dumbbell Press",                   cp},
    (Exercise){"Machine Chest Fly",                        i},
    (Exercise){"Machine Chest Press",                      cp},
    (Exercise){"Machine Incline Chest Press",              cp},
    (Exercise){"Pec Deck",                                 i},
    (Exercise){"Smith Machine Bench Press",                cp},
    (Exercise){"Smith Machine Incline Bench Press",        cp},
    (Exercise){"Standing Cable Chest Fly",                 i},
};

#define Length_Of_Exercise_Back 25
Exercise f [Length_Of_Exercise_Back] = {
    (Exercise){"Assisted Chin-Up",                  cp},
    (Exercise){"Assisted Pull-Up",                  cp},
    (Exercise){"Back Extensions",                   cp},
    (Exercise){"Face Pull",                         i},
    (Exercise){"Banded Muscle up",                  cp},
    (Exercise){"Barbell Row",                       cp},
    (Exercise){"Barbell Shrug",                     cp},
    (Exercise){"Cable Close Grip Seated Row",       cp},
    (Exercise){"Cable Wide Grip Seated Row",        cp},
    (Exercise){"Chin-Up",                           cp},
    (Exercise){"Deficit Deadlift",                  cp},
    (Exercise){"Dumbbell Row",                      cp},
    (Exercise){"Dumbbell Shrug",                    i},
    (Exercise){"Gorilla Row",                       cp},
    (Exercise){"Inverted Row",                      cp},
    (Exercise){"Inverted Row With Underhand Grip",  cp},
    (Exercise){"Lat Pulldown With Pronated Grip",   cp,r},
    (Exercise){"Lat Pulldown With Supinated Grip",  cp},
    (Exercise){"Muscle-Up",                         cp},
    (Exercise){"One Handed Cable Row",              cp},
    (Exercise){"One Handed Lat Pulldown",           cp},
    (Exercise){"Pull-Up",                           cp},
    (Exercise){"Pull-Up With Neutral Grip",         cp},
    (Exercise){"Seated Machine Row",                cp},
    (Exercise){"T-Bar Row",                         cp},
};

#define Length_Of_Exercise_Shoulders 22
Exercise g [Length_Of_Exercise_Shoulders] = {
    (Exercise){"Arnold Press",                              cp,r},
    (Exercise){"Barbell Front Raise",                       i},
    (Exercise){"Barbell Rear Delt Row",                     cp},
    (Exercise){"Barbell Upright Row",                       cp},
    (Exercise){"Cable Lateral Raises",                      i},
    (Exercise){"Cable Rear Delt Row",                       cp},
    (Exercise){"Dumbbell Front Raise",                      i},
    (Exercise){"Dumbbell Lateral Raise",                    i},
    (Exercise){"Dumbbell Rear Delt Row",                    cp},
    (Exercise){"Dumbbel Shoulder Press",                    cp},
    (Exercise){"Face Pull",                                 i},
    (Exercise){"Landmine Press",                            cp},
    (Exercise){"Machine Lateral Raise",                     i},
    (Exercise){"Machine Shoulder Press",                    cp},
    (Exercise){"Overhead Press",                            cp},
    (Exercise){"Plate Front Raise",                         i},
    (Exercise){"Reverse Cable Fly",                         i},
    (Exercise){"Reverse Dumbbell Fly",                      i},
    (Exercise){"Reverse Machine Fly",                       i},
    (Exercise){"Seated Dumbbell Shoulder Press",            cp},
    (Exercise){"Seated Barbell Overhead Press",             cp},
    (Exercise){"Seated Smith Machine Shoulder Press",       cp},

};

#define Length_Of_Exercise_Glutes 9
Exercise h [Length_Of_Exercise_Glutes] = {
    (Exercise){"Cossack Squat",                       cp},
    (Exercise){"Dumbbell Romanian Deadlift",          cp},
    (Exercise){"Hip Abduction Machine",               i},
    (Exercise){"Hip Thrust",                          cp,r},
    (Exercise){"Hip Thrust Machine",                  cp},
    (Exercise){"Standing Glute Kickback In Machine",  cp},
    (Exercise){"Sumo Deadlift",                       cp},
};


// how many times do you want to train a week?
// select 3, 4 or 5. If user wants to train 1 or 2 times per week > create a fullbody workout
// scanf the number and set it to n


Program_Exercises function_a() {

    //Fullbody
        srand(time(0));

        Exercise exercise1 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise1.Recommended != r) {
        exercise1 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == exercise1.s1) {
        exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise3 = f[rand() %Length_Of_Exercise_Back];
        while (exercise3.Recommended != r) {
            exercise3 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise4 = f[rand() %Length_Of_Exercise_Back];
        while (exercise4.Compound_or_Isolation != cp || exercise4.s1 == exercise3.s1) {
            exercise4 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise5 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise5.Recommended != r) {
            exercise5 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise6 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise6.Compound_or_Isolation != cp || exercise6.s1 == exercise5.s1) {
            exercise6 = a[rand() %Length_Of_Exercise_Legs];
        }
        Program_Exercises exercises = {
        exercise1,exercise2,exercise3,exercise4,exercise5,exercise6
        };
        return exercises;
}

Program_Exercises function_b() {
    //Upperbody

        srand(time(0));

        Exercise exercise1 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise1.Recommended != r) {
            exercise1 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == exercise1.s1) {
            exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise3 = g[rand() %Length_Of_Exercise_Shoulders];
        while (exercise3.Compound_or_Isolation != cp) {
            exercise3 = g[rand() %Length_Of_Exercise_Shoulders];
        }
        Exercise exercise4 = f[rand() %Length_Of_Exercise_Back];
        while (exercise4.Recommended != r) {
            exercise4 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise5 = f[rand() %Length_Of_Exercise_Back];
        while (exercise5.Compound_or_Isolation != cp && exercise5.s1 != exercise4.s1) {
            exercise5 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise6 = d[rand() %Length_Of_Exercise_Triceps];
        while (exercise6.Compound_or_Isolation != i) {
            exercise6 = d[rand() %Length_Of_Exercise_Triceps];
        }
        Program_Exercises exercises = {
        exercise1,exercise2,exercise3,exercise4,exercise5,exercise6
        };
        return exercises;
}

Program_Exercises function_c() {

    //Lowerbody

        srand(time(0));


        Exercise exercise1 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise1.Recommended != r) {
            exercise1 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise2 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise2.Compound_or_Isolation != cp && exercise2.s1 != exercise1.s1) {
            exercise2 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise3 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise3.Compound_or_Isolation != cp && exercise3.s1 != exercise2.s1 && exercise3.s1 != exercise1.s1) {
            exercise3 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise4 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise4.Compound_or_Isolation != i) {
            exercise4 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise5 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise5.Compound_or_Isolation != i && exercise5.s1 != exercise4.s1) {
            exercise5 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise6 = b[rand() %Length_Of_Exercise_Calves];
        while (exercise6.Recommended != r) {
            exercise6 = b[rand() %Length_Of_Exercise_Calves];
        }
        Program_Exercises exercises = {
        exercise1,exercise2,exercise3,exercise4,exercise5,exercise6
        };
        return exercises;
}
Program_Exercises function_d() {

    //Push day

        srand(time(0));


        Exercise exercise1 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise1.Recommended != r) {
            exercise1 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise2 = g[rand() %Length_Of_Exercise_Shoulders];
        while (exercise2.Compound_or_Isolation != cp) {
            exercise2 = g[rand() %Length_Of_Exercise_Shoulders];
        }
        Exercise exercise3 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise3.Compound_or_Isolation != cp && exercise3.s1 != exercise1.s1) {
            exercise3 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise4 = g[rand() %Length_Of_Exercise_Shoulders];
        while (exercise4.Compound_or_Isolation != i) {
            exercise4 = g[rand() %Length_Of_Exercise_Shoulders];
        }
        Exercise exercise5 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise5.Compound_or_Isolation != i) {
            exercise5 = e[rand() %Length_Of_Exercise_Chest];
        }
        Exercise exercise6 = d[rand() %Length_Of_Exercise_Triceps];
        while (exercise6.Compound_or_Isolation != i) {
            exercise6 = d[rand() %Length_Of_Exercise_Triceps];
        }
        Program_Exercises exercises = {
        exercise1,exercise2,exercise3,exercise4,exercise5,exercise6
        };
        return exercises;
}
Program_Exercises function_e() {

    //Pull day

        srand(time(0));


        Exercise exercise1 = f[rand() %Length_Of_Exercise_Back];
        while (exercise1.Recommended != r) {
            exercise1 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise2 = f[rand() %Length_Of_Exercise_Back];
        while (exercise2.Compound_or_Isolation != cp && exercise2.s1 != exercise1.s1) {
            exercise2 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise3 = f[rand() %Length_Of_Exercise_Back];
        while (exercise3.Compound_or_Isolation != cp && exercise3.s1 != exercise2.s1 && exercise3.s1 != exercise1.s1) {
            exercise3 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise4 = f[rand() %Length_Of_Exercise_Back];
        while (exercise4.Compound_or_Isolation != r) {
            exercise4 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise5 = f[rand() %Length_Of_Exercise_Back];
        while (exercise5.Compound_or_Isolation != i && exercise5.s1 != exercise4.s1) {
            exercise5 = f[rand() %Length_Of_Exercise_Back];
        }
        Exercise exercise6 = c[rand() %Length_Of_Exercise_Biceps];
        while (exercise6.Compound_or_Isolation != i) {
            exercise6 = c[rand() %Length_Of_Exercise_Biceps];
        }
        Program_Exercises exercises = {
        exercise1,exercise2,exercise3,exercise4,exercise5,exercise6
        };
        return exercises;
}
Program_Exercises function_f() {
    //Leg day

        srand(time(0));


        Exercise exercise1 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise1.Recommended != r) {
            exercise1 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise2 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise2.Compound_or_Isolation != cp && exercise2.s1 != exercise1.s1) {
            exercise2 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise3 = h[rand() %Length_Of_Exercise_Glutes];
        while (exercise3.Compound_or_Isolation != cp) {
            exercise3 = h[rand() %Length_Of_Exercise_Glutes];
        }
        Exercise exercise4 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise4.Compound_or_Isolation != i) {
            exercise4 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise5 = a[rand() %Length_Of_Exercise_Legs];
        while (exercise5.Compound_or_Isolation != i && exercise5.s1 != exercise4.s1) {
            exercise5 = a[rand() %Length_Of_Exercise_Legs];
        }
        Exercise exercise6 = b[rand() %Length_Of_Exercise_Calves];
        while (exercise6.Recommended != r) {
            exercise6 = b[rand() %Length_Of_Exercise_Calves];
        }
        Program_Exercises exercises = {
        exercise1,exercise2,exercise3,exercise4,exercise5,exercise6
        };
        return exercises;
}

Program_Exercises program1;
Program_Exercises program2;
Program_Exercises program3;
Program_Exercises program4;
Program_Exercises program5;


void AmountOfDaysToTrain() {
    if (n <= 3) {
        program1 = function_a();
        printf("Here is your full body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program1.exercise1.s1,program1.exercise2.s1,program1.exercise3.s1,program1.exercise4.s1,program1.exercise5.s1,program1.exercise6.s1);

    }
    if (n == 4) {
        program1 = function_b();
        printf("Here is your upper body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program1.exercise1.s1,program1.exercise2.s1,program1.exercise3.s1,program1.exercise4.s1,program1.exercise5.s1,program1.exercise6.s1);

        program2 = function_c();
        printf("Here is your lower body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program2.exercise1.s1,program2.exercise2.s1,program2.exercise3.s1,program2.exercise4.s1,program2.exercise5.s1,program2.exercise6.s1);

    }
    if (n == 5){
        program1 = function_b();
        printf("Here is your upper body workout program: \n %s\n %s\n %s\n %s\n %s\n %s\n",program1.exercise1.s1,program1.exercise2.s1,program1.exercise3.s1,program1.exercise4.s1,program1.exercise5.s1,program1.exercise6.s1);

        program2 = function_c();
        printf("Here is your lower body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program2.exercise1.s1,program2.exercise2.s1,program2.exercise3.s1,program2.exercise4.s1,program2.exercise5.s1,program2.exercise6.s1);

        program3 = function_d();
        printf("Here is your push day workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program3.exercise1.s1,program3.exercise2.s1,program3.exercise3.s1,program3.exercise4.s1,program3.exercise5.s1,program3.exercise6.s1);

        program4 = function_e();
        printf("Here is your pull day workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program4.exercise1.s1,program4.exercise2.s1,program4.exercise3.s1,program4.exercise4.s1,program4.exercise5.s1,program4.exercise6.s1);

        program5 = function_f();
        printf("Here is your leg day workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program5.exercise1.s1,program5.exercise2.s1,program5.exercise3.s1,program5.exercise4.s1,program5.exercise5.s1,program5.exercise6.s1);

    }
}


char input[10];
char programDislike[100];
int inputNumber = 0;
typedef struct program_select {
    int programDislike, inputNumber;
} program_select;

program_select DoYouLikeTheWorkout() {
    printf("Do you like these exercises?\n You can also change the exercises if your gym does not have the matching equipment. Type 'yes' to continue, type 'no' to change:\n");
    scanf("%s", input);

    if (strcmp(input, "yes") == 0) {
        //lock in workout

        return (program_select){-1, -1};
    }

    if (strcmp(input, "no") == 0) {
        printf("Which workout program would you like to make changes to?\n Please enter one of the following:\n 'Full' for full body\n 'Upper' for upper body\n 'Lower' for lower body\n 'Push' for push\n 'Pull' for pull days\n 'Legs' for leg day\n");
        scanf("%s", programDislike);

        int disliked_program_index = 0;
        if (strcmp(programDislike, "Full") == 0) {
            printf("This is your full body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program1.exercise1.s1,program1.exercise2.s1,program1.exercise3.s1,program1.exercise4.s1,program1.exercise5.s1,program1.exercise6.s1);
            disliked_program_index=0;
        }
        if (strcmp(programDislike, "Upper") == 0) {
            printf("This is your upper body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program1.exercise1.s1,program1.exercise2.s1,program1.exercise3.s1,program1.exercise4.s1,program1.exercise5.s1,program1.exercise6.s1);
            disliked_program_index=1;
        }
        if (strcmp(programDislike, "Lower") == 0) {
            printf("This is your lower body workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program2.exercise1.s1,program2.exercise2.s1,program2.exercise3.s1,program2.exercise4.s1,program2.exercise5.s1,program2.exercise6.s1);
            disliked_program_index=2;
        }
        if (strcmp(programDislike, "Push") == 0) {
            printf("This is your push day workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program3.exercise1.s1,program3.exercise2.s1,program3.exercise3.s1,program3.exercise4.s1,program3.exercise5.s1,program3.exercise6.s1);
            disliked_program_index=3;
        }
        if (strcmp(programDislike, "Pull") == 0) {
            printf("This is your pull day workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program4.exercise1.s1,program4.exercise2.s1,program4.exercise3.s1,program4.exercise4.s1,program4.exercise5.s1,program4.exercise6.s1);
            disliked_program_index=4;
        }
        if (strcmp(programDislike, "Legs") == 0) {
            printf("This is your leg day workout program:\n %s\n %s\n %s\n %s\n %s\n %s\n",program5.exercise1.s1,program5.exercise2.s1,program5.exercise3.s1,program5.exercise4.s1,program5.exercise5.s1,program5.exercise6.s1);
            disliked_program_index=5;
        }

        printf("Which exercises do you not like?\nPlease choose a number between 1 - 6 to change the exercise.\n 1 is the first exercise, 2 is the second exercise and so on...");
        scanf("%d", &inputNumber);
        return (program_select){disliked_program_index, inputNumber};
    }
    return (program_select){-1, -1};
}



void ChangeProgram(program_select selected){

    Program_Exercises all_programs[] = {program1, program2, program3, program4, program5};
    Program_Exercises program_to_change = all_programs[selected.programDislike];

    Exercise all_exercises[] = {
        program_to_change.exercise1,
        program_to_change.exercise2,
        program_to_change.exercise3,
        program_to_change.exercise4,
        program_to_change.exercise5,
        program_to_change.exercise6
    };
    Exercise exercise_to_change = all_exercises[selected.inputNumber];

    if (inputNumber == 1 && strcmp(programDislike, "Full") == 0) {
        Exercise exercise1 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise1.Compound_or_Isolation != cp || exercise1.s1 == program1.exercise2.s1) {
            exercise1 = e[rand() %Length_Of_Exercise_Chest];
        }
    }

    if (inputNumber == 2 && strcmp(programDislike, "Full") == 0) {
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == program1.exercise1.s1) {
            exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
    }

    if (inputNumber == 3 && strcmp(programDislike, "Full") == 0) {
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == program1.exercise1.s1) {
            exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
    }

    if (inputNumber == 4 && strcmp(programDislike, "Full") == 0) {
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == program1.exercise1.s1) {
            exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
    }

    if (inputNumber == 5 && strcmp(programDislike, "Full") == 0) {
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == program1.exercise1.s1) {
            exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
    }

    if (inputNumber == 6 && strcmp(programDislike, "Full") == 0) {
        Exercise exercise2 = e[rand() %Length_Of_Exercise_Chest];
        while (exercise2.Compound_or_Isolation != cp || exercise2.s1 == program1.exercise1.s1) {
            exercise2 = e[rand() %Length_Of_Exercise_Chest];
        }
    }
}
