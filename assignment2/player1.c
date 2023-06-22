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

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 256

/* 
 * checkString
 *
 *  return: 1 if string is valid, 0 if otherwise
 */

int checkString(char *string) {
	int check = 0;
	for(int i = 0; string[i] != '\0' && string[i] != '\n'; i++) { /* fgets adds a '\n'*/
		if(string[i] != '5' && string[i] != '7') {
			check++;
		}
	}
	return check;
}

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
		while(checkString(buffer) > 0) {
			printf("Invalid string, enter another one: ");
			fgets(buffer, BUFFER_SIZE, stdin);
		}
		write(pipefd[1], buffer, strlen(buffer)+1);
		close(pipefd[1]);
		wait(pid);
	}
	else {
		close(pipefd[1]);
		read(pipefd[0], buffer, sizeof(buffer));
		printf("Recevied string in player2.c: %s", buffer);
		close(pipefd[0]);
	}
	return 0;
}
