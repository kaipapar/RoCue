/*
@File    :   Draw.c
@Time    :   14.04.2023 18:36:51
@Author  :   Karri Korsu, Nestori Heiskanen
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/

#include "Rogue.h"


void mapDrawing()
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[currentFloor][y][x].visible)
            {
                mvaddch(y, x, map[currentFloor][y][x].ch | map[currentFloor][y][x].color);
            }
            else if (map[currentFloor][y][x].seen)
            {
                mvaddch(y, x, map[currentFloor][y][x].ch | COLOR_PAIR(SEEN_COLOR));
            }
            else
            {
                mvaddch(y, x, ' ');
            }
        }
    }
}

void entityDrawing(struct Entity* entity)
{
    if (entity -> visible == true)
    {
        mvaddch(entity->pos.y, entity->pos.x, entity->ch | entity->color);  
        //arguments (y,x,affected item)
    }
    if (entity -> points < 0)
    {
        entity -> collected = true;
    }
}

void coinDrawing()
{
    for(int i = 0; i < COIN_COUNT; i++)
    {
        if ((coinArray + i)->visible == true)
        {
        mvaddch((coinArray + i) -> pos.y, (coinArray + i) -> pos.x, (coinArray + i) -> ch | (coinArray + i)-> color);
        }

    }
}

void allDraw()
{
    clear();    // clears the screen before refreshing
    mapDrawing(); // renders the game map
    entityDrawing(player);
    coinDrawing(); // temporary testing function (replace later)
    entityDrawing(orc); // orc is similar to player
    entityDrawing(stairs);
    infoBoxDraw(); // UI element rendering for controls info
}

void infoBoxDraw()
{
        /*  Subwindow for printing game information */
    WINDOW* subwindow = newwin(13,30,5,100);
    refresh();
    box(subwindow,0,0);

    char hintBoxContent[] = "RoCue is a roguelike game \n"
                            "where you battle creeps! \n"
                            "Movement - WASD \n"
                            "Quit - F2 \n"
                            "Interact - I \n"
                            "Inventory - E";
    mvwprintw(subwindow, 1, 1, "Welcome to RoCue\n %s \n Y: %d, X: %d \n Floor: %d \n Points: %d", hintBoxContent,player->pos.y, player->pos.x, currentFloor, player -> points);
    //mvwprintw(subwindow,1,1,"Player y position: %d, x position: %d",);
    refresh();
    wrefresh(subwindow);
}


