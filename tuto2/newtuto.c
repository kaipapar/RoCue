#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

void subWinDraw()
{
        /*  Subwindow for printing game information */
    WINDOW* subwindow = newwin(10,30,5,100);
    refresh();
    box(subwindow,0,0);
    mvwprintw(subwindow, 1, 1, "Welcome to RoCue! \n RoCue is a roguelike game \n where you battle creeps!");
    refresh();
    wrefresh(subwindow);
}

char *choices[] = {
                        "Play!",
                        "Settings",
                        "Choice 3",
                        "Choice 4",
                        "Exit",
                  };

int main()
{	ITEM **my_items;
	/*
	int c;				
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;*/

	int c = 0;				
	MENU *my_menu;
	int n_choices = 5;
	ITEM *cur_item = NULL;
	WINDOW * menuWin = newwin(0,0,50,50);
	box(menuWin, 0, 0);
	refresh();
	wrefresh(menuWin);
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
    keypad(menuWin, TRUE);

	for(int i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(choices[i], choices[i]);
	my_items[n_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
	mvprintw(50, 0, "F1 to Exit, Arrow-Right to select");
	post_menu(my_menu);
	refresh();

	while((c = getch()))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case KEY_RIGHT:
				menu_driver(my_menu, REQ_TOGGLE_ITEM);
				free_item(my_items[0]);
				free_item(my_items[1]);
				free_menu(my_menu);
				unpost_menu(my_menu);
				subWinDraw();
				break;
			case KEY_F(1):
				free_item(my_items[0]);
				free_item(my_items[1]);
				free_menu(my_menu);
				endwin();
				break;
		}
	}	
	
	
}
