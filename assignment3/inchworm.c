#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define BODY_LENGTH 3
#define SLEEP_TIME 300000
#define SCRUNCH_TIME SLEEP_TIME * 2
#define TRAIL_CHAR ' '

pthread_mutex_t mutex;

struct iwBody{
	int y, x;
	char worm_char;
};

struct inchworm {
	int direction;
	struct iwBody body[BODY_LENGTH];
	int max_x, max_y;
};

void initWorm(struct inchworm *worm, int direction, int max_y, int max_x, int start_y, int start_x, const char head_char, const char body_char) {
	/* set worm direction to 0-7 */
	worm->direction = direction;
	
	/* assign max_y and max_x of worm's allowed movements  */
	worm->max_y = max_y;
	worm->max_x = max_x;

	/* assign char's to worm's body and unique char to worm head */
	worm->body[0].worm_char = head_char; 
	for(int i = 1; i < BODY_LENGTH; i++) {
		worm->body[i].worm_char = body_char;
	}

	/* assign worm's head position, which is also the starting position */
	worm->body[0].y = start_y; 
	worm->body[0].x = start_x;
}
	
void printWorm(struct inchworm *worm) {
	for(int i = 0; i < BODY_LENGTH; i++) {
		mvprintw(worm->body[i].y, worm->body[i].x, "%c", worm->body[i].worm_char);
	}
}

void eraseWorm(struct inchworm *worm) {
	for(int i = 0; i < BODY_LENGTH; i++) {
		mvprintw(worm->body[i].y, worm->body[i].x, "%c", ' ');
	}
}

void randomizeDirection(struct inchworm *worm) {
	int r = rand() % 101;

	if(r < 25) {
		if(worm->direction == 7)
			worm->direction = 0;
		else 
			worm->direction++;
	}
	else if(r > 75) {
		if(worm->direction == 0) 
			worm->direction = 7;
		else 
			worm->direction--;
	}
	eraseWorm(worm);
}

int checkBounds(struct inchworm *worm) {
	if(worm->body[0].y > worm->max_y - 7
				|| worm->body[0].y < 7
				|| worm->body[0].x < 7
				|| worm->body[0].x > worm->max_x - 7)
	{
		return 1;
	}
	else
		return 0;
}

void redirectWorm(struct inchworm *worm) {
	if(worm->direction != 7)
		worm->direction++;	
	else
		worm->direction = 0;

	eraseWorm(worm);
}

void *moveWorm(void *worm_ptr) {
	struct inchworm *worm = (struct inchworm*)(worm_ptr);

	while(1) {
	if(checkBounds(worm) == 1) {
		redirectWorm(worm); /* if worm is out of bounds then fix their direction  */
	}
	else {
		randomizeDirection(worm); /* if worm is not out of bounds then set a normal random direction */
	}

	/**	Cardinal direction representation using 0-7
	 *                  0
	 *          7       N       1
	 *              NW      NE
	 *      6   W               E   2
	 *              SW      SE
	 *          5       S       3
	 *                  4
	 */
pthread_mutex_lock(&mutex);
	switch(worm->direction) {
		case 0:
			/* scrunch worm  */
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			/* extend worm */
			worm->body[0].y = worm->body[0].y - 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			/* remove trailing character not part of worm */
			mvprintw(worm->body[2].y + 2, worm->body[2].x, "%c", TRAIL_CHAR);
			mvprintw(worm->body[1].y + 2, worm->body[1].x, "%c", TRAIL_CHAR);
			usleep(SCRUNCH_TIME);
			break;
		case 1:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x + 2;
			worm->body[0].y = worm->body[0].y - 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y + 2, worm->body[2].x - 2, "%c", TRAIL_CHAR);
			mvprintw(worm->body[1].y + 2, worm->body[1].x - 2, "%c", TRAIL_CHAR);
			usleep(SCRUNCH_TIME);
			break;
		case 2:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x + 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y, worm->body[2].x - 2, "%c", TRAIL_CHAR);
			mvprintw(worm->body[1].y, worm->body[1].x - 2, "%c", TRAIL_CHAR);
			usleep(SCRUNCH_TIME);
			break;
		case 3:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x + 2;
			worm->body[0].y = worm->body[0].y + 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x - i;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y - 2, worm->body[2].x - 2, "%c", TRAIL_CHAR);
			mvprintw(worm->body[1].y - 2, worm->body[1].x - 2, "%c", TRAIL_CHAR);
			usleep(SCRUNCH_TIME);
			break;
		case 4:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].y = worm->body[0].y + 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y - 2, worm->body[2].x, "%c", TRAIL_CHAR);	
			mvprintw(worm->body[1].y - 2, worm->body[1].x, "%c", TRAIL_CHAR);	
			usleep(SCRUNCH_TIME);
			break;
		case 5:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x - 2;
			worm->body[0].y = worm->body[0].y + 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y - i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y - 2, worm->body[2].x + 2, "%c", TRAIL_CHAR);	
			mvprintw(worm->body[1].y - 2, worm->body[1].x + 2, "%c", TRAIL_CHAR);	
			usleep(SCRUNCH_TIME);
			break;
		case 6:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x - 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y, worm->body[2].x + 2, "%c", TRAIL_CHAR);
			mvprintw(worm->body[1].y, worm->body[1].x + 2, "%c", TRAIL_CHAR);
			usleep(SCRUNCH_TIME);
			break;
		case 7:
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			worm->body[0].x = worm->body[0].x - 2;
			worm->body[0].y = worm->body[0].y - 2;
			for(int i = 0; i < BODY_LENGTH; i++) {
				worm->body[i].x = worm->body[0].x + i;
				worm->body[i].y = worm->body[0].y + i;
			}
			printWorm(worm);
			refresh();
			usleep(SLEEP_TIME);

			mvprintw(worm->body[2].y + 2, worm->body[2].x + 2, "%c", TRAIL_CHAR);
			mvprintw(worm->body[1].y + 2, worm->body[1].x + 2, "%c", TRAIL_CHAR);
			usleep(SCRUNCH_TIME);
			break;
	}
	pthread_mutex_unlock(&mutex);
	}
}

int main(int *argc, char *argv[]) {
	int max_y, max_x;
	struct inchworm worm[4];
	pthread_t thread[4];

	pthread_mutex_init(&mutex, NULL);

	initscr();
	curs_set(0);
	noecho();
	clear();
	getmaxyx(stdscr, max_y, max_x);

	srand(time(NULL));

	initWorm(&worm[0], 1, max_y, max_x, max_y/2, max_x/2, '@', '#');
	initWorm(&worm[1], 6, max_y, max_x, max_y/3, max_x/2, '@', '#');
	initWorm(&worm[2], 4, max_y, max_x, max_y/3, max_x/3, '@', '#');
	initWorm(&worm[3], 0, max_y, max_x, max_y/2, max_x/2, '@', '#');

	for(int i = 0; i < 4; i++) {
		pthread_create(&thread[i], NULL, moveWorm, &worm[i]);
	}

	for(int i = 0; i < 4; i++) {
		pthread_join(thread[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	endwin();
	return 0;
}
