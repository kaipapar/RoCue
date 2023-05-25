/*
@File    :   Engine.c
@Time    :   14.04.2023 18:09:18
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
/**
 * @file Engine.c
 * @brief Initializes game and starts game loop. 
 * @authors Karri Korsu, Nestori Heiskanen 
*/
#include "Rogue.h"

void setupCurses()
{
    initscr();
    noecho();
    curs_set(0);


    if (has_colors())
    {
        start_color();

        init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
        init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
    }
}
/**
 * Initializes game object and sets up game. Runs gameloop
 *
*/
void gameLoop()
{
    int ch = 45; // init as '0'

    struct Floor* floorArray = floorArrayCreation();

    //struct Position posStart = getStartPos(floorArray[*currentFloorPTR].rooms); // Is this ok? or is a local .rooms made? Does it matter? Does anything matter?  
    int currentFloor = 0;      // Now currentfloor is local, not global
    int* currentFloorPTR = &currentFloor;   ///< remember the mem loc of current floor
    struct Entity* player = playerCreation(floorArray[*currentFloorPTR].posStart);

    createFOV(player, floorArray, currentFloorPTR);
    allDraw(player, floorArray, currentFloorPTR);
    
    while(true)
    {       
        ch = getch();   
        if(ch == KEY_F(2))
        {
            break;
            quitGame(player, floorArray);
        }
        inputHandling(ch, 
                        player, 
                        floorArray, currentFloorPTR);
        allDraw(player, floorArray, currentFloorPTR);
        enemyPathFindingSimple(floorArray[currentFloor].orc, player);
        if (gameOver(player))
        {
            break;
            quitGame(player, floorArray);
        }
    }
}
/**
 * Not fully implemented yet, but should work.
*/
bool gameOver(struct Entity* player)
{
    if (player->points < 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * frees allocated memory, exits ncurses, exits program.
*/
void quitGame(struct Entity* player, struct Floor* floorArray)
{
    //It is questionable whether free() works now but this is a shot at it
    free(player);
    for (int i = 0; i<MAP_DEPTH; i++)
    {
        free(floorArray[i].orc);
        free(floorArray[i].stairs);
        free(floorArray[i].coinArray);
        free(floorArray[i].map);
        // ::::free queue also when it is implemented::::
    }
    free(floorArray);
    endwin();
    exit(1);
}

/**
 * Error Checking function for pointers, use with all mem allocation
*/
void EC(void *pointer)
{
	if (pointer == NULL)
	{
		fprintf(stderr, "Error, contiguous memory allocation failed");
		exit(-1);
	}
}