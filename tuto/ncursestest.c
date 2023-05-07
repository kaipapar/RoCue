#include <curses.h>

int main(int argc, char** argv)
{
  initscr();

  printw("Main window");

  WINDOW* subwindow = newwin(10,20,5,15);

  refresh();

  box(subwindow,0,0);
  mvwprintw(subwindow, 1, 1, "subwindow");


  refresh();
  wrefresh(subwindow);

  getch();
  delwin(subwindow);

  endwin();
  return 0;
}