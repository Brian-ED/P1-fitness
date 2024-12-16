#include <stdlib.h>
#include "Funktioner.c"
#include "../utils.c"

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





