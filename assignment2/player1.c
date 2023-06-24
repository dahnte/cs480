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
#define READ_END 0
#define WRITE_END 1
#define STRING_LIMIT 17 /* must account for '\n' */

/* 
 * int checkString ( char *string )
 *
 *  return: returns >0 for how many characters are not '5' or '7' OR if string length is over 17 OR if the string does not contain both '5' and '7'
 *	return: returns 0 if string contains only '5' AND '7'
 */

int checkString(char *string) {
	int check = 0;
	int fiveFlag = 0;
	int sevenFlag = 0;

	for(int i = 0; string[i] != '\0' && string[i] != '\n'; i++) { /* fgets adds a '\n' */
		if((strlen(string) > STRING_LIMIT) 
		|| (string[i] != '5' && string[i] != '7')) {
			check++;
		}
		else if(string[i] == '5') {
			fiveFlag++;
		}
		else if(string[i] == '7') {
			sevenFlag++;
		}
	}

	if(fiveFlag > 0 && sevenFlag > 0) { /* this will ensure we return 0 ONLY if the string contains '5' AND '7' */
		return check;
	}
	else { /* otherwise even if string is only '5' or '7' it will throw a number >0 */
		return check + fiveFlag + sevenFlag;
	}
}

/*
 * char *cutString ( char *string )
 *
 *	return: a char* that has been snipped of a
*/

int main() {
	int pipefd[2];
	pid_t pid;
	char buffer[BUFFER_SIZE];

	if(pipe(pipefd) == -1) {
		printf("Error creating pipe");
		return 1;
	}
	if((pid = fork()) < 0) {
		printf("Error with pipe");
		return 2;
	}
	else if(pid > 0) { /* parent  process */
		close(pipefd[READ_END]);
		printf("Enter a string consisting of 5 and 7 that is less than 16 characters: ");
		fgets(buffer, BUFFER_SIZE, stdin);
		while(checkString(buffer) > 0) {
			printf("Invalid string, enter another one: ");
			fgets(buffer, BUFFER_SIZE, stdin);
		}
		write(pipefd[WRITE_END], buffer, strlen(buffer)+1);
		close(pipefd[WRITE_END]);
		printf("%d\n", pid);
	}
	else if(pid == 0) { /* child process */
		close(pipefd[WRITE_END]);
		read(pipefd[READ_END], buffer, sizeof(buffer));
		printf("Recevied string in player2.c: %s", buffer);
		close(pipefd[READ_END]);
		printf("%d\n", pid);
	}
	return 0;
}