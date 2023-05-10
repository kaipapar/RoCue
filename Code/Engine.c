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
    struct Tile*** map = mapTileCreation();

    struct Position posStart = mapSetup(map);  

    struct Entity* player = playerCreation(posStart);

    struct Entity* coinArray = coinCreation(map);
    
    struct Entity* orc = enemyCreation(map);

    struct Entity* stairs = stairsCreation(map);
    createFOV(player, map, coinArray, orc, stairs);
    //menuDraw();
    allDraw(map, posStart, player, coinArray, orc, stairs);
    
    while(true)
    {       
        ch = getch();   
        if(ch == KEY_F(2))
        {
            break;
            quitGame(player, map);
            endwin();
        }
        inputHandling(ch, player, map, coinArray, orc, stairs);
        allDraw(map, posStart, player, coinArray, orc, stairs);
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
void quitGame(struct Entity* player, struct Tile*** map)
{
    free(player);
    releaseMap(map);
    endwin();
    exit(1);
}