#include <stdio.h>
#include <stdlib.h>
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

void view_matrix(int index_matrix, int spaces) {
  int width = getWidth(index_matrix);
  int height = getHeight(index_matrix);

  for (int vertical = 0; vertical < height * 2 + 1; vertical++) {

    for (int space = 0; space < spaces; space++) {
      printf(" ");
    }

    for (int horizontal = 0; horizontal < (width + 1) * 4; horizontal++) {

      if (horizontal == 4) {
        if (vertical % 2 == 0) {
          printf("  ");
        } else {
          printf(" ");
        }
      }

      if (vertical % 2 == 1 && horizontal % 4 == 0 && horizontal != 0) {
        printf("%-4d", matrix[index_matrix][vertical / 2][horizontal / 4 - 1]);
      } else if (horizontal == 1) {
        if (vertical == 0) {
          printf("┌");
        } else if (vertical == height * 2) {
          printf("└");
        } else {
          printf("│");
        }
      } else if (horizontal == (width + 1) * 4 - 1 ) {
        if (vertical == 0) {
          printf("┐");
        } else if (vertical == height * 2) {
          printf("┘");
        } else {
          printf("│");
        }
      } else if(vertical % 2 != 1 || horizontal == 0 || horizontal == 2 || horizontal == 3) {
        printf(" ");
      }
    }

    printf("\n");

  }

}

void view_operation(char operator) {
  int width1 = getWidth(0);
  int width2 = getWidth(1);
  int avgWidth = (width1 + width2) / 2;
  int diffWidth1 = width2 - width1;
  int diffWidth2 = width1 - width2;
  int biggestWidth;
  if (width1 > width2) {
    biggestWidth = width1;
  } else {
    biggestWidth = width2;
  }
  int diffResult = biggestWidth - getWidth(2);

  //print first matrix

  view_matrix(0 ,diffWidth1 * 2);


  //print operator

  for (int i = 0; i < 3; i++) {
    printf(" ");
  }
  for (int j = 0; j < biggestWidth * 2; j++) {
    printf(" ");
  }

  printf("%c\n", operator);


  //print second  matrix 

  view_matrix(1, diffWidth2 * 2);


  //print equal sign

  for (int i = 0; i < 3; i++) {
    printf(" ");
  }
  for (int j = 0; j < biggestWidth * 2; j++) {
    printf(" ");
  }

  printf("=\n");


  //print result matrix


  view_matrix(2, diffResult * 2);

}

void add_values_matrix(int index_matrix) {
  int height = getHeight(index_matrix);
  int width = getWidth(index_matrix);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int value;
      scanf(" %d", &value);
      matrix[index_matrix][i][j] = value; 
    }
  }
}

void calculate_add() {
  int height = getHeight(0);
  int width = getWidth(0);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int value = matrix[0][i][j] + matrix[1][i][j];
      matrix[2][i][j] = value;
    }
  }
}

void add_matrix() {
  int height = 0;
  int width = 0;
  printf("What is the size of the the matrices? (n x m) = ");
  scanf(" %d %d", &height, &width);
  printf("\n");

  if (height > 0 && width > 0) {

    matrix_sizes[0][0] = height;
    matrix_sizes[0][1] = width;
    matrix_sizes[1][0] = height;
    matrix_sizes[1][1] = width;
    matrix_sizes[2][0] = height;
    matrix_sizes[2][1] = width;

    printf("Values of the first matrix\n");
    add_values_matrix(0);
    printf("Values of the second matrix\n");
    add_values_matrix(1);

    calculate_add();

  } else {
    printf("Invalid input, please try again.\n\n");
    add_matrix();
  }
}

void calculate_multiply() {
  int height = getHeight(2);
  int width = getWidth(2);

  for (int result_vertical = 0; result_vertical < height; result_vertical++) {
    for (int result_horizontal = 0; result_horizontal < width; result_horizontal++) {
      int value = 0;

      // Calculate value

      for (int i = 0; i < getWidth(0); i++) {
        value+= matrix[0][result_vertical][i] * matrix[1][i][result_horizontal];
      }



      //Put it into result matrix

      matrix[2][result_vertical][result_horizontal] = value;

    }
  }
}

void multiply_matrix() {
  int height1 = 0;
  int width1 = 0;
  int height2 = 0;
  int width2 = 0;
  printf("What is the size of the the matrices? n x m and m x p = ");
  scanf(" %d %d %d %d", &height1, &width1, &height2, &width2);
  printf("\n");

  if (width1 == height2 && height1 > 0 && width1 > 0 && height2 > 0 && width2 > 0) {

    matrix_sizes[0][0] = height1;
    matrix_sizes[0][1] = width1;
    matrix_sizes[1][0] = height2;
    matrix_sizes[1][1] = width2;
    matrix_sizes[2][0] = height1;
    matrix_sizes[2][1] = width2;

    printf("Values of the first matrix\n");
    add_values_matrix(0);
    printf("Values of the second matrix\n");
    add_values_matrix(1);

    calculate_multiply();

  } else {
    printf("Invalid input, please try again.\n\n");
    add_matrix();
  }

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
  ask_action();
  view_operation('*');
  // loop();
  return 0;
}
