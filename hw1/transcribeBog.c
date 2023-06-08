/* Written by: Dante Cardenas
   May 27, 2023
   CS480 - Advanced Topics in Computing */

#include <stdio.h>
#include <stdlib.h>

void charWriteFile(const char*, const char*);
void removeArr(char*, int, int, int*);
void removeNonAlphabetic(char*, int);
void lineWriteFile(const char*, const char*);

// Reads from r_stream and writes to w_stream character by character
void charWriteFile(const char *file_read, const char *file_write) {
  FILE *r_stream = fopen(file_read, "r"); 
  FILE *w_stream = fopen(file_write, "w");
  char buffer;

  do {
    buffer = fgetc(r_stream);
    fputc(buffer, w_stream);
  } while (buffer != EOF);  
  
  fclose(r_stream);
  fclose(w_stream);
}

// Copies over remainaing elements in array to current spot
void removeArr(char *arr, int index, int count, int *size) {
  index = index - (count-1);
  do {
     arr[index] = arr[index+(count+1)];
     index++;
  } while (arr[index+(count+1)] != '\0');
  //*size = *size-count;
}

// Reads through the string until a non-alphabetic char is found
void removeNonAlphabet(char *line, int size) {
  int count;
  for (int i = 0; i < size-1; i++) {
    while (line[i] < 'A' || line[i] > 'Z' && line[i] < 'a' || line[i] > 'z') {
        count++;
        i++;
    }
  removeArr(line, i, count, &size);
  }
}

// Reads from read_stream and writes to write_stream line by line, not including nonalphabetic characters (like '!' and ' ', etc.)
void lineWriteFile(const char *file_read, const char *file_write) {
  FILE *r_stream = fopen(file_read, "r");
  FILE *w_stream = fopen(file_write, "w");
  char buffer[32];
  char *b = buffer;
  //size_t size = 32;
  size_t line;
 
  do { 
  line = getline(&b, (size_t)&buffer, r_stream); 
  removeNonAlphabet(b, line);
  printf("Size: %zu\nLine: %s\n", line, b);
  fputs(b, w_stream);
  } while (*b != EOF);

  fclose(r_stream);
  fclose(w_stream);
}

int main() {
  charWriteFile("theRattlinBog.txt", "bogWrite.txt");
  lineWriteFile("bogWrite.txt", "bogWriteNA.txt");
  return 0;
}
