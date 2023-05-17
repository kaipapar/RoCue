/*
@File    :   Player.c
@Time    :   14.04.2023 17:31:50
@Author  :   Karri Korsu, Nestori Heiskanen
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
#include "Rogue.h"

//struct Position posStart; // ???
/**
 * CREATE CUSTOM STRUCT FOR PLAYER WHICH 'INHERITS' ENTITY STRUCT
 */
struct Entity* playerCreation(struct Position posStart)
{
    struct Entity* newPlayer = calloc(1, sizeof(struct Entity)); //correct use of calloc?
    EC((struct Entity*) newPlayer);
    newPlayer->pos.y = posStart.y;
    newPlayer->pos.x = posStart.x;
    newPlayer->color = COLOR_PAIR(VISIBLE_COLOR);
    newPlayer->ch = '@';
    newPlayer->visible = true;
    newPlayer->points = 0;
    newPlayer->value = 0;
 
    return newPlayer;
}

/*  Handle user input */
void inputHandling(int input, struct Entity* player, 
                    struct Floor* floorArray, int* currentFloorPTR)
{
    struct Position newPos = { player->pos.y, player->pos.x };

    switch (input)
    {
        case 'w':
            newPos.y--;
            break;
        case 's':
            newPos.y++;
            break;
        case 'a':
            newPos.x--;
            break;
        case 'd':
            newPos.x++;
            break;
        case KEY_F(2):
            quitGame(player, floorArray);
            break;
        case 'i':
            // interact
            interact(player, floorArray, currentFloorPTR);
            //int localFloor = currentFloor;
            //newPos = floorArray[4].posStart;        ////////////////////    This is where you continue
            break;
        
        default:
            break;
    }

    playerMovement(newPos, player, floorArray, currentFloorPTR);
}

/*  Checks whether movement over a certain block is allowed */
void playerMovement(struct Position newPos, 
                    struct Entity* player, struct Floor* floorArray, int* currentFloorPTR)
{
    if (floorArray[*currentFloorPTR].map[newPos.y][newPos.x].walkable)
    {
        clearFOV(player, floorArray, currentFloorPTR);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        createFOV(player, floorArray, currentFloorPTR);
    }
}

void interact(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR)
{
    int dice = 0;
    for (int i = 0; i < COIN_COUNT+1; i++)
    {
        if (player->pos.y == (floorArray[*currentFloorPTR].coinArray + i)->pos.y 
            && player->pos.x == (floorArray[*currentFloorPTR].coinArray + i)->pos.x)
        {
            player->points += (floorArray[*currentFloorPTR].coinArray + i)->value;
            (floorArray[*currentFloorPTR].coinArray + i)-> visible = false;
            (floorArray[*currentFloorPTR].coinArray + i)-> collected = true;
        }
        else if (player->pos.y == floorArray[*currentFloorPTR].orc->pos.y 
                && player->pos.x == floorArray[*currentFloorPTR].orc->pos.x 
                && floorArray[*currentFloorPTR].orc->collected == false)
        {
            dice = rand() % 20;
            if (dice < 10)
            {
                player->points -= 100;
            }
            else
            {
                floorArray[*currentFloorPTR].orc->points -= 300;
            }
            floorArray[*currentFloorPTR].orc->collected = true;
        }
    }
    //____________________________________
    if (player->pos.y == floorArray[*currentFloorPTR].stairs->pos.y 
            && player->pos.x == floorArray[*currentFloorPTR].stairs->pos.x)
    {
        changeFloor(1, currentFloorPTR);
        //int localFloor = currentFloor; ///< Need to localize current floor. If not localized, incrementing on it would change the floor altogether.
        //struct Position newPos = {floorArray[localFloor++].posStart->y,floorArray[localFloor++].posStart->x};
        //int newFloor = *currentFloorPTR + 1;
        //*currentFloorPTR = newFloor;    // <- this works.   this doesnt -> currentFloorPTR = &newFloor;
        playerMovement(floorArray[*currentFloorPTR].stairs->pos, player, floorArray, currentFloorPTR);
        //player->pos.y = 0;
        //player->pos.x = 0;

        //currentFloor++;
    }
}

/**
 * @brief Function which changes floors either up or down
 * @param[in] floorChange : negative or positive integer which states how many floors we want to go up or down.
*/
void changeFloor(int floorChange, int* currentFloorPTR)
{
    int newFloor = *currentFloorPTR + floorChange;
    if (newFloor < MAP_DEPTH && 0 < newFloor)
    {
        *currentFloorPTR = newFloor;    ///< Swaps the data in mem location of currentFloor to whatever newFloor is.

    }
}