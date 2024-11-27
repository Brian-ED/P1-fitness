#include "Funktioner.c"

int main() {
  Introduction();
  node *firstnode = scaningwhy();
  info();
  program();
  needs();
  to_file(firstnode, age, height, weight, gender, protein, calorie);
  free_space(firstnode);
  return 0;
}





