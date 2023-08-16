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
	int max_Y, max_X;

	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, max_Y, max_X);

	struct inchworm worm1 = { 0 }; /* initialize inchworm "object" as worm1*/
	worm1.body[0].x = max_X/2;
	worm1.body[0].y = max_Y/2;
	setWormBody(&worm1, '@', '#'); /* decide which characters will represent the worm1 */

	while(1) {
		//randomDirection(&worm1);
		updateWormPosition(&worm1, max_Y, max_X);
	}

	endwin();
	return 0;
}
