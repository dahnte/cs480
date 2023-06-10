/* Written by: Dante Cardenas
   May 27, 2023
   CS480 - Advanced Topics in Computing */

#include <stdio.h>
#include <stdlib.h>

void charWriteFile(const char *, const char *);
void removeNonAlphabeticChar(char * line);
void lineWriteFile(const char *, const char *);

// Reads from r_stream and writes to w_stream character by character
void charWriteFile(const char * file_read, const char * file_write) {
  FILE * r_stream = fopen(file_read, "r"); 
  FILE * w_stream = fopen(file_write, "w");
  char buffer = '\0';

  do {
    buffer = fgetc(r_stream);
    fputc(buffer, w_stream);
  } while (buffer != EOF);  
  
  fclose(r_stream);
  fclose(w_stream);
}

void removeNonAlphabeticChar(char * line) {
  for(int index = 0, temp; line[index] != '\0'; ++index) {
    while(!(line[index] >= 'A' && line[index] <= 'Z') && !(line[index] >= 'a' && line[index] <= 'z') && !(line[index] == '\0')) {
      for(temp = index; line[temp] != '\0'; ++temp) {
        line[temp] = line[temp+1];
      }
      line[temp] = '\0';
    }
  }
}

// Reads from read_stream and writes to write_stream line by line, not including nonalphabetic characters (like '!' and ' ', etc.)
void lineWriteFile(const char * file_read, const char * file_write) {
  FILE * r_stream = fopen(file_read, "r");
  FILE * w_stream = fopen(file_write, "w");
  size_t size = 0;
  char * buffer = NULL;
  size_t bufsize = 32;
 
  do { 
    size = getline(&buffer, &bufsize, r_stream); 
    removeNonAlphabeticChar(buffer);
    printf("Size: %zu\nLine: %s\n", size, buffer);
    fputs(buffer, w_stream);
  } while (*buffer != EOF);

  fclose(r_stream);
  fclose(w_stream);
}

int main() {
  charWriteFile("theRattlinBog.txt", "bogWrite.txt");
  lineWriteFile("bogWrite.txt", "bogWriteNA.txt");
  return 0;
}
