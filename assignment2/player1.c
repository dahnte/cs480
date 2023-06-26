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
#define STRING_LIMIT 17 /* must acsubstr_length for '\n' */
#define BUFFER_SIZE 256 /* adjusted for spammed characters, as of now this works fine */

int checkString(char *string);
void getString(char *string);
void storeSubstring(char *string, int *index_choice, int *substr_amount);
char *cutString(char *string);

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
		getString(buffer);	
		cutString(buffer);
		write(pipefd[WRITE_END], buffer, strlen(buffer)+1);
		close(pipefd[WRITE_END]);
	}
	else if(pid == 0) { /* child process */
		close(pipefd[WRITE_END]);
		read(pipefd[READ_END], buffer, sizeof(buffer));
		printf("Received string in player2.c: %s\n", buffer);
		close(pipefd[READ_END]);
	}
	return 0;
}

/* 
 * int checkString ( char *string )
 *
 *  return >0: for how many characters are not '5' or '7' OR if string length is over 17 OR if the string does not contain both '5' AND '7'
 *	return 0: if string contains only '5' AND '7' and is below the 17 char substr_length
 */

int checkString(char *string) {
	int check = 0;
	int five_substr_length = 0;
	int seven_substr_length = 0;

	for(int i = 0; string[i] != '\0' && string[i] != '\n'; i++) { /* fgets looks for '\n' */
		if((strlen(string) > STRING_LIMIT) 
		|| (string[i] != '5' && string[i] != '7')) {
			check++;
		}
		else if(string[i] == '5') {
			five_substr_length++;
		}
		else if(string[i] == '7') {
			seven_substr_length++;
		}
	}

	if(five_substr_length > 0 && seven_substr_length > 0) { /* this will ensure we return 0 ONLY if the string contains '5' AND '7' */
		return check;
	}
	else { /* otherwise even if string is only '5' or '7' it will throw a number >0 */
		return check + five_substr_length + seven_substr_length;
	}
}

/*
 * void getString ( char * string )
 *
 *	side-effect: gets user inputted string, invokes checkStrine(string) to make sure its valid
 */

void getString(char *string) {
	printf("Enter a string that's less than 16 characters and ONLY contains '5' and '7': ");
	fgets(string, BUFFER_SIZE, stdin);

	while(checkString(string) > 0) { /* begin invalid string loop */
		printf("Invalid string, try again: ");
		fgets(string, BUFFER_SIZE, stdin);
	} 
}

/*
 * void storeSubstring ( char *string, int *index_choice )
 *
 * 	side-effect: fills int array with indices containing position of last char in each substring found
 */

void storeSubstring(char *string, int *index_choice, int *substr_amount) {
	char key = '\0';

	printf("Which set would you like to remove?\n");

	for(int i = 0, j = 0; (string[i] != '\0') && (string[i] != '\n'); i = j) { /* begin string loop */
		key = string[i]; /* character that will be looked for consecutively */
		printf("[%d]", *substr_amount);

		for(j = i; string[j] == key; j++) { /* print consecutive strings */
			printf("%c", string[j]);
		}

		index_choice[*substr_amount] = j - 1; /* adjust for substring's ending and not start of next substring */
		printf(" ");

		//printf("\ndebug1: %d and %d\n", index_choice[*substr_amount], *substr_amount);

		*substr_amount = *substr_amount + 1; /* interesting behavior when using *substr_amount++ */
	}
}

/*
 * char *cutString ( char *string )
 *
 *	return: a char* that has been snipped of a chosen set of 5 or 7 within the string by the user
 */

char *cutString(char *string) {
	int substr_choice = 0; /* contains substring number user wants to remove */
	int substr_amount = 0; /* holds how many substrings there are within string + 1 */
	int substr_length = 0; /* holds the length of substring to remove */
	int index_choice[STRING_LIMIT - 1]; /* acsubstr_length for \n */

	storeSubstring(string, index_choice, &substr_amount); 
	printf("\nEnter the number of the set: ");
	scanf("%d", &substr_choice);

	while((substr_choice > substr_amount - 1) || (substr_choice < 0)) { /* begin invalid set decision loop */
		printf("Invalid set entry, try again: ");
		scanf("%d", &substr_choice);
	}

	if(substr_choice == 0) {
		substr_length = index_choice[substr_choice] + 1;
	}
	else {
		substr_length = index_choice[substr_choice] - index_choice[substr_choice - 1];
	}

	//printf("debug2: %d\n", substr_length);

	for(int i = index_choice[substr_choice], j = i; substr_length > 0; substr_length--, i--, j = i) {
		if(substr_choice == substr_amount - 1) { /* removing the last set case */	
			string[i] = '\0';
		}
		else { /* otherwise they should copy over everything untill current position is '\0'*/
			while(string[j] != '\0') {
				string[j] = string[j + 1];
				j++;
			}
		}
	}

	//printf("debug3: %s", string);

	return string;
}