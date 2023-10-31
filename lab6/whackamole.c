#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MOLE 'M'
#define EMPTY_HOLE 'O'

struct moleHole {
	int pos_y, pos_x;
	char hole_char;
};

void print_titles(int *max_y, int *max_x) {
	mvprintw(2, *max_x/2 - 6, "Whack-A-Mole");
	mvprintw(3, *max_x/2 - 18, "To whack a mole, type the hole number");
	mvprintw(*max_y - 4, 10, "Score:");
	mvprintw(*max_y - 4, *max_x - 13, "Round:");
}

void print_warning(int *max_y, int *max_x) {
	mvprintw(*max_y - 4, *max_x/2 - 12, "New mole hole incoming!");
}

void print_end_screen(int *max_y, int *max_x, int total_score, int hit_score) {
	total_score = hit_score - total_score;
	mvprintw(*max_y/2, *max_x/2 - 23, "Great job, you whacked %d moles and missed %d!", hit_score, total_score);
}

void remove_warning(int *max_y, int *max_x) {
	mvprintw(*max_y - 4, *max_x/2 - 12, "                       ");
}

/** intialize_holes() - prepares struct moleHole for the game */
void initialize_holes(struct moleHole holes[], int *max_y, int *max_x) {
	holes[0].pos_y = *max_y/2 - 1;
	holes[0].pos_x = *max_x/2;
	holes[1].pos_y = *max_y/2 - 3;
	holes[1].pos_x = *max_x/1.5;
	holes[2].pos_y = *max_y/2 - 3;
	holes[2].pos_x = *max_x/3;
	holes[6].pos_y = *max_y/2;
	holes[6].pos_x = *max_x/1.7;
	holes[8].pos_y = *max_y/2;
	holes[8].pos_x = *max_x/2.4;
	holes[9].pos_y = *max_y/2;
	holes[9].pos_x = *max_x/1.3;
	holes[3].pos_y = *max_y/1.5 - 3;
	holes[3].pos_x = *max_x/1.6;
	holes[7].pos_y = *max_y/1.5 - 3;
	holes[7].pos_x = *max_x/2.7;
	holes[4].pos_y = *max_y/2;
	holes[4].pos_x = *max_x/4;
	holes[5].pos_y = *max_y/1.5 - 1;
	holes[5].pos_x = *max_x/2;
}

/** update_mole() - randomizes mole placement, empties holes before placing mole */
void update_mole(struct moleHole holes[], int round) {
	if(round < 7)
		round = round + 3; /* should be 2 but its +1 because we need to include 0 */
	else
		round = round + 2;
	int r = rand() % round; /* inclusive */
	
	while(round >= 0) {
		holes[round].hole_char = EMPTY_HOLE;
		round--;
	}
	holes[r].hole_char = MOLE;
}

/** update_holes() - keeps up with current round and prints available holes */
void update_holes(struct moleHole holes[], int round) {
	round = round + 2;
	while(round >= 0) {
		attron(A_STANDOUT);
		mvprintw(holes[round].pos_y, holes[round].pos_x, "%c", holes[round].hole_char);
	  	attroff(A_STANDOUT);
		mvprintw(holes[round].pos_y + 1, holes[round].pos_x, "%d", round);
		round--;
	}
}

/** update_score() - prints current score and round */
//TODO BUG going from negative to positive doubles your points?
void update_score(int *max_y, int *max_x, int *total_score, int *round) {
	mvprintw(*max_y - 3, 12, "%d", *total_score);
	mvprintw(*max_y - 3, *max_x - 11, "%d", *round);
}

int main(int *argc, char *argv[]) {
	int max_y, max_x;
	int total_score = 0, hit_score, round = 0;
	char c = 0;
	int timing = 1500;
	struct moleHole holes[10];

	initscr();
	cbreak();
	curs_set(0);
	noecho();
	//nodelay(stdscr, TRUE);
	timeout(timing);
	getmaxyx(stdscr, max_y, max_x);
	srand(time(NULL));

	/* print static elements and initialize layout for holes */
	print_titles(&max_y, &max_x);
	initialize_holes(holes, &max_y, &max_x);

	while(round <= 7) {
		update_mole(holes, round);
		update_holes(holes, round);
		update_score(&max_y, &max_x, &total_score, &round);
		if((c = getch()) != ERR) {
			c = c - '0';
			/* needs some work, but adds a visual to which hole you whack */
			attron(A_STANDOUT);
			mvprintw(holes[c].pos_y, holes[c].pos_x + 1, " ");
			mvprintw(holes[c].pos_y, holes[c].pos_x - 1, " ");
			refresh();
			usleep(timing * 100);
			attroff(A_STANDOUT);
			mvprintw(holes[c].pos_y, holes[c].pos_x + 1, " ");
			mvprintw(holes[c].pos_y, holes[c].pos_x - 1, " ");

			if(holes[c].hole_char == MOLE){
				timing = timing - 50;
				total_score++;
				hit_score++;
			}
			else {
				timing = timing - 50;
				total_score--;
			}
		}
		else {
			timing = timing - 100;
		}
		/* DEBUG
		mvprintw(1,3,"timing: %d", timing);
		mvprintw(2,3,"integer: %d", c);
		mvprintw(3,3,"char: %c", c);
		mvprintw(4,3,"holes: %c", holes[c].hole_char);
		refresh();
		*/
		if(timing <= 200 && timing > 0) {
			if(round < 7)
				print_warning(&max_y, &max_x);
		}
		else if (timing <= 0) {
			if(round < 7)
				remove_warning(&max_y, &max_x);
			round++;
			timing = 1200;
		}
	}

	clear();
	print_end_screen(&max_y, &max_x, total_score, hit_score);
	refresh();
	sleep(5);

	endwin();
	return 0;
}
