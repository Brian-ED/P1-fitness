#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_NO_LIMIT 16

void Introduction() {
  printf("Welcome to a new chapter in your life\n");
  printf("Welcome to (APP name)\n");
};
typedef struct node {
  char your_why[SIZE_NO_LIMIT];
  struct node *nextnode;
} node;

node* readinput(){
  node *firstnode = NULL, *currentnode = NULL;
  int index = 0;
  char c;
  while ((c=getchar()) == '\n') {} // Clearing newlines still present in stdin
  while ((c=getchar()) != '\n' && c != EOF)
  {
    if (!currentnode || index == SIZE_NO_LIMIT - 1)
    {
      node *node2 = (node *)malloc(sizeof(node));
      if (!node2)
      {
        printf("Can't allocate memory");
        exit(EXIT_FAILURE);
      }
      node2 -> nextnode = NULL;
      if (!firstnode)
      {
        firstnode = node2;
      } else
      {
        currentnode -> nextnode = node2;
      }
      currentnode = node2;
      index = 0;
    }
    currentnode -> your_why[index++] = c;
  }
  return firstnode;
}

void printinput(node *firstnode){
  node *currentnode = firstnode;
  while (currentnode)
  {
    for (int i = 0; i < SIZE_NO_LIMIT; i++)
    {
      putchar(currentnode -> your_why[i]);
    }
    currentnode = currentnode -> nextnode;
  }
  putchar('\n');
}

void freemyguy(node *firstnode){
  node *currentnode = firstnode;
  while (currentnode)
  {
    node *temp = currentnode;
    currentnode = currentnode -> nextnode;
    free(temp);
  }
}

node* scaningwhy(){
  printf("What is your \"why\", tell us:");
  fflush(stdin);
  return readinput();
}


float tmp;
int age;
int height;
int weight;
char gender;
float protein;
float caloriem;
float calorief;
float calorie;

void info(){
  printf("We are almost done, please tell us more about your self, in order for us to make a personilized program for you\n");
  printf("Age:");
  scanf("%d", &age);
  printf("Height(cm):");
  scanf("%f", &tmp);
  height=(int)tmp;
  printf("Weight(kg):");
  scanf("%f", &tmp);
  weight=(int)tmp;
  gender = ' ';
  while (gender != 'm' && gender != 'f')
  {
    printf("Gender(m for male, f for female):");
    scanf(" %c", &gender);
    if (gender != 'm' && gender != 'f'){
      printf("wrong input, please try again\n");
    }
  }
  protein = weight * 1.7;
  caloriem = 1.5 * 10 * weight + 6.25 * height - 5 * age + 5;
  calorief = 1.5 * 10 * weight + 6.25 * height - 5 * age - 161;
};

int program_days;

void program(){
  program_days = 0;
  while (program_days != 3 && program_days != 4 && program_days != 5)
  {
    printf("How many times a week are you willing to train.(it has to be between 3-5)");
    scanf("%d", &program_days);
    if (program_days != 3 && program_days != 4 && program_days != 5){
      printf("wrong input, please try again\n");
    }
  }
};



void needs(){
  if (gender == 'm')
  {
    calorie = caloriem;
  }
  else if(gender == 'f'){
    calorie = calorief;
  }
  else{
    exit(1);
  }
};

void to_file(node *firstnode, int age, int height, int weight, char gender, float protein, float calorie){
  FILE* file = fopen("User_Data","w");
  if (file == NULL) {
    printf("Error opening file\n");
    exit(EXIT_FAILURE);
    }
  fprintf(file, " --- Your Very Own Document ---\n\n\n");
  fprintf(file, "User's Why: ");
  node *currentnode = firstnode;
  while (currentnode) {
    fprintf(file, "%s", currentnode->your_why);
    currentnode = currentnode->nextnode;
   }
  // Write personal details and needs
  fprintf(file, "\nPersonal Information:\n");
  fprintf(file, "Age: %d\nHeight: %d cm\nWeight: %d kg\nGender: %s\n\n", age, height, weight, gender=='m'? "Male" : "Female");
  fprintf(file, "Training:\n");
  fprintf(file, "Days: %d\n", program_days);

  fprintf(file, "\nNutritional Needs:\n");
  fprintf(file, "Protein Requirement: %.f grams/day\n", protein);
  fprintf(file, "Calorie Requirement: %.f calories/day\n", calorie);
  fclose(file);
}
void free_space(node *firstnode){
  freemyguy(firstnode); //frees the memory
}
