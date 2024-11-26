#include <stdio.h>
#include <stdlib.h>
#define SIZE_NO_LIMIT 16 //the size of the array

void Introduction() {
  printf("Welcome to a new chapter in your life\n");
  printf("Welcome to (APP name)\n");
};

//node in linked list
typedef struct node {
  char your_why[SIZE_NO_LIMIT];
  struct node *nextnode;
} node;

//reading the input that is in the linked list
node* readinput(){
  node *firstnode = NULL, *currentnode = NULL;
  int index = 0;
  char c;
  while ((c=getchar()) != '\n')
  {
    if (!currentnode || index == SIZE_NO_LIMIT)
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

void scaningwhy(){
  printf("What is your \"why\", tell us:");
  node *firstnode = readinput();
  printf("\nYou entered:\n");
  printinput(firstnode);
  freemyguy(firstnode);
}

/*char your_why[250];

void why(){
  printf("What is your \"why\", tell us:");
  scanf("%249[^\n]", your_why);
  fflush(stdin);
  printf("Wow, how inspiring. We wish you the best of luck\n");
};*/
//float tmp;
float age;
float height;
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
