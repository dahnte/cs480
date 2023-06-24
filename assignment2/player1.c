/* 
 * Author: Dante Cardenas
 * June 14, 2023
 * CS480 - Advanced Topics in Computing
 *
 * Assignment 2 - A Game of Pipes. 
 * objective:
 *		player1.c starts the game with user inputted string containing 5 and 7
 *		the string is limited and checked for invalid chars
 *
 *		player1.c edits the string removing any substr of 5's or 7's 
 *		by any amount
 *
 *		player2.c responds by also editting the recevied string
 *
 *		the game continues until any player receives a blank string
 *
 *		the self declared loser sends a 1 to the other player so they could
 *		declare themselves the winner
 */

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define READ_END 0
#define WRITE_END 1
#define STRING_LIMIT 17 /* must account for '\n' */
#define BUFFER_SIZE 256 /* adjusted for spammed characters, as of now this works fine */

/* 
 * int checkString ( char *string )
 *
 *  return >0: for how many characters are not '5' or '7' OR if string length is over 17 OR if the string does not contain both '5' AND '7'
 *	return 0: if string contains only '5' AND '7' and is below the 17 char count
 */

int checkString(char *string) {
	int check = 0;
	int five_count = 0;
	int seven_count = 0;

	for(int i = 0; string[i] != '\0' && string[i] != '\n'; i++) { /* fgets looks for '\n' */
		if((strlen(string) > STRING_LIMIT) 
		|| (string[i] != '5' && string[i] != '7')) {
			check++;
		}
		else if(string[i] == '5') {
			five_count++;
		}
		else if(string[i] == '7') {
			seven_count++;
		}
	}

	if(five_count > 0 && seven_count > 0) { /* this will ensure we return 0 ONLY if the string contains '5' AND '7' */
		return check;
	}
	else { /* otherwise even if string is only '5' or '7' it will throw a number >0 */
		return check + five_count + seven_count;
	}
}

/*
 * char *cutString ( char *string )
 *
 *	return: a char* that has been snipped of a chosen set of 5 or 7 within the string by the user
 */

char *cutString(char *string) {
	int set_num = 1;
	char key = '\0';
	int index_choice[STRING_LIMIT - 1]; /* does not need to account for '\n' */
	printf("Which set would you like to remove?\n");
	for(int i = 0, j = 0; (string[i] != '\0') && (string[i] != '\n'); i = j) {
		key = string[i];
		printf("[%d]", set_num++);
		index_choice[set_num - 1] = i; /* for the sake of UI, the index begins at 1 */
		for(j = i; string[j] == key; j++) {
			printf("%c", string[j]);
		}
		printf(" ");
	}

	int set_choice = 0;
	printf("\nEnter the number of the set: ");
	scanf("%d", set_choice);
	int temp = index_choice[set_choice] - index_choice[set_choice - 1]; /* a tad bit confusing aint it */
	for(int i_rev = (strlen(string) - 1), j_rev; temp > 0; i_rev--) {
		for(j_rev = i_rev; j_rev > index_choice[set_choice - 1]; j_rev--) {
			string[j_rev - 1] = string[j_rev];
			string[j_rev] = '\0';
			printf("From cutString: %s", string);
		}
		temp--;
	}
	return string;
}

int main() {
	int pipefd[2];
	pid_t pid;
	char buffer[BUFFER_SIZE];

	if(pipe(pipefd) == -1) { /* create pipe */
		printf("Error creating pipe");
		return 1;
	}

	if((pid = fork()) == -1) { /* get pid from fork */
		printf("Error with pipe");
		return 2;
	}
	else if(pid > 0) { /* parent process */
		close(pipefd[READ_END]);
		printf("Enter a string that's less than 16 characters and contains '5' and '7': ");
		fgets(buffer, BUFFER_SIZE, stdin);
		while(checkString(buffer) > 0) { /* begin invalid string loop */ 
			printf("Invalid string, try again: ");
			fgets(buffer, BUFFER_SIZE, stdin);
		}
		cutString(buffer);
		write(pipefd[WRITE_END], buffer, strlen(buffer)+1);
		close(pipefd[WRITE_END]);
	}
	else if(pid == 0) { /* child process */
		close(pipefd[WRITE_END]);
		read(pipefd[READ_END], buffer, sizeof(buffer));
		printf("Recevied string in player2.c: %s", buffer);
		close(pipefd[READ_END]);
	}
	return 0;
}
