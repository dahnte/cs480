#ifndef STRINGGAME_H
#define STRINGGAME_H

#define STRING_LIMIT 17 /* must account for '\n' and '\0' */
#define STRING_MIN 5
#define BUFFER_SIZE 64 /* adjusted for spammed characters, as of now this works fine */

#define P1WRITE "/tmp/P1WRITE"
#define P2WRITE "/tmp/P2WRITE"

void gameIntro();
void clearInputBuffer(); 
void getInteger(int *integer_buffer, int buffer_size);
void getString(char *string);
void editString(char *string);
int checkWinCondition(char *string, char *player_name);

#endif