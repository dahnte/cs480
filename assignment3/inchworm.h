#ifndef INCHWORM_H
#define INCHWORM_H

#define BODY_LENGTH 3
#define SLEEP_TIME 500000

struct iwBody {
	int y, x;
	char worm_char;
};

struct inchworm {
	int direction;
	struct iwBody body[BODY_LENGTH];
};

void printWormPosition(struct inchworm *worm);
void setWormBody(struct inchworm *worm, const char head_char, const char body_char);
void updateWormPosition(struct inchworm *worm, const int max_Y, const int max_X);
void randomDirection(struct inchworm *worm);

#endif
