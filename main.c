#include "src/include_me_in_mains.c"

// TODO
void ShowProgressionViaDataIfEnoughWorkoutsSavedInData() {} // Jonas

#define DEBUG 1
// #define BACKGROUND_IMAGE "content/workout-images.png"
// #include "src/frontend-brian/frontend.c"

void FLOW_EndApp() {
    if (DEBUG) {printf("DEBUG: EndApp\n");}
    EndApp();
    exit(0);
}

void FLOW_SaveRepsToWorkoutFile() {
    if (DEBUG) {printf("DEBUG: SaveRepsToWorkoutFile\n");}
    // TODO: SaveRepsToWorkoutFile(); Not neccessary since DoEachSet() currently saves as it goes. Should be moved to SaveRepsToWorkoutFile().
    FLOW_EndApp();
}

void FLOW_DoEachSet() {
    if (DEBUG) {printf("DEBUG: DoEachSet\n");}

    int exercise_lenght;
    Exercise *exercises = read_exercises(&exercise_lenght);
    GetDate();
    DoEachSet(exercises, exercise_lenght);

    FLOW_SaveRepsToWorkoutFile();
}

void FLOW_ReadInDataFileAndGetDate() {
    if (DEBUG) {printf("DEBUG: ReadInDataFileAndGetDate\n");}
    // TODO: ReadInDataFile(); Reading in data is done during "DoEachSet()", and should be moved to the ReadInDataFile() function.
    GetDate();
    FLOW_DoEachSet();
}

void FLOW_DoesUserWantToStartAWorkoutSession() {
    if (DEBUG) {printf("DEBUG: DoesUserWantToStartAWorkoutSession\n");}
    if (DoesUserWantToStartAWorkoutSession()) {
        FLOW_ReadInDataFileAndGetDate();
    } else {
        FLOW_EndApp();
    }
}

void FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData() {
    if (DEBUG) {printf("DEBUG: ShowProgressionViaDataIfEnoughWorkoutsSavedInData\n");}
    ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    FLOW_DoesUserWantToStartAWorkoutSession();
}

void FLOW_AskForWeightAndCalculateCaloryIntake() {
    if (DEBUG) {printf("DEBUG: AskForWeightAndCalculateCaloryIntake\n");}
    AskForWeight();
    CalculateCaloryIntake();
    FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
}

void FLOW_DoesUserWantToAddNewWeight() {
    if (DEBUG) {printf("DEBUG: DoesUserWantToAddNewWeight\n");}
    if (DoesUserWantToAddNewWeight()) {
        FLOW_AskForWeightAndCalculateCaloryIntake();
    } else {
        FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    }
}

void FLOW_SaveUserOptionsToFile() {
    if (DEBUG) {printf("DEBUG: SaveUserOptionsToFile\n");}
    SaveUserOptionsToFile();
    FLOW_DoesUserWantToAddNewWeight();
}

void FLOW_ShowAndAskOptions() {
    if (DEBUG) {printf("DEBUG: ShowAndAskOptions\n");}
    ShowAndAskAndSaveUserOptions();
    FLOW_SaveUserOptionsToFile();
}

void FLOW_DoesUserWantToChangeOptions() {
    if (DEBUG) {printf("DEBUG: DoesUserWantToChangeOptions\n");}
    if (DoesUserWantToChangeOptions()) {
        FLOW_ShowAndAskOptions();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_WriteChangedWorkoutToFile() {
    if (DEBUG) {printf("DEBUG: WriteChangedWorkoutToFile\n");}
    WriteChangedWorkoutToFile();
    FLOW_DoesUserWantToChangeOptions();
}

void FLOW_ChangeWorkoutViaAskingUserQuestions() {
    if (DEBUG) {printf("DEBUG: ChangeWorkoutViaAskingUserQuestions\n");}
    ChangeWorkoutViaAskingQuestions();
    FLOW_WriteChangedWorkoutToFile();
}

void FLOW_DoesUserWantToChangeWorkout() {
    if (DEBUG) {printf("DEBUG: DoesUserWantToChangeWorkout\n");}
    if (DoesUserWantToChangeWorkout()) {
        FLOW_ChangeWorkoutViaAskingUserQuestions();
    } else {
        FLOW_DoesUserWantToChangeOptions();
    }
}

void FLOW_SaveProgramToWorkoutFile() {
    if (DEBUG) {printf("DEBUG: SaveProgramToWorkoutFile\n");}
    SaveProgramToWorkoutFile();
    FLOW_DoesUserWantToChangeWorkout();
}

void FLOW_CreateDefaultProgram() {
    if (DEBUG) {printf("DEBUG: CreateDefaultProgram\n");}
    CreateDefaultProgram();
    FLOW_SaveProgramToWorkoutFile();
}

void FLOW_DisplayIntroduction() {
    if (DEBUG) {printf("DEBUG: DisplayIntroduction\n");}
    DisplayIntroductionMessage();
    FLOW_CreateDefaultProgram();
}

void FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout() {
    if (DEBUG) {printf("DEBUG: AskUserIfTheyWantToChangeOptionsAndOrWorkout\n");}
    // User has been in the application before, so we say welcome back.
    show_welcome_back();

    if (UserWantsToChangeOptionsAndOrWorkout()) {
        FLOW_DoesUserWantToChangeWorkout();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_DoesDataFileExist() {
    if (DEBUG) {printf("DEBUG: DoesDataFileExist\n");}
    if (DoesDataFileExist()) {
        FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout();
    } else {
        FLOW_DisplayIntroduction();
    }
}

void FLOW_start_app() {
    if (DEBUG) {printf("DEBUG: start_app\n");}
    printf("Warning; This app only aims to assist you with fitness training and better habits. If you have injuries, or suffer from any sort of disease, seek professional medical attention before considering using our app\n");
    FLOW_DoesDataFileExist();
}

int main() {
    FLOW_start_app();
    return 0;
}
