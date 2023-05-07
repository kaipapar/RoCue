/*
@File    :   Player.c
@Time    :   14.04.2023 17:31:50
@Author  :   Karri Korsu, Nestori Heiskanen
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
#include "Rogue.h"

struct Position posStart;
/*                       CREATE CUSTOM  STRUCT FOR PLAYER WHICH INHERITS ENTITY STRUCT       */
struct Entity* playerCreation(struct Position posStart)
{
    struct Entity* newPlayer = calloc(1, sizeof(struct Entity)); //correct use of calloc?

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
void inputHandling(int input)
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
            quitGame();
            break;
        case 'i':
            // interact
            interact();
            break;
        
        default:
            break;
    }

    playerMovement(newPos);
}

/*  Checks whether movement over a certain block is allowed */
void playerMovement(struct Position newPos)
{
    if (map[currentFloor][newPos.y][newPos.x].walkable)
    {
        clearFOV(player);
        player->pos.y = newPos.y;
        player->pos.x = newPos.x;
        createFOV(player);
    }
}

void interact()
{
    int dice = 0;
    for (int i = 0; i < COIN_COUNT+1; i++)
    {
        if (player->pos.y == (coinArray + i)->pos.y && player->pos.x == (coinArray + i)->pos.x)
        {
            player->points += (coinArray + i)->value;
            (coinArray + i)-> visible = false;
            (coinArray + i)-> collected = true;
        }
        else if (player->pos.y == orc->pos.y && player->pos.x == orc->pos.x && orc->collected == false)
        {
            dice = rand() % 20;
            if (dice < 10)
            {
                player->points -= 100;
            }
            else
            {
                orc->points -= 300;
            }
            orc->collected = true;
        }
    //____________________________________
        else if (player->pos.y == stairs->pos.y && player->pos.x == stairs->pos.x)
        {
            if (currentFloor == 6)
            {
                currentFloor--;
            } 
            currentFloor++;
            posStart = mapSetup();  
            player = playerCreation(posStart);
            coinArray = coinCreation();
            orc = enemyCreation();
            stairs = stairsCreation();
        }
    }
}