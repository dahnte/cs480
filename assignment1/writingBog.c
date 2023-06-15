/* 
 * Author: Dante Cardenas
 * June 12, 2023
 * CS480 - Advanced Topics in Computing
 *
 * File contains my solution to assignment 1. Each function is preceded with a comment that exaplains its process.
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

/* Function: void charWriteFile
 * ----------------------------
 * file_read: Name of file to be read from
 * file_write: Name of file to be written to
 * 
 * side-effect: Reads from file_read, character by character, and writes into file_write, character by character. Writes to terminal if successful.
*/

void charWriteFile(const char *file_read, const char *file_write) {
  FILE *r_stream = fopen(file_read, "r"); 
  FILE *w_stream = fopen(file_write, "w");
  char buffer = '\0';

  while((buffer = fgetc(r_stream)) != EOF) {
    fputc(buffer, w_stream);
  }  
  if (fclose(r_stream) == 0 && fclose(w_stream) == 0) {
    printf("Wrote to %s successfully!\n", file_write);
  }
}

/* Function: void removeNonAlphabetChar
 * ------------------------------------
 * line: A pointer to the buffer holding current line read from file
 * 
 * side-effect: Reads line character by character and removes non-alphabetical characters by copying over the next alphbetical character. Runs until it reaches the '\0' delim.
*/

void removeNonAlphabetChar(char * line) {
   for (int i = 0, j; line[i] != '\0'; ++i) { 
    while ((line[i] < 'A' || line[i] > 'Z') 
      && (line[i] < 'a' || line[i] > 'z') 
      && (line[i] != '\0' && line[i] != '\n') ) {
      for (j = i; line[j] != '\0'; ++j) {
        line[j] = line[j + 1];
      }
      line[j] = '\0';
    }
  }
}

/* Function: void lineWriteFile
 * ----------------------------
 * file_read: Name of file to be read from
 * file_write: Name of file to be written to
 * 
 * side-effect: Reads from file_read line by line until failure or EOF condition. 
 * While getline is active, the current buffer is then passed to removeNonAlphabetChar. 
 * Once the buffer has been processed it is then written to file_write. Writes to terminal if sucessful.
*/

void lineWriteFile(const char *file_read, const char *file_write) {
  FILE *r_stream = fopen(file_read, "r");
  FILE *w_stream = fopen(file_write, "w");
  size_t buffer_size = 0;
  char *buffer = NULL;

  while(getline(&buffer, &buffer_size, r_stream) != -1) {
    removeNonAlphabetChar(buffer);
    fputs(buffer, w_stream);
  }
  if (fclose(r_stream) == 0 && fclose(w_stream) == 0) {
    printf("Wrote to %s successfully!\n", file_write);
  }
}

/* Function: int diffFile
   ----------------------
   file_comp1: Name of file to be compared to file_comp2
   file_comp2: Name of file to be compared to file_comp1
   
   return: Returns an int representing the number of characters that are different between two files
*/ 

int diffFile(const char *file_comp1, const char *file_comp2) {
  FILE *r_stream1 = fopen(file_comp1, "r");
  FILE *r_stream2 = fopen(file_comp2, "r");
  char *diff_prompt = NULL, *buffer1 = NULL, *buffer2 = NULL;
  int counter = 0;
  //sprintf(diff_prompt, "diff %s %s", file_comp1, file_comp2);
  //FILE * prompt = popen(diff_prompt, "w");

  if((fclose(r_stream1) == 0) && (fclose(r_stream2) == 0)) {
    printf("Successfully compared %s and %s\n", file_comp1, file_comp2);
  }
  //pclose(prompt); 
}

int upperCaseCount(const char *file_read) {
  FILE *r_stream = fopen(file_read, "r");
  char buffer = '\0';
  int counter = 0;

  while((buffer = fgetc(r_stream)) != EOF) {
    if(isupper(buffer)) {
      counter++;
    }
  }  

  if(fclose(r_stream) == 0) {
    printf("Successfully counted upper case!\n");
  }
  return counter;
}

int main() {
  printf("charWriteFile: ");
  charWriteFile("bogLyrics.txt", "bogWrite.txt");

  printf("lineWriteFile: ");
  lineWriteFile("bogWrite.txt", "bogWriteNA.txt");

  printf("diffFile: ");
  diffFile("bogLyrics.txt", "bogWrite.txt");
  
  printf("upperCaseCount: %d\n", upperCaseCount("bogWriteNA.txt"));
  return 0;
}
