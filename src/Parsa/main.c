#include <stdlib.h>
#include "Funktioner.c"

int main() {
  Introduction();
  node *firstnode = scaningwhy();
  info();
  program();
  needs();
  to_file(firstnode, age, height, weight, gender2, protein, calorie);
  free_space(firstnode);
  printf("open the document \"User_Data\" to view relevant data related to your training journey");
  system("notepad C:\\Users\\parsa\\OneDrive\\Desktop\\P1-fitness\\src\\Parsa\\User_Data");
  return 0;
}





