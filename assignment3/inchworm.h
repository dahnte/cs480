#ifndef INCHWORM_H
#define INCHWORM_H

#define BODY_LENGTH 3
#define SLEEP_TIME 120000
#define SCRUNCH_TIME SLEEP_TIME * 2
#define TRAIL_CHAR ' '

struct iwBody {
	int y, x;
	char worm_char;
};

struct inchworm {
	int direction;
	struct iwBody body[BODY_LENGTH];
};

void initWorm(struct inchworm *worm, int direction, int start_y, int start_x, const char head_char, const char body_char);
void printWorm(struct inchworm *worm);
void eraseWorm(struct inchworm *worm);
void randomizeDirection(struct inchworm *worm);
int checkBounds(struct inchworm *worm, const int max_y, const int max_x);
void redirectWorm(struct inchworm *worm);
void moveWorm(struct inchworm *worm, const int max_y, const int max_x);

#endif
