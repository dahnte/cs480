#include <ncurses.h>
#include "inchworm.h"

void printWormPosition(struct inchworm *worm) {
	for(int i = 0; i < BODY_LENGTH; i++) {
		mvprintw(worm->body[i].y, worm->body[i].x, "%c", worm->body[i].worm_char);
	}
}

void setWormBody(struct inchworm *worm, const char head_char, const char body_char) {
	worm->body[0].worm_char = head_char;
	for(int i = 1; i < BODY_LENGTH; i++) {
		worm->body[i].worm_char = body_char;
	}
}

void randomDirection(struct inchworm *worm) {
	int input;
	scanf("%d", &input);
	worm->direction = input;
}

void updateWormPosition(struct inchworm *worm, const int max_Y, const int max_X) {
	clear();

	/* change direction of the worm if out of bounds */
	if(worm->body[0].x > max_X) {
		worm->direction = 6;
	}
	else if(worm->body[0].x < 0) {
		worm->direction = 2;
	}
	else if(worm->body[0].y < 0) {
		worm->direction = 4;
	}
	else if(worm->body[0].y > max_Y) {
		worm->direction = 0;
	}

	/**	How cardinal direction is represented
	 *                  0
	 *          7       N       1
	 *              NW      NE
	 *      6   W               E   2
	 *              SW      SE
	 *          5       S       3
	 *                  4
	 */

	/**	Multiple ways to make this work
	 * Currently I'm faking its body scrunch by having its length be 3 and
	 * adding 2 more when it "extends" 
	 */
	switch(worm->direction) {
		case 2:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x + 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);
			break;

		case 6:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x - 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);
			break;

		case 0:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].y = worm->body[0].y - 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);
			break;

		case 4:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].y = worm->body[0].y + 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWormPosition(worm);
			refresh();
			usleep(SLEEP_TIME);
			break;
	}
}
