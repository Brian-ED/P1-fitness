#include "Funktioner.c"

int main() {
  Introduction();
  node *firstnode = scaningwhy();
  info();
  program();
  needs();
  to_file(firstnode, age, height, weight, gender, protein, calorie);
  free_space(firstnode);
  printf("open the document \"User_Data\" to view relevant data related to your training journey");
  return 0;
}





