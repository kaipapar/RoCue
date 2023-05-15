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
                    struct Floor* floorArray, int currentFloor)
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
            interact(player, floorArray);
            break;
        
        default:
            break;
    }

    playerMovement(newPos, player, floorArray, currentFloor);
}

/*  Checks whether movement over a certain block is allowed */
void playerMovement(struct Position newPos, 
                    struct Entity* player, struct Floor* floorArray, int currentFloor)
{
    if (floorArray[currentFloor].map[newPos.y][newPos.x].walkable)
    {
        clearFOV(player, floorArray, currentFloor);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        createFOV(player, floorArray, currentFloor);
    }
}

void interact(struct Entity* player, struct Floor* floorArray)
{
    int dice = 0;
    for (int i = 0; i < COIN_COUNT+1; i++)
    {
        if (player->pos.y == (floorArray[currentFloor].coinArray + i)->pos.y 
            && player->pos.x == (floorArray[currentFloor].coinArray + i)->pos.x)
        {
            player->points += (floorArray[currentFloor].coinArray + i)->value;
            (floorArray[currentFloor].coinArray + i)-> visible = false;
            (floorArray[currentFloor].coinArray + i)-> collected = true;
        }
        else if (player->pos.y == floorArray[currentFloor].orc->pos.y 
                && player->pos.x == floorArray[currentFloor].orc->pos.x 
                && floorArray[currentFloor].orc->collected == false)
        {
            dice = rand() % 20;
            if (dice < 10)
            {
                player->points -= 100;
            }
            else
            {
                floorArray[currentFloor].orc->points -= 300;
            }
            floorArray[currentFloor].orc->collected = true;
        }
    }
    //____________________________________
    if (player->pos.y == floorArray[currentFloor].stairs->pos.y 
            && player->pos.x == floorArray[currentFloor].stairs->pos.x)
    {
        changeFloor(1);
        playerMovement(floorArray[currentFloor].posStart, player, floorArray, currentFloor);

        //currentFloor++;
    }
}

/**
 * @brief Function which changes floors either up or down
 * @param[in] floorChange : negative or positive integer which states how many floors we want to go up or down.
*/
void changeFloor(int floorChange)
{
    int newFloor = currentFloor + floorChange;
    if (newFloor < MAP_DEPTH && 0 < newFloor)
    {
        currentFloor = newFloor;

    }
}