#include <stdio.h>

void theFunc(char * line) {
   for (int i = 0, j; line[i] != '\0'; ++i) {
      // enter the loop if the character is not an alphabet
      // and not the null character
      printf("1st loop: %s\n", line);

      while (!(line[i] >= 'a' && line[i] <= 'z') && !(line[i] >= 'A' && line[i] <= 'Z') && !(line[i] == '\0')) {
         printf("2nd loop: %s\n", line);
            for (j = i; line[j] != '\0'; ++j) {
            // if jth element of line is not an alphabet,
            // assign the value of (j+1)th element to the jth element
            printf("3rd loop: %s\n", line);

              line[j] = line[j + 1];
            }
         line[j] = '\0';
      }
   }
}

int main() {
  FILE * fstream = fopen("../hw1/bogWrite.txt", "r");
  char * buffer = NULL;
  size_t bufsize = 40;
   
  do{
    getline(&buffer, &bufsize, fstream);
    //printf("Before: %s\n", buffer);
    theFunc(buffer);
    //printf("After: %s\n", buffer);
} while (*buffer != EOF);

  return 0;
}
