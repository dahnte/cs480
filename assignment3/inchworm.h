#ifndef INCHWORM_H
#define INCHWORM_H

#define BODY_SIZE 5

struct iwBody {
	int y, x;
	char charWorm;
};

struct inchworm {
	int y, x;
	char direction;
	struct iwBody body[BODY_SIZE];
};

void updateWormPosition(struct inchworm *worm, const int maxY, const int maxX);
void setWormBody(struct inchworm *worm, const char charHead, const char charBody);

#endif
