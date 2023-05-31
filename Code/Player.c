/*
@File    :   Player.c
@Time    :   14.04.2023 17:31:50
@Author  :   Karri Korsu, Nestori Heiskanen
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
#include "Rogue.h"

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

/**  Handle user input */
void inputHandling(int input, struct Entity* player, 
                    struct Floor* floorArray, int* currentFloorPTR)
{
    struct Position newPos = { player->pos.y, player->pos.x };

    switch (input)
    {
        case 'w':
            newPos.y--;
            playerMovement(newPos, player, floorArray, currentFloorPTR);
            break;
        case 's':
            newPos.y++;
            playerMovement(newPos, player, floorArray, currentFloorPTR);
            break;
        case 'a':
            newPos.x--;
            playerMovement(newPos, player, floorArray, currentFloorPTR);
            break;
        case 'd':
            newPos.x++;
            playerMovement(newPos, player, floorArray, currentFloorPTR);
            break;
        case KEY_F(2):
            quitGame(player, floorArray);
            break;
        case 'i':
            interact(player, floorArray, currentFloorPTR);
            break;
        default:
            break;
    }

    endTurn(player, floorArray, currentFloorPTR);
}

/**  Checks whether movement over a certain block is allowed */
void playerMovement(struct Position newPos, 
                    struct Entity* player, struct Floor* floorArray, int* currentFloorPTR)
{
    if (floorArray[*currentFloorPTR].map[newPos.y][newPos.x].walkable)
    {
        //clearFOV(player, floorArray, currentFloorPTR);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        //createFOV(player, floorArray, currentFloorPTR);
    }
}

void endTurn(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR)
{
        clearFOV(player, floorArray, currentFloorPTR);
        createFOV(player, floorArray, currentFloorPTR);
}

void interact(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR)
{
    int dice = 0;

    /// Interacting with coins
    for (int i = 0; i < COIN_COUNT+1; i++)
    {
        if (player->pos.y == (floorArray[*currentFloorPTR].coinArray + i)->pos.y 
            && player->pos.x == (floorArray[*currentFloorPTR].coinArray + i)->pos.x)
        {
            player->points += (floorArray[*currentFloorPTR].coinArray + i)->value;
            (floorArray[*currentFloorPTR].coinArray + i)-> visible = false;
            (floorArray[*currentFloorPTR].coinArray + i)-> collected = true;
        }
    }

    /// Interacting with the enemy
    if (player->pos.y == floorArray[*currentFloorPTR].orc->pos.y 
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

    ///  Interacting with stairs
    if (player->pos.y == floorArray[*currentFloorPTR].stairs->pos.y 
            && player->pos.x == floorArray[*currentFloorPTR].stairs->pos.x)
    {
        changeFloor(1, currentFloorPTR);
        playerMovement(floorArray[*currentFloorPTR].stairs->pos, player, floorArray, currentFloorPTR);
    }
}

/**
 * @brief Function which changes floors either up or down
 * @param[in] floorChange : negative or positive integer which states how many floors we want to go up or down.
*/
void changeFloor(int floorChange, int* currentFloorPTR)
{
    int newFloor = *currentFloorPTR + floorChange;  // <- this works.   this doesnt -> currentFloorPTR = &newFloor;
    if (newFloor < MAP_DEPTH && 0 < newFloor)
    {
        *currentFloorPTR = newFloor;    ///< Swaps the data in mem location of currentFloor to whatever newFloor is.
    }
}