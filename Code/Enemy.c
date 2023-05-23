/*
@File    :   Enemy.c
@Time    :   21.04.2023 12:56:08
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
#include "Rogue.h"
/** @file  Enemy creation, pathfinding, interaction with player    */

/*
Create enemy entity
    inherits from entity struct, 

*/
struct Entity* enemyCreation(struct Tile** map)
{
    struct Entity* orc = calloc(1, sizeof(struct Entity));
    EC((struct Entity*) orc);

    orc -> ch = 'O';
    orc -> color = COLOR_PAIR(COIN_COLOR);
    orc -> visible = false;
    orc -> transparent = false;
    orc -> points = 1000;

    int flag = 0;

    while (true)
    {
        int randomx = rand() % 100;
        int randomy = rand() % 25;

        if (map[randomy][randomx].walkable && flag == 0)
        {
            orc -> pos.x = randomx;
            orc -> pos.y = randomy;
            flag = 1;
            break;
        }
    }
    return orc;
}

void enemyPathFinding(struct Entity* orc, struct Entity* player, struct Tile** map)
{     //http://www.roguebasin.com/index.php/Quick_Pathfinding_in_a_Dungeon  
      //Find path between enemy and player, activated when orc sees player
    //  Using BFS

    // orc position
    struct Position origin = orc->pos;
    // player position
    struct Position target = player->pos;

    //int weight = 0; //To be used in a future update

    struct Position current = {0,0};

    // need for 'selected' variable ? 

    // mark adjacent positions with weight + 1
    // adjacent --> current; --y, --x, ++x, ++y
    struct Queue* queue = queueCreation();
    
    enqueue(queue, map[origin.y][origin.x]);
    visit(queue);

    while (!isEmpty(queue)) ///< While queue is not empty visit neighbours of current 
    {
        //  current = deque

        // visit neighbours
        if (currentX-- == 0 && map[currentY][currentX--].walkable == true)
        {   // operate on (x-1,y)
            map[currentY][currentX-1].found = map[currentY][currentX].found++;
        }
        else if (currentX++ == 0 && map[currentY][currentX++].walkable == true)
        {   //operate on (x+1,y)
            map[currentY][currentX+1].found = map[currentY][currentX].found++;
        }
        else if (currentY++ == 0 && map[currentY++][currentX].walkable == true)
        {   // operate on (x,y+1)
            map[currentY+1][currentX].found = map[currentY][currentX].found++;
        }
        else if (currentY-- == 0 && map[currentY--][currentX].walkable == true)
        {   // operate on (x,y-1)
            map[currentY-1][currentX].found = map[currentY][currentX].found++;
        
        }

        // once player has been found 
        if (currentX == targetX && currentY == targetY)
        {
            break;
        }
    }
}




