/* 
 * Author: Dante Cardenas
 * June 14, 2023
 * CS480 - Advanced Topics in Computing
 *
 * Assignment 2 - A Game of Pipes. 
 * objective:
 * 1. player1.c starts the game with user inputted string containing 5 and 7
 * 2. the string should be limited and checked for invalid chars
 * 3. player2.c reponds with editted version removing any substr of 5's or 7's 
 * by any amount
 * 4. the game continues until any player receives a blank string
 * 5. the self declared loser sends a 1 to the other player so they could
 * declare themselves the winner
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 256

/*
 * getNumString.c
 *
 * side-effect: check for invalid chars, remove any amount of
 * consecutive 5 or 7
 * return: a string of characters contianing 5 and 7
 */

/* 
 * checkString.c 
 *
 * return: a string that has been checked for invalid characters
 */

int main() {
  int pipefd[2];
  pid_t pid;
  char buffer[BUFFER_SIZE];

  if(pipe(pipefd) == -1) {
    printf("Error creating pipe");
    return 1;
  }

  pid = fork();

  if(pid < 0) {
    printf("Error with pipe");
    return 2;
  }
  else if(pid > 0) {
    close(pipefd[0]);
    printf("Enter a string consisting of 5 and 7: ");
    fgets(buffer, BUFFER_SIZE, stdin);
    write(pipefd[1], buffer, strlen(buffer)+1);
    close(pipefd[1]);
    wait(pid);
  }
  else {
    close(pipefd[1]);
    read(pipefd[0], buffer, sizeof(buffer));
    printf("Recevied string in pplayer2.c: %s", buffer);
    close(pipefd[0]);
  }
  return 0;
}
