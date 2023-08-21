/** Author: Dante Cardenas
 *  August 10, 2023
 *  CS480 - Linux Programming
 *
 *  The pen for holding the inchworms
 */

#include <ncurses.h>
#include <stdlib.h> /* srand() */
#include <time.h> /* time() */
#include <pthread.h> /* POSIX threads */
#include "inchworm.h" /* SLEEP_TIME, BODY_LENGTH, SCRUNCH_TIME */

int main(int *argc, char *argv[]) {
	int max_y, max_x;
	struct inchworm worm1, worm2, worm3, worm4;
	pthread_t thread1, thread2, thread3, thread4;

	initscr();
	curs_set(0);
	noecho();
	getmaxyx(stdscr, max_y, max_x);

	srand(time(NULL));

	initWorm(&worm1, 1, max_y, max_x, max_y/2, max_x/2, '@', '#');
	initWorm(&worm2, 6, max_y, max_x, max_y/3, max_x/2, '@', '#');
	initWorm(&worm3, 4, max_y, max_x, max_y/3, max_x/3, '@', '#');
	initWorm(&worm4, 0, max_y, max_x, max_y/2, max_x/2, '@', '#');

	while(1) {
		pthread_create(&thread1, NULL, moveWorm, &worm1);
		pthread_create(&thread2, NULL, moveWorm, &worm2);
		//pthread_create(&thread3, NULL, moveWorm, &worm3);
		//pthread_create(&thread4, NULL, moveWorm, &worm4);
		pthread_join(thread1, NULL);
		pthread_join(thread2, NULL);
		//pthread_join(thread3, NULL);
		//pthread_join(thread4, NULL);
	}
	endwin();
	return 0;
}
