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
double age;
double height;
double weight;
char gender;
double protein;
double caloriem;
double calorief;

void info(){
  printf("We are almost done, please tell us more about your self, in order for us to make a personilized program for you\n");
  printf("Age:");
  scanf("%lf", &age);
  printf("Height(cm):");
  scanf("%lf", &height);
  printf("Weight(kg):");
  scanf("%lf", &weight);
  gender1:
  printf("Gender(m for male, f for female):");
  scanf(" %c", &gender);
  if (gender != 'm' && gender != 'f'){
    printf("wrong input, please try again\n");
    goto gender1;
  };
  protein = weight * 1.7;
  caloriem = 1.5 * 10 * weight + 6.25 * height - 5 * age + 5;
  calorief = 1.5 * 10 * weight + 6.25 * height - 5 * age - 161;
  //Mifflin-St Jeor formula
};

double program_days;

void program(){
  printf("How many times a week are you willing to train.(it has to be between 3-5)");
  scanf("%lf", &program_days);
};



void needs(){
   printf("you need %lfgram protein daily\n", protein);
  if (gender == 'm')
  {
    printf("you need %lfgram calories daily\n", caloriem);
  }
  else if(gender == 'f'){
    printf("you need %lfgram calories daily\n", calorief);
  }
  else{
    exit(1);
  }
};
