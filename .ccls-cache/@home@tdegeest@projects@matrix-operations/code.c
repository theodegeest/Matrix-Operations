#include <stdio.h>
#define MAX_MATRIX 2
#define MAX_SIZE 10

/*   n x m => n height, m width
 *
 *   ┌             ┐     ┌             ┐     ┌             ┐
 *   │  1   2   3  │     │  1   2   3  │     │  2   4   6  │
 *   │             │     │             │     │             │
 *   │  4   5   6  │  +  │  4   5   6  │  =  │  8   10  12 │  
 *   │             │     │             │     │             │
 *   │  7   8   9  │     │  7   8   9  │     │  14  16  18 │
 *   └             ┘     └             ┘     └             ┘
 *
 */


int run = 1;
int nbr_matrix = 2;
int current_size = 0;

int matrix[MAX_MATRIX + 1][MAX_SIZE][MAX_SIZE];
int matrix_sizes[MAX_MATRIX + 1][2];

void init_matrices() {
  for (int index = 0; index < MAX_MATRIX + 1; index++) {
    for (int outer = 0; outer < MAX_SIZE; outer++) {
      for (int inner = 0; inner < MAX_SIZE; inner++) {
        matrix[index][outer][inner] = 0;
      }
    }
  }
}

void init_sizes() {
  for (int index = 0; index < MAX_MATRIX + 1; index++) {
    for (int inner = 0; inner < 2; inner++) {
      matrix_sizes[index][inner] = 3;
    }
  }
}

int getHeight(int index_matrix) {
  return matrix_sizes[index_matrix][0];
}

int getWidth(int index_matrix) {
  return matrix_sizes[index_matrix][1];
}

void view_matrix(int index_matrix) {
  for (int outer = 0; outer < current_size; outer++) {
    for (int inner = 0; inner < current_size; inner++) {

    }
  }
}

void view_operation(char operation) {
  int highest_heigth = 0;
  for (int i = 0; i < nbr_matrix; i++) {
    int height = getHeight(i);
    if (height > highest_heigth) {
      highest_heigth = height;
    }
  }

  int matrix1_width = getWidth(0);
  printf("%d\n", matrix1_width);

  for (int vertical = 0; vertical < highest_heigth * 2 + 1; vertical++) {

    for (int matrix1 = 0; matrix1 < (matrix1_width + 1) * 4; matrix1++) {
      if (vertical % 2 == 1 && matrix1 % 4 == 0 && matrix1 != 0) {
        printf("X");
      } else if (matrix1 == 1 || matrix1 == 15) {
        printf("│");
      } else {
        printf(" ");
      }
    }

    printf("\n");

  }
}

void add_values_matrix(int index_matrix) {
  printf("%d\n", index_matrix);
}

void add_matrix() {
  printf("How many matrices would you like to add? ");
  scanf(" %d", &nbr_matrix);
  printf("\n");

  if (nbr_matrix > 1 && nbr_matrix <= MAX_MATRIX) {
    for (int i = 0; i < nbr_matrix; i++) {
      add_values_matrix(i);
    }
  } else {
    printf("Invalid input, please try again.\n\n");
    add_matrix();
  }
}

void multiply_matrix() {

}


void ask_action() {
  char input;
  printf("Action: (a) Add, (m) Multiply, ...\n");
  scanf(" %c", &input);
  switch (input) {
    case 'a':
      add_matrix();
      break;
    case 'm':
      multiply_matrix();
      break;
    default:
      printf("Unknown action, please try again.\n");
      break;
  }
}

void loop() {
  while (run) {
    ask_action();
  }
}

int main (int argc, char *argv[])
{
  init_matrices();
  init_sizes();
  view_operation('x');
  loop();
  return 0;
}
