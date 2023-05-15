/*
@File    :   Draw.c
@Time    :   14.04.2023 18:36:51
@Author  :   Karri Korsu, Nestori Heiskanen
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/

#include "Rogue.h"


void mapDrawing(struct Tile** map)
{
    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (map[y][x].visible)
            {
                mvaddch(y, x, map[y][x].ch | map[y][x].color);
            }
            else if (map[y][x].seen)
            {
                mvaddch(y, x, map[y][x].ch | COLOR_PAIR(SEEN_COLOR));
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

/**
 * @brief A function which renders an array of entities, eg. coinArray
 * @param[in] entityArray : placeholder for any array of similar entities
 * @param[in] entityCount : getting the size of the array as argument is best practises
*/
void entitiesDrawing(struct Entity* entityArray, int entityCount)
{
    for(int i = 0; i < entityCount; i++)
    {
        if ((entityArray + i)->visible == true)
        {
            mvaddch((entityArray + i) -> pos.y, 
                    (entityArray + i) -> pos.x, 
                    (entityArray + i) -> ch | (entityArray + i)-> color);
        }
    }
}

void allDraw(struct Entity* player, struct Floor* floorArray, int currentFloor)
{
    clear();    // clears the screen before refreshing
    mapDrawing(floorArray[currentFloor].map); // renders the game map
    entityDrawing(player);
    entitiesDrawing(floorArray[currentFloor].coinArray, COIN_COUNT); // temporary testing function (replace later)
    entityDrawing(floorArray[currentFloor].orc); // orc is similar to player
    entityDrawing(floorArray[currentFloor].stairs);
    infoBoxDraw(player); // UI element rendering for controls info
}

void infoBoxDraw(struct Entity* player)
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


