#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "src/Parsa/Funktioner.c"
#include "src/Lukas/progression.c"
#include "src/welcome_back/welcome_back.c"

#define DEBUG 1
// #define BACKGROUND_IMAGE "content/workout-images.png"
// #include "src/frontend-brian/frontend.c"

void FLOW_EndApp() {
    EndApp();
    exit(0);
}

void FLOW_SaveRepsToWorkoutFile() {
    SaveRepsToWorkoutFile();
    FLOW_EndApp();
}

void FLOW_DoEachSet() {
    DoEachSet();
    FLOW_SaveRepsToWorkoutFile();
}

void FLOW_ReadInDataFileAndGetDate() {
    ReadInDataFile();
    GetDate();
    FLOW_DoEachSet();
}

void FLOW_DoesUserWantToStartAWorkoutSession() {
    if (UserWantsToStartAWorkoutSession()) {
        FLOW_ReadInDataFileAndGetDate();
    } else {
        FLOW_EndApp();
    }
}

void FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData() {
    ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    FLOW_DoesUserWantToStartAWorkoutSession();
}

void FLOW_AskForWeightAndCalculateCaloryIntake() {
    AskForWeight();
    CalculateCaloryIntake();
    FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
}

void FLOW_DoesUserWantToAddNewWeight() {
    if (UserWantsToAddNewWeight()) {
        FLOW_AskForWeightAndCalculateCaloryIntake();
    } else {
        FLOW_ShowProgressionViaDataIfEnoughWorkoutsSavedInData();
    }
}

void FLOW_SaveUserOptionsToFile() {
    SaveUserOptionsToFile();
    FLOW_DoesUserWantToAddNewWeight();
}

void FLOW_ShowAndAskOptions() {
    ShowAndAskAndSaveUserOptions();
    FLOW_SaveUserOptionsToFile();
}

void FLOW_DoesUserWantToChangeOptions() {
    if (DoesUserWantToChangeOptions()) {
        FLOW_ShowAndAskOptions();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_WriteChangedWorkoutToFile() {
    WriteChangedWorkoutToFile();
    FLOW_DoesUserWantToChangeOptions();
}

void FLOW_ChangeWorkoutViaAskingUserQuestions() {
    ChangeWorkoutViaAskingQuestions();
    FLOW_WriteChangedWorkoutToFile();
}

void FLOW_DoesUserWantToChangeWorkout() {
    if (DoesUserWantToChangeWorkout()) {
        FLOW_ChangeWorkoutViaAskingUserQuestions();
    } else {
        FLOW_DoesUserWantToChangeOptions();
    }
}

void FLOW_SaveProgramToWorkoutFile() {
    SaveProgramToWorkoutFile();
    FLOW_DoesUserWantToChangeWorkout();
}

void FLOW_CreateDefaultProgram() {
    CreateDefaultProgram();
    FLOW_SaveProgramToWorkoutFile();
}

void FLOW_DisplayIntroduction() {
    DisplayIntroductionMessage();
    FLOW_CreateDefaultProgram();
}

void FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout() {
    // User has been in the application before, so we say welcome back.
    show_welcome_back();

    if (UserWantsToChangeOptionsAndOrWorkout()) {
        FLOW_DoesUserWantToChangeWorkout();
    } else {
        FLOW_DoesUserWantToAddNewWeight();
    }
}

void FLOW_DoesDataFileExist(){
    if (DataFileExists()) {
        FLOW_AskUserIfTheyWantToChangeOptionsAndOrWorkout();
    } else {
        FLOW_DisplayIntroduction();
    }
}

void FLOW_start_app() {
    FLOW_DoesDataFileExist();
}

int main() {
    FLOW_start_app();
    return 0;
}