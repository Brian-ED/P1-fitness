#include <stdlib.h>

int week_number = -1;
int day_of_the_week = -1;
int age;
int height;
int weight;
char gender;
float protein;
float calorie;
int program_days;

#include "Funktioner.c"
#include "../utils.c"

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





