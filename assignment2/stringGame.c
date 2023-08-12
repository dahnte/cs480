/** Author: Dante Cardenas
 *	July 21, 2023
 *	CS480 - Linux Programming
 *
 *	Assignment 2 - 57 Pipes
 *	objective:
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

#include <stdio.h> /* fgets, fgetc */
#include <stdlib.h> /* malloc */
#include <string.h> /* strlen  */
#include <ctype.h>
#include <errno.h> /* errno */
#include "stringGame.h"

void gameIntro() {
	fprintf(stdout, "\n ____ _____   ____  _                 \n");
	fprintf(stdout, "| ___|___  | |  _ \\(_)_ __   ___  ___ \n");
	fprintf(stdout, "|___ \\  / /  | |_) | | '_ \\ / _ \\/ __|\n");
	fprintf(stdout, " ___) |/ /   |  __/| | |_) |  __/\\__ \\\n");
	fprintf(stdout, "|____//_/    |_|   |_| .__/ \\___||___/\n");
	fprintf(stdout, "                     |_|              \n");
	fprintf(stdout, "A two-player string manipulation game\n\n");
}

/**	clearInputBuffer() - is a helper function inside editString()
 *
 *	Prevents characters being wrongly accepted as input from overflow
 */
void clearInputBuffer() {
	char c = 0;
	while ((c = getchar()) != '\n' && c != EOF);
}

/**	getInt() is a helper function inside editString()
 *
 *	@integer_buffer: 
 *	@buffer_size: 
 *
 *	Handles overflow and invalid input
 */
void getInteger(int *integer_buffer, int buffer_size) {
	char *input_buffer = malloc(sizeof(char) * buffer_size);
	memset(input_buffer, 0 , buffer_size);
	char *input = NULL;

	while (input == NULL) {
		input = fgets(input_buffer, buffer_size, stdin);

		if(input_buffer[strlen(input_buffer) - 1] != '\n') {
			fprintf(stderr, "Invalid input, too many characters. Try again: ");
			clearInputBuffer();
			input = NULL;
			continue;
		}

		errno = 0;
		char *endptr = NULL;
		*integer_buffer = strtol(input, &endptr, 10);

		if(input == endptr) {
			input[strcspn(input, "\n")] = 0;
			fprintf(stderr, "Invalid input, no integer found. Try again: ");
			clearInputBuffer();
			input = NULL;
		}

		if(errno != 0) {
			fprintf(stderr, "Invalid input. Try again! ");
			clearInputBuffer();
			input = NULL;
		}
	}
	free(input_buffer);
}

/** getString() - Handles the start game mechanic
 *
 *	@string: Input received from player1.c
 *
 *	It asks the user for input via `fgets` and then checks it to make sure 
 *	it only contains 5 and 7 and is below the 16 character limit.
 */
void getString(char *string) {
	char *result = NULL;
	unsigned int flag_five = 0;
	unsigned int flag_seven = 0;
	unsigned int flag_invalid = 0;

	fprintf(stdout, "Enter a string that contains 5 AND 7 that is also greater than 4 and less than 16 characters\n");
	while(result == NULL) {
		result = fgets(string, BUFFER_SIZE, stdin);

		//DEBUG
		//fprintf(stderr, "[DEBUG] Length of strlen(string) - 1: %d\n", (strlen(string) - 1));

		if((strlen(string) > STRING_LIMIT) || (strlen(string) < STRING_MIN)) {
			fprintf(stderr, "Invalid input, must be greater than 4 and less than 16 characters. Try again\n");
			clearInputBuffer();
			result = NULL;
			continue;
		}

		for(int i = 0; i < strlen(string) - 1; i++) {
			if(string[i] == '5') { flag_five++; }
			if(string[i] == '7') { flag_seven++; }
			if(string[i] != '5' && string[i] != '7') { flag_invalid++; }
		}

		if(flag_invalid > 0) {
			fprintf(stderr, "Invalid input, must contain only 5 AND 7. Try again\n");
			clearInputBuffer();
			flag_invalid = 0;
			result = NULL;
			continue;
		}

		//DEBUG
		//fprintf(stderr, "[DEBUG] flag_five: %d, flag_seven: %d\n", flag_five, flag_seven);

		if(flag_five < 2 || flag_seven < 2) {
			fprintf(stderr, "Invalid input, must contain both 5 AND 7. Try again\n");
			flag_five = 0;
			flag_seven = 0;
			clearInputBuffer();
			result = NULL;
			continue;
		}
	}
}

