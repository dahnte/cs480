#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_BODY_SEGMENTS 5

typedef struct {
    int x;
    int y;
    int dx;
    int dy;
} WormSegment;

typedef struct {
    int x;
    int y;
    int direction;
    WormSegment body[MAX_BODY_SEGMENTS];
    int numSegments;
} Worm;

void moveWorm(Worm* worm, int maxX, int maxY) {
    if (worm->x <= 0 || worm->x >= maxX - 1)
        worm->direction = -worm->direction;

    if (worm->direction > 0) {
        if (worm->x < maxX - 1) {
            worm->x++;
        } else {
            worm->y++;
            worm->direction = -worm->direction;
        }
    } else {
        if (worm->x > 0) {
            worm->x--;
        } else {
            worm->y++;
            worm->direction = -worm->direction;
        }
    }

    for (int i = worm->numSegments - 1; i > 0; i--) {
        worm->body[i] = worm->body[i - 1];
    }

    worm->body[0].x = worm->x;
    worm->body[0].y = worm->y;
}

int main() {
    initscr();
    curs_set(0);
    noecho();

    int maxX, maxY;
    getmaxyx(stdscr, maxY, maxX);

    Worm worm;
    worm.x = maxX / 2;
    worm.y = 1;
    worm.direction = 1;
    worm.numSegments = 0;

    while (1) {
        clear();

        moveWorm(&worm, maxX, maxY);

        mvprintw(worm.y, worm.x, "@");

        for (int i = 0; i < worm.numSegments; i++) {
            mvprintw(worm.body[i].y, worm.body[i].x, "#");
        }

        refresh();

        usleep(100000);

        if (worm.numSegments < MAX_BODY_SEGMENTS) {
            worm.numSegments++;
        }
    }

    endwin();
    return 0;
}

