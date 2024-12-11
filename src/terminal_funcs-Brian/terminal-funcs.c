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

void ChangeWorkoutViaAskingQuestions() {

    // How many days a week
    program(); // Also calculates calories needed and protein goals

    // TODO more questions
}
