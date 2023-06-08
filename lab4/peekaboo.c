#include <stdio.h>

int main() {

  fprintf(stdout, "Peekaboo! I see you!\n");
  fflush(stdout);
  sleep(10);

  return 0; 
}
