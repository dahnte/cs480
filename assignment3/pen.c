/** Author: Dante Cardenas
 *  August 10, 2023
 *  CS480 - Linux Programming
 *
 *  The basis for holding the inchworms
 */

#include <ncurses.h>
#include <string.h>

void initPen(int y, int x) {
	char mesg[] = "Hello";
	bkgdset('-');
	mvprintw(LINES/2, (COLS/2) - strlen(mesg),"%s", mesg);
	refresh();
	sleep(1);
}

int main(int argc, char *argv) {
	int y, x;
	initscr();
	noecho();
	curs_set(FALSE);

	initPen(y, x);

	endwin();
	return 0;
}