/**	editString() - handles the main gameplay mechanic.
 *
 *	@string: Input from previous player, only contains 5's and 7's
 *
 *	Users input the index of the substring they would like to edit and
 *	the amount of characters they would like to remove for the chosen substring.
 */
void editString(char *string) {
	int substr_index = 0; /* Contains substring number user wants to remove */
	int substr_length = 0; /* Holds the length of substring to be removed */
	int substr_total = 0; /* Holds how many substrings there are within string + 1 */
	char key = 0;
	int *substr_index_list = malloc(sizeof(char) * BUFFER_SIZE);

	for(int i = 0, j = 0; (string[i] != '\n'); i = j, substr_total++) { /* Begin string loop */
		key = string[i]; /* Character that will be looked for consecutively */
		fprintf(stdout, "[%d]", substr_total);

		for(j = i; string[j] == key; j++) { /* Print consecutive strings */
			fprintf(stdout, "%c", string[j]);
		}

		substr_index_list[substr_total] = j - 1; /* Adjust for substring's ending and not start of next substring */
		fprintf(stdout, " \n");
		//DEBUG
		//fprintf(stderr, "\ncutstring1: %d and %d\n", substr_index_list[substr_total], substr_total);
	}
	fprintf(stdout, "Enter [index] of substring you would like to remove: ");
	getInteger(&substr_index, BUFFER_SIZE);

	/* Invalid input loop */
	while((substr_index > substr_total - 1) || (substr_index < 0)) { 
		// Handle input greater than or less than accepted range
		fprintf(stderr, "Invalid index choice, try again: ");
		getInteger(&substr_index, BUFFER_SIZE);
		clearInputBuffer();
	}

	fprintf(stdout, "Enter amount to reduce substring's length by: ");
	getInteger(&substr_length, BUFFER_SIZE);
	/* Invalid input loop */
	if(substr_index == 0) {
		while((substr_length > (substr_index_list[substr_index] + 1)) || (substr_length < 1)) {
			fprintf(stderr, "Invalid reduction length, try again: ");
			getInteger(&substr_length, BUFFER_SIZE);
			clearInputBuffer();
		}
	}
	else {
		while((substr_length > (substr_index_list[substr_index] - substr_index_list[substr_index - 1])) || (substr_length < 1))  { /* Invalid length if greaters than max length of substr OR <1 */
			fprintf(stderr, "Invalid reduction length, try again: ");
			getInteger(&substr_length, BUFFER_SIZE);
			clearInputBuffer();
		}
	}
	//DEBUG
	//fprintf(stdout, "[DEBUG] cutstring2: %d and %d\n", substr_length, strlen(string));

	for(int i = substr_index_list[substr_index], j = i; substr_length > 0; substr_length--, i--, j = i) {
		if(substr_index == substr_total - 1) { /* Removing the last set case */	
			string[i] = '\n';
		}
		else { /* Otherwise they should copy over everything until current position is 0 */
			while((string[j] != '\n')) {
				string[j] = string[j + 1];
				j++;
			}
		}
	}
	//DEBUG
	//printf("[DEBUG]: %s", string);
}

/** checkWinCondition() - Handles the win conditions
 *
 *	@string: Input from received from previous players, may be 'empty' at this point
 *	@player_name: Holds the player's name to be included in the result message
 *
 *	Return 0 if a player won and return 1 if a player lost
 */
int checkWinCondition(char *string, char *player_name) {
	if((string[0] == '\n')) {
		fprintf(stdout, "\n%s won the game! Good job.\n", player_name);
		string[0] = '1';
		return 0;
	}	
	else if(string[0] == '1') {
		fprintf(stdout, "\n%s lost the game! Better luck next time.\n", player_name);
		return 0;
	}
	else { return 1; }
}
