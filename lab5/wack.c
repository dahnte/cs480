#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
  initscr();

  int row, col;
  getmaxyx(stdscr, row, col);
  mvprintw(row/2, (col-12)/2, "Hello, World!");

  getch();

  endwin();

  return 0;
}
