// ------------------ //
// Global definitions //
// ------------------ //

//the size of character array in each linked list node
#define SIZE_NO_LIMIT 16

// ------------------- //
// Global struct types //
// ------------------- //

/* struct: your_why = fixed-size array for storing some of input
 * nextnode = pointer to the next node in the linked list
 * this struct enables efficient memory management because of the fixed-sized array
 */
typedef struct node {
  char your_why[SIZE_NO_LIMIT];
  struct node *nextnode;
} node;

// ---------------- //
// Global variables //
// ---------------- //
node *user_why;
int week_number = -1;
int day_of_the_week = -1;
int age;
int height;
int weight;
char gender;
float protein;
float calorie;
int program_days;

// --------------- //
// Global includes //
// --------------- //
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// --------------------------- //
// project files include order //
// --------------------------- //
#include "utils.c"
#include "log_regression/log_regression.c"
#include "exercise_management/read_from_list.c"
#include "settings/Funktioner.c"
#include "welcome_back/welcome_back.c"
#include "terminal_funcs/terminal-funcs.c"
