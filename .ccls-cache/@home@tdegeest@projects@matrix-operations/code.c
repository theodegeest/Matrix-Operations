#include <stdio.h>
#include <stdlib.h>
#define MAX_MATRIX 4
#define MAX_SIZE 10
#define DEFAULT_SIZE 3


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

int matrix[MAX_MATRIX][MAX_SIZE][MAX_SIZE];
int matrix_sizes[MAX_MATRIX][2];
int temp_matrix[MAX_SIZE][MAX_SIZE];


/* Initializing functions */

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
      matrix_sizes[index][inner] = DEFAULT_SIZE;
    }
  }
}

void init_temp() {
  for (int outer = 0; outer < MAX_SIZE; outer++) {
    for (int inner = 0; inner < MAX_SIZE; inner++) {
      temp_matrix[outer][inner] = 0;
    }
  }
}


/* Getters */

int getHeight(int index_matrix) {
  return matrix_sizes[index_matrix][0];
}

int getWidth(int index_matrix) {
  return matrix_sizes[index_matrix][1];
}


/* Printing functions */

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

void view_scalair(int index_matrix, int spaces) {

  printf("\n");
  if (matrix[1][0][0] > 99) {
    printf("  ");
  } else {
    printf("   ");
  }
  for (int space = 0; space < spaces; space++) {
    printf(" ");
  }
  printf("%-4d\n\n", matrix[1][0][0]);
}

void view_transpose() {
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

  printf("\n");

  for (int i = 0; i < 3; i++) {
    printf(" ");
  }
  for (int j = 0; j < biggestWidth * 2; j++) {
    printf(" ");
  }

  printf("T\n\n");

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

void view_operation(char operator, int scalair) {
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

  if (scalair) {
    view_scalair(1 ,biggestWidth * 2);
  } else {
    view_matrix(1, diffWidth2 * 2);
  }

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


/* Memory funtions */
void memory_view() {

  for (int index = 0; index < MAX_MATRIX; index++) {
    printf("Address %d: %d x %d matrix\n", index, getHeight(index), getWidth(index));
    view_matrix(index, 0);
    printf("\n");
  }
}

void memory_add() {
  int address = -1;
  char type;
  printf("Which address would you like to overwrite and what type is it? size, (m) matrix/ (s) scalair = ");
  scanf(" %d %c", &address, &type);
  printf("\n");

  if (address >= 0 && address < MAX_MATRIX) {
    if (type == 'm') {

      int height = 0;
      int width = 0;
      printf("What is the size of the the matrix? (n x m) = ");
      scanf(" %d %d", &height, &width);
      printf("\n");

      if (height > 0 && width > 0 && height < MAX_SIZE && width < MAX_SIZE) {

        matrix_sizes[address][0] = height;
        matrix_sizes[address][1] = width;

        printf("What are the values of the matrix?\n");

        for (int i = 0; i < height; i++) {
          for (int j = 0; j < width; j++) {
            int value;
            scanf(" %d", &value);
            matrix[address][i][j] = value; 
          }
        }

        printf("Memory address %d has been overwritten with:\n", address);
        view_matrix(address, 0);
      } else {
        printf("Unknown values, please try again\n");
        memory_add();
      }




    } else if (type == 's') {
      printf("What is the value of the scalair?\n");

    } else {
      printf("Unknown values, please try again\n");
      memory_add();
    }
  } else {
    printf("Unknown values, please try again\n");
    memory_add();
  }
}

void memory_remove() {
  int address = -1;
  printf("Which address would you like to remove? ");
  scanf(" %d", &address);
  printf("\n");

  if (address >= 0 && address < MAX_MATRIX) {

    int height = getHeight(address);
    int width = getWidth(address);

    for (int i = 0; i < height; i++) {
      for (int j = 0; j < width; j++) {
        matrix[address][i][j] = 0; 
      }
    }

    matrix_sizes[address][0] = DEFAULT_SIZE;
    matrix_sizes[address][1] = DEFAULT_SIZE;

  } else {
    printf("Unknown values, please try again\n");
    memory_add();
  }

}

void memory_swap() {
  int address1 = -1;
  int address2 = -1;
  printf("Which addresses would you like to swap? \n");
  scanf(" %d %d", &address1, &address2);
  printf("\n");

  if (address1 != address2 && address1 >= 0 && address2 >= 0) {
    //swap 1 to temp_matrix

    int height = getHeight(address1);
    int width = getWidth(address1);
    for (int outer = 0; outer < height; outer++) {
      for (int inner = 0; inner < width; inner++) {
        temp_matrix[outer][inner] = matrix[address1][outer][inner];
      }
    }


    // swap 2 to 1

    height = getHeight(address2);
    width = getWidth(address2);
    for (int outer = 0; outer < height; outer++) {
      for (int inner = 0; inner < width; inner++) {
        matrix[address1][outer][inner] = matrix[address2][outer][inner];
      }
    }


    //swap temp_matrix to 2

    height = getHeight(address1);
    width = getWidth(address1);
    for (int outer = 0; outer < height; outer++) {
      for (int inner = 0; inner < width; inner++) {
        matrix[address2][outer][inner] = temp_matrix[outer][inner];
      }
    }

    //swap sizes
    int temp_size_height = getHeight(address1);
    int temp_size_width = getWidth(address1);
    matrix_sizes[address1][0] = getHeight(address2);
    matrix_sizes[address1][1] = getWidth(address2);
    matrix_sizes[address2][0] = temp_size_height;
    matrix_sizes[address2][1] = temp_size_width;

    // give user feedback

    memory_view();

  } else {
    printf("Unknown values, please try again\n");
    memory_swap();
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
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
////////////////////////////////////////////////////////////////////////////////////////////////////

/* Calculate funtions */

void calculate_add(int x, int y, int output) {
  int height = getHeight(x);
  int width = getWidth(x);

  matrix_sizes[output][0] = height;
  matrix_sizes[output][1] = width;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int value = matrix[x][i][j] + matrix[y][i][j];
      matrix[output][i][j] = value;
    }
  }
}

void action_add() {

  int x = -1;
  int y = -1;
  int output;
  printf("What matrices would you like to add up and where do you want to store it? x y output = ");
  scanf(" %d %d %d", &x, &y, &output);

  if (x >= 0 && y >= 0 && getWidth(x) == getWidth(y) && getHeight(x) == getHeight(y)) {
    calculate_add(x, y, output);
  } else {
    action_add();
  }
}

void calculate_multiply(int x, int y, int output) {

  int height = getHeight(x);
  int width = getWidth(y);

  matrix_sizes[output][0] = height;
  matrix_sizes[output][1] = width;

  int iter = getWidth(x);

  for (int result_vertical = 0; result_vertical < height; result_vertical++) {
    for (int result_horizontal = 0; result_horizontal < width; result_horizontal++) {
      int value = 0;

      // Calculate value

      for (int i = 0; i < iter; i++) {
        value+= matrix[x][result_vertical][i] * matrix[y][i][result_horizontal];
      }



      //Put it into result matrix

      matrix[output][result_vertical][result_horizontal] = value;

    }
  }
}

void action_multiply() {

  int x = -1;
  int y = -1;
  int output;
  printf("What matrices would you like to multiply and where do you want to store it? x y output = ");
  scanf(" %d %d %d", &x, &y, &output);

  if (x >= 0 && y >= 0 && getWidth(x) == getHeight(y) && getWidth(x) > 0 && getWidth(y) > 0 && getHeight(x) > 0 && getHeight(y) > 0) {
    calculate_multiply(x, y, output);
  } else {
    action_multiply();
  }
}


void calculate_multiply_scalair() {
  int height = getHeight(0);
  int width = getWidth(0);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int value = matrix[0][i][j] * matrix[1][0][0];
      matrix[2][i][j] = value;
    }
  }
}

