#include <stdlib.h>
#include "Funktioner.c"

int main() {
  DisplayIntroductionMessage();
  node *firstnode = scaningwhy();
  info();
  program();
  to_file(firstnode, age, height, weight, gender, protein, calorie);
  free_space(firstnode);
  printf("open the document \"User_Data\" to view relevant data related to your training journey");
  system("notepad C:\\Users\\parsa\\OneDrive\\Desktop\\P1-fitness\\src\\Parsa\\User_Data");
  return 0;
}





