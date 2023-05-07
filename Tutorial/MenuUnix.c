/*
@File    :   menuUnix.c
@Time    :   17.04.2023 14:58:48
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/


#include "Rogue.h"

#ifdef __unix__

void menuDraw()
{
    //WINDOW* menuWin = newwin(0,0,MAP_HEIGHT,MAP_WIDTH);
    //box(menuWin,0,0);
    refresh();
    ITEM *myItems[5];
	int c = 0;				
	MENU *myMenu;  // Cannot be initialized to null, causes seg fault
	int nChoices = 5;
	//ITEM *cur_item = NULL;

    keypad(stdscr, TRUE);

    char *choices[] = {
                        "Play!",
                        "Settings",
                        "Choice 3",
                        "Choice 4",
                        "Exit",
                  };
    
    int choice = 0; //   used to select an item

    for(int i = 0; i < nChoices; ++i)
    {
        myItems[i] = new_item(choices[i], choices[i]);
    }
    
    myItems[nChoices] = (ITEM *)NULL;
	myMenu = new_menu((ITEM **)myItems);
    set_menu_mark(myMenu, " * ");

	mvprintw(LINES - 2, 0, "F2 to Exit, Arrow-Right to select");
	post_menu(myMenu);
    
	refresh();

	while((c = getch()))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(myMenu, REQ_DOWN_ITEM);
                choice++;
                if (choice == nChoices)
                {
                    choice--;
                }
				break;
			case KEY_UP:
				menu_driver(myMenu, REQ_UP_ITEM);
                choice--;
                if (choice == -1)
                {
                    choice++;
                }
				break;
			case KEY_RIGHT:
				menu_driver(myMenu, REQ_TOGGLE_ITEM);
                if (choice == 0)
                {
                    gameLoop();
                }
                else 
                {
                    break;
                }
                free_item(myItems[0]);
				free_item(myItems[1]);

                unpost_menu(myMenu);
				break;
			case KEY_F(2):
				free_item(myItems[0]);
				free_item(myItems[1]);
				//free_menu(my_menu);
                quitGame();
				break;
		}
	}
}

#else

void menuDraw()
{
    ITEM **my_items;
    MENU *my_menu;
    int n_choices = 5;
    int choice = 0;
    int c;

    initscr();
    clear();
    noecho();
    cbreak();

    keypad(stdscr, TRUE);

    char *choices[] = {
                        "Play!",
                        "Settings",
                        "Choice 3",
                        "Choice 4",
                        "Exit",
                  };
    

    my_items = (ITEM **)malloc((n_choices + 1) * sizeof(ITEM *));
    for (int i = 0; i < n_choices; i++)
    {
        my_items[i] = new_item(choices[i], choices[i]);
    }

    my_menu = new_menu((ITEM **)my_items);

    post_menu(my_menu);
    refresh();

    while ((c = getch()))
    {
        switch (c)
        {
            case KEY_DOWN:
                menu_driver(my_menu, REQ_DOWN_ITEM);
                if (choice < n_choices - 1)
                {
                    choice++;
                }
                break;

            case KEY_UP:
                menu_driver(my_menu, REQ_UP_ITEM);
                if (choice > 0)
                {
                    choice--;
                }
                break;

            case 10: // Enter key
            {
                ITEM *cur;
                cur = current_item(my_menu);
                mvprintw(LINES - 2, 0, "You have chosen item: %s", item_name(cur));
                pos_menu_cursor(my_menu);
                break;
            }

            case KEY_F(1):
                goto cleanup;

            default:
                break;
        }
    }

cleanup:
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (int i = 0; i < n_choices; ++i)
    {
        free_item(my_items[i]);
    }
    endwin();
}

#endif