void action_multiply_scalair() {
  int height1 = 0;
  int width1 = 0;
  printf("What is the size of the the matrix? n x m = ");
  scanf(" %d %d", &height1, &width1);
  printf("\n");

  if (height1 > 0 && width1 > 0) {

    matrix_sizes[0][0] = height1;
    matrix_sizes[0][1] = width1;
    matrix_sizes[1][0] = 1;
    matrix_sizes[1][1] = 1;
    matrix_sizes[2][0] = height1;
    matrix_sizes[2][1] = width1;

    printf("Values of the matrix\n");
    add_values_matrix(0);
    printf("Value of the scalair\n");
    add_values_matrix(1);

    calculate_multiply_scalair();

    view_operation('*', 1);

  } else {
    printf("Invalid input, please try again.\n\n");
    action_multiply_scalair();
  }

}

void calculate_transpose() {
  int height = getHeight(0);
  int width = getWidth(0);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      int value = matrix[0][i][j];
      matrix[2][j][i] = value;
    }
  }
}

void action_transpose() {
  int height1 = 0;
  int width1 = 0;
  printf("What is the size of the the matrix? n x m = ");
  scanf(" %d %d", &height1, &width1);
  printf("\n");

  if (height1 > 0 && width1 > 0) {

    matrix_sizes[0][0] = height1;
    matrix_sizes[0][1] = width1;
    matrix_sizes[2][0] = width1;
    matrix_sizes[2][1] = height1;

    printf("Values of the matrix\n");
    add_values_matrix(0);

    calculate_transpose();

    view_transpose();

  } else {
    printf("Invalid input, please try again.\n\n");
    action_transpose();
  }

}



void ask_action() {
  char input;
  printf("Memory: (a) Add, (r) Remove, (s) Swap, (v) View\n");
  printf("Actions: (A) Add, (M) Multiply, (S) Multiply with scalair, (T) Transpose, (q) Quit\n");
  scanf(" %c", &input);
  switch (input) {
    case 'a':
      memory_add();
      break;
    case 'r':
      memory_remove();
      break;
    case 's':
      memory_swap();
      break;
    case 'v':
      memory_view();
      break;
    case 'A':
      action_add();
      break;
    case 'M':
      action_multiply();
      break;
    case 'S':
      action_multiply_scalair();
      break;
    case 'T':
      action_transpose();
      break;
    case 'q':
      run = 0;
      break;
    default:
      printf("Unknown action, please try again.\n");
      ask_action();
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
  // ask_action();
  loop();
  return 0;
}
