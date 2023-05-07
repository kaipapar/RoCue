/*
@File       :       Items.c
@Author     :       Joona Luttinen
@Version    :       1.0
@Description:       creates all needed items
*/

#include "Rogue.h"

struct Entity* coinCreation()
{
    int help = 0;   
    struct Entity* coinArray = calloc(COIN_COUNT, sizeof(struct Entity));

    for(int i = 0; i < COIN_COUNT; i++)
    {
        (coinArray + i) -> ch = 'C';
        (coinArray + i) -> color = COLOR_PAIR(COIN_COLOR);
        (coinArray + i) -> visible = false;
        (coinArray + i) -> transparent = false;
        (coinArray + i) -> value = rand() % 1000 + 500;
        (coinArray + i) -> collected = false;
    }

    while (true)
    {  
        int randomx = rand() % 100;
        int randomy = rand() % 25;

        if(map[currentFloor][randomy][randomx].walkable)
        {
            (coinArray + help) -> pos.y = randomy;
            (coinArray + help) -> pos.x = randomx;
            help += 1;
        }

        if(help == COIN_COUNT - 1)
        {
            break;
        }
    }

    return coinArray;
}