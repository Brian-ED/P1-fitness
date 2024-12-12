#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "src/utils.c"
#include "src/Lukas2/read_from_list.c"
#include "src/Parsa/Funktioner.c"
#include "src/Lukas/progression.c"
#include "src/welcome_back-Jonas/welcome_back.c"
#include "src/terminal_funcs-Brian/terminal-funcs.c"

// TODO
void ShowProgressionViaDataIfEnoughWorkoutsSavedInData() {} // Jonas
void DoEachSet() {} // Lukas
void SaveRepsToWorkoutFile() {} // Lukas

#define DEBUG 1
// #define BACKGROUND_IMAGE "content/workout-images.png"
// #include "src/frontend-brian/frontend.c"

void FLOW_EndApp() {
    if (DEBUG) {printf("EndApp\n");}
    EndApp();
    exit(0);
}

void FLOW_SaveRepsToWorkoutFile() {
    if (DEBUG) {printf("SaveRepsToWorkoutFile\n");}
    SaveRepsToWorkoutFile();
    FLOW_EndApp();
}

void FLOW_DoEachSet() {
    if (DEBUG) {printf("DoEachSet\n");}
    DoEachSet();
    FLOW_SaveRepsToWorkoutFile();
}

void FLOW_ReadInDataFileAndGetDate() {
    if (DEBUG) {printf("ReadInDataFileAndGetDate\n");}
    ReadInDataFile();
    GetDate();
    FLOW_DoEachSet();
}

void FLOW_DoesUserWantToStartAWorkoutSession() {
    if (DEBUG) {printf("DoesUserWantToStartAWorkoutSession\n");}
    if (DoesUserWantToStartAWorkoutSession()) {
        FLOW_ReadInDataFileAndGetDate();
    } else {
        FLOW_EndApp();
    }
}

void FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData() {
    if (DEBUG) {printf("ShowProgressionViaDataIfEnoughWorkoutsSavedInData\n");}
    ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    FLOW_DoesUserWantToStartAWorkoutSession();
}

void FLOW_AskForWeightAndCalculateCaloryIntake() {
    if (DEBUG) {printf("AskForWeightAndCalculateCaloryIntake\n");}
    AskForWeight();
    CalculateCaloryIntake();
    FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
}

void FLOW_DoesUserWantToAddNewWeight() {
    if (DEBUG) {printf("DoesUserWantToAddNewWeight\n");}
    if (DoesUserWantToAddNewWeight()) {
        FLOW_AskForWeightAndCalculateCaloryIntake();
    } else {
        FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    }
}

void FLOW_SaveUserOptionsToFile() {
    if (DEBUG) {printf("SaveUserOptionsToFile\n");}
    SaveUserOptionsToFile();
    FLOW_DoesUserWantToAddNewWeight();
}

void FLOW_ShowAndAskOptions() {
    if (DEBUG) {printf("ShowAndAskOptions\n");}
    ShowAndAskAndSaveUserOptions();
    FLOW_SaveUserOptionsToFile();
}

void FLOW_DoesUserWantToChangeOptions() {
    if (DEBUG) {printf("DoesUserWantToChangeOptions\n");}
    if (DoesUserWantToChangeOptions()) {
        FLOW_ShowAndAskOptions();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_WriteChangedWorkoutToFile() {
    if (DEBUG) {printf("WriteChangedWorkoutToFile\n");}
    WriteChangedWorkoutToFile();
    FLOW_DoesUserWantToChangeOptions();
}

void FLOW_ChangeWorkoutViaAskingUserQuestions() {
    if (DEBUG) {printf("ChangeWorkoutViaAskingUserQuestions\n");}
    ChangeWorkoutViaAskingQuestions();
    FLOW_WriteChangedWorkoutToFile();
}

void FLOW_DoesUserWantToChangeWorkout() {
    if (DEBUG) {printf("DoesUserWantToChangeWorkout\n");}
    if (DoesUserWantToChangeWorkout()) {
        FLOW_ChangeWorkoutViaAskingUserQuestions();
    } else {
        FLOW_DoesUserWantToChangeOptions();
    }
}

void FLOW_SaveProgramToWorkoutFile() {
    if (DEBUG) {printf("SaveProgramToWorkoutFile\n");}
    SaveProgramToWorkoutFile();
    FLOW_DoesUserWantToChangeWorkout();
}

void FLOW_CreateDefaultProgram() {
    if (DEBUG) {printf("CreateDefaultProgram\n");}
    CreateDefaultProgram();
    FLOW_SaveProgramToWorkoutFile();
}

void FLOW_DisplayIntroduction() {
    if (DEBUG) {printf("DisplayIntroduction\n");}
    DisplayIntroductionMessage();
    FLOW_CreateDefaultProgram();
}

void FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout() {
    if (DEBUG) {printf("AskUserIfTheyWantToChangeOptionsAndOrWorkout\n");}
    // User has been in the application before, so we say welcome back.
    show_welcome_back();

    if (UserWantsToChangeOptionsAndOrWorkout()) {
        FLOW_DoesUserWantToChangeWorkout();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_DoesDataFileExist() {
    if (DEBUG) {printf("DoesDataFileExist\n");}
    if (DoesDataFileExist()) {
        FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout();
    } else {
        FLOW_DisplayIntroduction();
    }
}

void FLOW_start_app() {
    if (DEBUG) {printf("start_app\n");}
    FLOW_DoesDataFileExist();
}

int main() {
    FLOW_start_app();
    return 0;
}
