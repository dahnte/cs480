#include <stdio.h>

void swapChar(char * a, char * b) {
  *a = 'L';
  *b = 'T';
}

int main() {
  char x = 'A';
  char y = 'B';

  printf("x: %c\n", x);
  printf("y: %c\n", y);

  swapChar(&x, &y);

  printf("after swapChar x: %c\n", x);
  printf("after swapChar y: %c\n", y);


  return 0;
}
