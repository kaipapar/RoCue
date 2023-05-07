/*
@File    :   Fov.c
@Time    :   15.04.2023 08:18:49
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
#include "Rogue.h"

void createFOV(struct Entity* player)
{
    int y = 0;
    int x = 0;
    int distance = 0;
    int radius = 15; // draw distance of the player
    struct Position target;

    map[currentFloor][player->pos.y][player->pos.x].visible = true;
    map[currentFloor][player->pos.y][player->pos.x].seen = true;

    for (y = player->pos.y - radius; y < player->pos.y + radius; y++)
    {
        for (x = player->pos.x - radius; x < player->pos.x + radius; x++)
        {
            target.y = y;
            target.x = x;
            distance = getDistance(player->pos, target);
            //printf("Target y: %d, target x: %d, player y, player x, distance");

            if (distance < radius && isInMap(y, x) && lineOfSight(player->pos, target))
            {
                map[currentFloor][y][x].visible = true;
                map[currentFloor][y][x].seen = true;
                for (int i = 0; i < COIN_COUNT; i++)
                {
                    if ((coinArray + i)->pos.y == y && (coinArray + i)->pos.x == x && (coinArray + i)->collected == false) 
                    {   //if there is a coin at these x,y coordinates
                        (coinArray + i)->visible = true;
                    }
                }

                if (orc -> pos.y == y && orc -> pos.x == x && orc->collected == false)
                {
                    orc -> visible = true;
                }

                if (stairs -> pos.y == y && stairs -> pos.x == x && stairs->collected == false)
                {
                    stairs -> visible = true;
                }
            }/*  Yes I know there is 3 nested for loops  */
        }
    }
}

void clearFOV(struct Entity* player)
{
    int y = 0;
    int x = 0;
    int radius = 15;

    for (y = player->pos.y - radius; y < player->pos.y + radius; y++)
    {
        for (x = player->pos.x - radius; x < player->pos.x + radius; x++)
        {
            if (isInMap(y,x))
            {
                map[currentFloor][y][x].visible = false;

                /*  clear fov of coins  */
                for (int i = 0; i < COIN_COUNT; i++)
                {/*
                    if (strcmp((coinArray + i)->pos.y, y) == 0 && strcmp((coinArray + i)->pos.x, x) == 0)
                    {   //if there is a coin at these x,y coordinates
                        (coinArray + i)->visible = false;
                    }*/
                    if ((coinArray + i)->pos.y == y && (coinArray + i)->pos.x == x)
                    {
                        (coinArray + i)->visible = false;
                    }
                }   

                /*  Clear fov of orc */
                if (orc -> pos.y == y && orc -> pos.x == x)
                {
                    orc -> visible = false;
                }
                if (stairs -> pos.y == y && stairs -> pos.x == x)
                {
                    stairs -> visible = false;
                }
            }
        }
    }

}

int getDistance(struct Position origin, struct Position target)
{
    double dy = 0;
    double dx = 0;
    int distance = 0;

    dx = target.x - origin.x;
    dy = target.y - origin.y;
    distance = floor(sqrt((dx * dx) + (dy * dy)));

    return distance;
}

bool isInMap(int y, int x)
{
    if((0 < y && y < MAP_HEIGHT - 1) && (0 < x && x < MAP_WIDTH - 1))
    {
        return true;
    }
    return false;
}

bool lineOfSight(struct Position origin, struct Position target)
{
    int t = 0;
    int x = 0;
    int y = 0;
    int xAbsDelta = 0;
    int yAbsDelta = 0;
    int xSign = 0;
    int ySign = 0;
    int xDelta = 0;
    int yDelta = 0;

    xDelta = origin.x - target.x;
    yDelta = origin.y - target.y;

    xAbsDelta = abs(xDelta);
    yAbsDelta = abs(yDelta);

    xSign = getSign(xDelta);
    ySign = getSign(yDelta);

    x = target.x;
    y = target.y;
    
    if (xAbsDelta > yAbsDelta)
    {
        t = yAbsDelta * 2 - xAbsDelta;

        while (map[currentFloor][y][x].transparent)
        {
            if (t >= 0)
            {
                y += ySign;
                t -= xAbsDelta * 2;
            }

            x += xSign;
            t += yAbsDelta * 2;

            if (x == origin.x && y == origin.y)
            {
                return true;
            }
        }
        return false;
    }
    else
    {
        t = xAbsDelta * 2 - yAbsDelta;

        while (map[currentFloor][y][x].transparent)
        {
            if (t >= 0)
            {
                x += xSign;
                t -= yAbsDelta * 2;
            }

            y += ySign;
            t += xAbsDelta * 2;

            if (x == origin.x && y == origin.y)
            {
                return true;
            }
        }
        return false;  
    }
}

int getSign(int a)
{
    if (a < 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}