/** Author: Dante Cardenas
 *  August 10, 2023
 *  CS480 - Linux Programming
 *
 *  The pen for holding the inchworms
 */

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "inchworm.h" /* SLEEP_TIME, BODY_LENGTH, SCRUNCH_TIME */

int main(int *argc, char *argv[]) {
	int max_y, max_x;

	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, max_y, max_x);

	srand(time(NULL));

	struct inchworm worm1;
	initWorm(&worm1, 1, max_y/2, max_x/2, '@', '#');
	struct inchworm worm2;
	initWorm(&worm2, 6, max_y/3, max_x/2, '@', '#');
	struct inchworm worm3;
	initWorm(&worm3, 4, max_y/3, max_x/3, '@', '#');
	struct inchworm worm4;
	initWorm(&worm4, 0, max_y/2, max_x/2, '@', '#');

	while(1) {
		//randomDirection(&worm1);
		moveWorm(&worm1, max_y, max_x);
		moveWorm(&worm2, max_y, max_x);
		moveWorm(&worm3, max_y, max_x);
		moveWorm(&worm4, max_y, max_x);
	}

	endwin();
	return 0;
}
