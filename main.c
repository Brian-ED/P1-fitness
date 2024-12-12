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
    if (DEBUG) {printf("EndApp");}
    EndApp();
    exit(0);
}

void FLOW_SaveRepsToWorkoutFile() {
    if (DEBUG) {printf("SaveRepsToWorkoutFile");}
    SaveRepsToWorkoutFile();
    FLOW_EndApp();
}

void FLOW_DoEachSet() {
    if (DEBUG) {printf("DoEachSet");}
    DoEachSet();
    FLOW_SaveRepsToWorkoutFile();
}

void FLOW_ReadInDataFileAndGetDate() {
    if (DEBUG) {printf("ReadInDataFileAndGetDate");}
    ReadInDataFile();
    GetDate();
    FLOW_DoEachSet();
}

void FLOW_DoesUserWantToStartAWorkoutSession() {
    if (DEBUG) {printf("DoesUserWantToStartAWorkoutSession");}
    if (DoesUserWantToStartAWorkoutSession()) {
        FLOW_ReadInDataFileAndGetDate();
    } else {
        FLOW_EndApp();
    }
}

void FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData() {
    if (DEBUG) {printf("ShowProgressionViaDataIfEnoughWorkoutsSavedInData");}
    ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    FLOW_DoesUserWantToStartAWorkoutSession();
}

void FLOW_AskForWeightAndCalculateCaloryIntake() {
    if (DEBUG) {printf("AskForWeightAndCalculateCaloryIntake");}
    AskForWeight();
    CalculateCaloryIntake();
    FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
}

void FLOW_DoesUserWantToAddNewWeight() {
    if (DEBUG) {printf("DoesUserWantToAddNewWeight");}
    if (DoesUserWantToAddNewWeight()) {
        FLOW_AskForWeightAndCalculateCaloryIntake();
    } else {
        FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    }
}

void FLOW_SaveUserOptionsToFile() {
    if (DEBUG) {printf("SaveUserOptionsToFile");}
    SaveUserOptionsToFile();
    FLOW_DoesUserWantToAddNewWeight();
}

void FLOW_ShowAndAskOptions() {
    if (DEBUG) {printf("ShowAndAskOptions");}
    ShowAndAskAndSaveUserOptions();
    FLOW_SaveUserOptionsToFile();
}

void FLOW_DoesUserWantToChangeOptions() {
    if (DEBUG) {printf("DoesUserWantToChangeOptions");}
    if (DoesUserWantToChangeOptions()) {
        FLOW_ShowAndAskOptions();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_WriteChangedWorkoutToFile() {
    if (DEBUG) {printf("WriteChangedWorkoutToFile");}
    WriteChangedWorkoutToFile();
    FLOW_DoesUserWantToChangeOptions();
}

void FLOW_ChangeWorkoutViaAskingUserQuestions() {
    if (DEBUG) {printf("ChangeWorkoutViaAskingUserQuestions");}
    ChangeWorkoutViaAskingQuestions();
    FLOW_WriteChangedWorkoutToFile();
}

void FLOW_DoesUserWantToChangeWorkout() {
    if (DEBUG) {printf("DoesUserWantToChangeWorkout");}
    if (DoesUserWantToChangeWorkout()) {
        FLOW_ChangeWorkoutViaAskingUserQuestions();
    } else {
        FLOW_DoesUserWantToChangeOptions();
    }
}

void FLOW_SaveProgramToWorkoutFile() {
    if (DEBUG) {printf("SaveProgramToWorkoutFile");}
    SaveProgramToWorkoutFile();
    FLOW_DoesUserWantToChangeWorkout();
}

void FLOW_CreateDefaultProgram() {
    if (DEBUG) {printf("CreateDefaultProgram");}
    CreateDefaultProgram();
    FLOW_SaveProgramToWorkoutFile();
}

void FLOW_DisplayIntroduction() {
    if (DEBUG) {printf("DisplayIntroduction");}
    DisplayIntroductionMessage();
    FLOW_CreateDefaultProgram();
}

void FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout() {
    if (DEBUG) {printf("AskUserIfTheyWantToChangeOptionsAndOrWorkout");}
    // User has been in the application before, so we say welcome back.
    show_welcome_back();

    if (UserWantsToChangeOptionsAndOrWorkout()) {
        FLOW_DoesUserWantToChangeWorkout();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_DoesDataFileExist() {
    if (DEBUG) {printf("DoesDataFileExist");}
    if (DoesDataFileExist()) {
        FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout();
    } else {
        FLOW_DisplayIntroduction();
    }
}

void FLOW_start_app() {
    if (DEBUG) {printf("start_app");}
    FLOW_DoesDataFileExist();
}

int main() {
    FLOW_start_app();
    return 0;
}
