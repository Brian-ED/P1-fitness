#include <stdio.h>
#include <stdlib.h>
void Introduction() {
  printf("Welcome to a new chapter in your life\n");
  printf("Welcome to (APP name)\n");
};

char your_why[250];

void why(){
  printf("What is your \"why\", tell us:");
  scanf("%249[^\n]", your_why);
  fflush(stdin);
  printf("Wow, how inspiring. We wish you the best of luck\n");
};
//float tmp;
float age;
int height;
float weight;
char gender;
float protein;
float caloriem;
float calorief;

void info(){
  printf("We are almost done, please tell us more about your self, in order for us to make a personilized program for you\n");
  printf("Age:");
  scanf("%f", &age);
  printf("Height(cm):");
  scanf("%f", &height);
  /*scanf("%f", &tmp);
  height=(int)tmp;
  */
  printf("Weight(kg):");
  scanf("%f", &weight);
  gender = ' ';
  while (gender != 'm' && gender != 'f')
  {
    printf("Gender(m for male, f for female):");
    scanf(" %c", &gender);
    if (gender != 'm' && gender != 'f'){
      printf("wrong input, please try again\n");
    }
  }

  /*gender1:
  printf("Gender(m for male, f for female):");
  scanf(" %c", &gender);
  if (gender != 'm' && gender != 'f'){
    printf("wrong input, please try again\n");
    goto gender1;
  };
  */
  protein = weight * 1.7;
  caloriem = 1.5 * 10 * weight + 6.25 * height - 5 * age + 5;
  calorief = 1.5 * 10 * weight + 6.25 * height - 5 * age - 161;
  //Mifflin-St Jeor formula
};

int program_days;

void program(){
  printf("How many times a week are you willing to train.(it has to be between 3-5)");
  scanf("%d", &program_days);
};



void needs(){
   printf("you need %fgram protein daily\n", protein);
  if (gender == 'm')
  {
    printf("you need %fgram calories daily\n", caloriem);
  }
  else if(gender == 'f'){
    printf("you need %fgram calories daily\n", calorief);
  }
  else{
    exit(1);
  }
};
