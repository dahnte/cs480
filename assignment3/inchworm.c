#include "inchworm.h"

void updateWormPosition(struct inchworm *worm, const int maxY, const int maxX) {
	if(worm->x >= maxX) {
		worm->direction = 'W';
	}
	else if(worm->x <= 0) {
		worm->direction = 'E';
	}

	switch(worm->direction) {
		case 'E':
			worm->x++;
			
			for(int i = 0; i < BODY_SIZE; i++) {
				worm->body[i].x = worm->x - i;
			}

			break;

		case 'W':
			worm->x--;

			for(int i = 0; i < BODY_SIZE; i++) {
				worm->body[i].x = worm->x + i;
			}
			break;
	}
}

void setWormBody(struct inchworm *worm, const char charHead, const char charBody) {
	worm->body[0].charWorm = charHead;
	for(int i = 1; i < BODY_SIZE; i++) {
		worm->body[i].charWorm = charBody;
	}
}
