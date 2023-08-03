#ifndef STRINGGAME_H
#define STRINGGAME_H

#define STRING_LIMIT 18 /* must account for '\n' */
#define BUFFER_SIZE 4 /* adjusted for spammed characters, as of now this works fine */

#define P1WRITE "/tmp/P1WRITE"
#define P2WRITE "/tmp/P2WRITE"

void clearInputBuffer(); 
void getInteger(int *integer_buffer, int buffer_size);
void getString(char *string);
void editString(char *string);
int checkString(char *string, char *player_name);

#endif
