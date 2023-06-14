#include <stdio.h>

void printString(char * arr, int arrSize, int index) {
  int i = 0;
  while(i < index) {
    printf("%c", arr[i]);
    i++;
  }
  printf("[%c]", arr[index]);
  index += 1;
  while(index < arrSize) {
    printf("%c", arr[index]);
    index++;
  } 
}

int main() {
  float x = 6;
  float d;
  long a;
  double b;
  int c;
  char e;
  char t = 'A';
  int sizeArr = 20;
  int index = 9;
  char myStr[sizeArr];
  int testArr[24];
  int sizeCheck = *(&testArr+1)-testArr;
  char myStr1[sizeArr - 8];

  /* Checking array size using pointer arithmetic */
  printf("Size check: %d\n", sizeCheck);
  printf("testArr address: %p\n", &testArr);
  printf("Char 'A' value: %d\n", (int)t);

  /* Decimal precission */
  printf("Hello World!\n%.2f\n", x);

  /* for loop */
  int i = 0;
  while (i <= 6) {
    printf("%d\n", i);
    i++;
  }

  printf("%d, %d, %d, %lu, %lu\n", sizeof(d), sizeof(a) ,sizeof(b), sizeof(c), sizeof(e));
  printf("%d\n", x > d);
  printf("%d\n", x < d);

  /* Ternary if...else operator */
  (x > d) ? printf("Greater than 'd'\n") : printf("Less than 'd'\n");

  /* Testing scanf function */
  printf("Enter string less than %d characters: ", sizeArr);
  scanf("%s", myStr);
  printf("\nYour String was: ");
  printString(myStr, sizeArr, index); 
  //printf("Your string was: %s\nPrinting at index %d: %c\n", myStr, index, myStr[index]);

  printf("\nEnter a string less than %d characters: ", sizeArr - 8);
  scanf("%s", myStr1);
  printf("\nYour string was: %s\n", myStr1);

  return 0;
}
