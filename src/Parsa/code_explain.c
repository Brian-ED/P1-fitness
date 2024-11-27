#include <stdio.h>
#include <stdlib.h>
#define SIZE_NO_LIMIT 16 //the size of character array in each linked list node

void Introduction() {
  printf("Welcome to a new chapter in your life\n");
  printf("Welcome to (APP name)\n");
};

/*struct: your_why = fixed-size array for storing some of input
nextnode = pointer to the next node in the linked list
this struct enables efficient memory management because of the fixed-sized array
*/
typedef struct node {
  char your_why[SIZE_NO_LIMIT];
  struct node *nextnode;
} node;

/*reading the input that is in the linked list
Initialization:
firstnode points to the first node of the list
currentnode tracks the current node
index tracks the position in the fixed-sized array
reading char:
getchar reads one char at a time and ends at a newline
creating new node:
if the list currentnode is empty or the current array is full
new node is created with malloc
linking nodes:
if it is the first node firstnode is the pointer
if not the previous node's nextnode is linked to the new node
storing char:
char is stored in your_why array of the current node and
index is incremented
this method allows us to handle inputs of any unlimited length
without knowing the size in advance
*/
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

/*printing the linked content
printinput function goes through every node in the linked list
and for each node, it reads and displays the characters stored
in its your_why array.
start at the first node:
he pointer currentnode is initialized to firstnode, the starting
point of the linked list.
process each node:
For every node, the program loops through the your_why array using
for (int i = 0; i < SIZE_NO_LIMIT; i++)
print char:
putchar(currentnode -> your_why[i]) prints one character at a time from the array.
move to next node:
current = current->nextnode updates the pointer to the next node in the list
this repeats until currentnode beacise NULL(end of the list)
*/

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
//Iteratively frees each node of the linked list.
void freemyguy(node *firstnode){
  node *currentnode = firstnode;
  while (currentnode)
  {
    node *temp = currentnode;
    currentnode = currentnode -> nextnode;
    free(temp);
  }
}
/*Prompts the user for input
reads the input into a linked list and
prints the input
*/
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
float tmp; //tmp float that is used for memory efficiency
float age;
int height;
int weight;
char gender;
float protein;
float caloriem;
float calorief;

void info(){
  printf("We are almost done, please tell us more about your self, in order for us to make a personilized program for you\n");
  printf("Age:");
  scanf("%f", &age);
  printf("Height(cm):");
  //scanf("%f", &height);
  scanf("%f", &tmp);
  height=(int)tmp;//some may not enter a int as there height. so for efficiency we use a tmp float that we take a int value of
  printf("Weight(kg):");
  //scanf("%f", &weight);
  scanf("%f", &tmp);
  weight=(int)tmp;//some may not enter a int as there weight. so for efficiency we use a tmp float that we take a int value of
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
