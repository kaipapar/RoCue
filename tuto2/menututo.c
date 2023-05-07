#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4

char *choices[] = {
                        "Play!",
                        "Settings",
                        "Choice 3",
                        "Choice 4",
                        "Exit",
                  };

int main()
{	ITEM **my_items;
	int c;				
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;
	//WINDOW * menuWin = newwin();
	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	char *choices[] = {
                        "Play!",
                        "Settings",
                        "Choice 3",
                        "Choice 4",
                        "Exit",
                  };

	for(i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(choices[i], choices[i]);
	my_items[n_choices] = (ITEM *)NULL;

	my_menu = new_menu((ITEM **)my_items);
	mvprintw(LINES - 2, 0, "F1 to Exit, Arrow-Right to select");
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
				endwin();
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