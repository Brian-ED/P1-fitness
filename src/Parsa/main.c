#include "../include_me_in_mains.c"

int main() {
  DisplayIntroductionMessage();
  node *firstnode = scaningwhy();
  info();
  program();
  to_file(firstnode, age, height, weight, gender, protein, calorie);
  free_space(firstnode);
  ShowAndAskAndSaveUserOptions()
  return 0;
}





