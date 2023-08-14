/** Author: Dante Cardenas
 *  August 10, 2023
 *  CS480 - Linux Programming
 *
 *  The pen for holding the inchworms
 */

#include <ncurses.h>
#include <unistd.h>
#include <string.h>
#include "inchworm.h"

int main(int *argc, char *argv[]) {
	struct inchworm worm1 = {15, 62, 'E'};
	int maxY, maxX;

	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, maxY, maxX);
	setWormBody(&worm1, 'O', 'o');

	while(1) {
		clear();
		updateWormPosition(&worm1, maxY, maxX);
		for(int i = 0; i < BODY_SIZE; i++) {
			mvprintw(worm1.y, worm1.body[i].x, "%c", worm1.body[i].charWorm);
		}
		refresh();
		usleep(20000);
	}

	endwin();
	return 0;
}
