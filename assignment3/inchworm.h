#ifndef INCHWORM_H
#define INCHWORM_H

#define BODY_LENGTH 3
#define SLEEP_TIME 400000
#define HEAD 0

struct iwBody {
	int y, x;
	char worm_char;
};

struct inchworm {
	int direction;
	struct iwBody body[BODY_LENGTH];
};

void initWorm(struct inchworm *worm, int direction, int y, int x, const char head_char, const char body_char);
void randomDir(struct inchworm *worm);
void printWorm(struct inchworm *worm);
void updateWorm(struct inchworm *worm, const int max_Y, const int max_X);

#endif
