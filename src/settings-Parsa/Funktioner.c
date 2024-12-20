#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void DisplayIntroductionMessage() {
  printf("Welcome to a new chapter in your life\n");
  printf("Welcome to (APP name)\n");
};

/* reading the input that is in the linked list
 * Initialization:
 * firstnode points to the first node of the list
 * currentnode tracks the current node
 * index tracks the position in the fixed-sized array
 * reading char:
 * getchar reads one char at a time and ends at a newline
 * creating new node:
 * if the list currentnode is empty or the current array is full
 * new node is created with malloc
 * linking nodes:
 * if it is the first node firstnode is the pointer
 * if not the previous node's nextnode is linked to the new node
 * storing char:
 * char is stored in your_why array of the current node and
 * index is incremented
 * this method allows us to handle inputs of any unlimited length
 * without knowing the size in advance
 */
node* readinput(){
  node *firstnode = NULL, *currentnode = NULL;
  int index = 0;
  char c;
  while ((c=getchar()) == '\n') {} // Clearing newlines still present in stdin
  do {
    if (!currentnode || index == SIZE_NO_LIMIT - 1) //The element of the list starts from 0, there for it is important to minus 1.
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
  } while ((c=getchar()) != '\n' && c != EOF);
  return firstnode;
}

/* printing the linked content
 * printinput function goes through every node in the linked list
 * and for each node, it reads and displays the characters stored
 * in its your_why array.
 * start at the first node:
 * he pointer currentnode is initialized to firstnode, the starting
 * point of the linked list.
 * process each node:
 * For every node, the program loops through the your_why array using
 * for (int i = 0; i < SIZE_NO_LIMIT; i++)
 * print char:
 * putchar(currentnode -> your_why[i]) prints one character at a time from the array.
 * move to next node:
 * current = current->nextnode updates the pointer to the next node in the list
 * this repeats until currentnode beacise NULL(end of the list)
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

void freemyguy(node *firstnode){
  node *currentnode = firstnode;
  while (currentnode)
  {
    node *temp = currentnode;
    currentnode = currentnode -> nextnode;
    free(temp);
  }
}

/* Prompts the user for input
 * reads the input into a linked list and
 * prints the input
 */
node* scaningwhy(){
  printf("What is your \"why\", tell us:");
  fflush(stdin);
  return readinput();
}

void CalculateCaloryIntake() {
  //Mifflin-St Jeor formula
  if (gender == 'm') {
    calorie = -5*age + 5;
  } else if (gender == 'f'){
    calorie = -5*age - 161;
  } else {
    printf("%c a\n",gender);
    exit(0);
  }
  calorie += 1.5*10*weight + 6.25*height;
}

void info(){
  printf("We are almost done, please tell us more about your self, in order for us to make a personilized program for you\n");
  printf("Age:");
  scanf("%d", &age);
  printf("Height(cm):");
  float tmp;
  scanf("%f", &tmp);
  height=(int)roundf(tmp); // some may not enter a int as there height, so we use a tmp float that we take a int value of
  printf("Weight(kg):");
  scanf("%f", &tmp);
  weight=(int)tmp;
  gender = ' ';

  // I want to make sure that the user put the right input so i use a loop
  while (gender != 'm' && gender != 'f') {
    printf("Gender(m for male, f for female):");
    scanf(" %c", &gender);
    if (gender != 'm' && gender != 'f'){
      printf("wrong input, please try again\n");
    }
  }
  protein = weight * 1.7;
  CalculateCaloryIntake();
};

/* I use a loop to make sure the app recived the right
 * input from the user as done before
 */
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

// I make a txt document where i put important about the user
void to_file(node *firstnode, int age, int height, int weight, char gender, float protein, float calorie){
  FILE* file = fopen(PATH_TO_DATA "User_Data","w");
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
void ShowAndAskAndSaveUserOptions() {
  DisplayIntroductionMessage();
  user_why = scaningwhy();
  info();
  program();
  to_file(user_why, age, height, weight, gender, protein, calorie);
}

void ReadInDataFile() {
    char *why;
    char genderText[8];
    int days;

    FILE *file = fopen(PATH_TO_DATA "User_Data", "r+");
    if (file == NULL) {
        printf("Error opening file");
        exit(1);
    }
    fscanf(file, " --- Your Very Own Document ---\n");
    fscanf(file, "\n");
    fscanf(file, "\n");
    fscanf(file, "User's Why: ");

    node *firstnode = NULL, *currentnode = NULL;
    int index = 0;
    char c;
    while ((c=fgetc(file)) == '\n') {} // Clearing newlines still present in stdin
    do {
        if (!currentnode || index == SIZE_NO_LIMIT - 1) { //The element of the list starts from 0, there for it is important to minus 1.
            node *node2 = (node *)malloc(sizeof(node));
            if (!node2) {
                printf("Can't allocate memory");
                exit(EXIT_FAILURE);
            }
            node2 -> nextnode = NULL;
            if (!firstnode) {
                firstnode = node2;
            } else {
                currentnode -> nextnode = node2;
            }
            currentnode = node2;
            index = 0;
        }
        currentnode -> your_why[index++] = c;
    } while ((c=fgetc(file)) != '\n' && c != EOF);

    fscanf(file, "Personal Information:\n");
    fscanf(file, "Age: %d\n", &age);
    fscanf(file, "Height: %d cm\n", &height);
    fscanf(file, "Weight: %d kg\n", &weight);
    fscanf(file, "Gender: %s\n", genderText);
    fscanf(file, "\n");
    fscanf(file, "Training:\n");
    fscanf(file, "Days: %d\n", &days);
    fscanf(file, "\n");
    fscanf(file, "Nutritional Needs:\n");
    fscanf(file, "Protein Requirement: %f grams/day\n", &protein);
    fscanf(file, "Calorie Requirement: %f calories/day\n", &calorie);
    if (!strcmp(genderText, "Male")) {
        gender = 'm';
    } else if (!strcmp(genderText, "Female")) {
        gender = 'f';
    }
    if (user_why != NULL) {
        free_space(user_why);
    }
    user_why = firstnode;
}
