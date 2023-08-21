#ifndef INCHWORM_H
#define INCHWORM_H

#define BODY_LENGTH 3
#define SLEEP_TIME 150000
#define SCRUNCH_TIME SLEEP_TIME * 2
#define TRAIL_CHAR ' '

struct iwBody {
	int y, x;
	char worm_char;
};

struct inchworm {
	int direction;
	struct iwBody body[BODY_LENGTH];
	int max_x, max_y;
};

void initWorm(struct inchworm *worm, int direction, int start_y, int start_x, const char head_char, const char body_char);
void printWorm(struct inchworm *worm);
void eraseWorm(struct inchworm *worm);
void randomizeDirection(struct inchworm *worm);
int checkBounds(struct inchworm *worm);
void redirectWorm(struct inchworm *worm);
void *moveWorm(void *worm_ptr);

#endif
