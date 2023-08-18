/** Author: Dante Cardenas
 *  August 10, 2023
 *  CS480 - Linux Programming
 *
 *  The pen for holding the inchworms
 */

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "inchworm.h" /* SLEEP_TIME, BODY_LENGTH */

int main(int *argc, char *argv[]) {
	int max_y, max_x;

	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, max_y, max_x);

	struct inchworm worm1; /* initialize inchworm "object" as worm1*/
	initWorm(&worm1, 1, max_y/2, max_x/2, '@', '#');
	struct inchworm worm2;
	initWorm(&worm2, 3, max_y/3, max_x/2, '@', '#');
	struct inchworm worm3;
	initWorm(&worm3, 6, max_y/2, max_x/3, '@', '#');
	struct inchworm worm4;
	initWorm(&worm4, 4, max_y/3, max_x/3, '@', '#');
	struct inchworm worm5;
	initWorm(&worm5, 7, max_y/4, max_x/2, '@', '#');

	while(1) {
		//randomDirection(&worm1);
		updateWorm(&worm1, max_y, max_x);
		updateWorm(&worm2, max_y, max_x);
		updateWorm(&worm3, max_y, max_x);
		updateWorm(&worm4, max_y, max_x);
		updateWorm(&worm5, max_y, max_x);
		
	}

	endwin();
	return 0;
}
