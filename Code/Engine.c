/*
@File    :   Engine.c
@Time    :   14.04.2023 18:09:18
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
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
/*
    int coinAmount = (rand() % 4) + 2;
    struct Entity* coins = coinCreation(coinAmount);
*/

    struct Floor* floorArray = floorArrayCreation();

    struct Position posStart = getStartPos(floorArray[currentFloor].rooms);  

    struct Entity* player = playerCreation(posStart);
/*    
    struct Tile** map = mapTileCreation();
    
    struct Entity* coinArray = coinCreation(map);
    
    struct Entity* orc = enemyCreation(map);

    struct Entity* stairs = stairsCreation(map);
*/

    createFOV(player, 
                floorArray[currentFloor].map, 
                floorArray[currentFloor].coinArray, 
                floorArray[currentFloor].orc, 
                floorArray[currentFloor].stairs);
    //menuDraw();
    allDraw(floorArray[currentFloor].map, 
            posStart, 
            player, 
            floorArray[currentFloor].coinArray, 
            floorArray[currentFloor].orc, 
            floorArray[currentFloor].stairs);
    
    while(true)
    {       
        ch = getch();   
        if(ch == KEY_F(2))
        {
            break;
            quitGame(player, floorArray);
            endwin();
        }
        inputHandling(ch, 
                        player, 
                        floorArray[currentFloor].map, 
                        floorArray[currentFloor].coinArray, 
                        floorArray[currentFloor].orc, 
                        floorArray[currentFloor].stairs);
        allDraw(floorArray[currentFloor].map, 
                posStart, 
                player, 
                floorArray[currentFloor].coinArray, 
                floorArray[currentFloor].orc, 
                floorArray[currentFloor].stairs);
        /*
        if (gameOver())
        {
            break;
        }*/
    }
}
/*
bool gameOver()
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
*/
void quitGame(struct Entity* player, struct Tile** map)
{
    free(player);
    releaseFloors(map, MAP_DEPTH);
    endwin();
    exit(1);
}

/**
 * Error Checking function for pointers
*/
void *EC(void *pointer)
{
	if (pointer == NULL)
	{
		fprintf(stderr, "Error, contiguous memory allocation failed");
		exit(-1);
	}
}