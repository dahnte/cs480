#include <stdio.h>
#include <string.h>

int initGame(void) {
  /* Collects the initial string to start the game */
  printf("Enter the intial starting string\n");
  char initString[10];
  fgets(initString, sizeof(initString), stdin);
  
  /* Small test to see if string was collected properly */
  printf("%s\n", initString);

  return 0;
}

int main() {
  /* Call initGame to start the game */
  initGame();

  return 0;
}
