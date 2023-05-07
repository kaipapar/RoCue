/*
@File    :   Enemy.c
@Time    :   21.04.2023 12:56:08
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/
#include "Rogue.h"
/*  Enemy creation, pathfinding, interaction with player    */

/*
Create enemy entity
    inherits from entity struct, 

*/
struct Entity* enemyCreation()
{
    struct Entity* orc = calloc(1, sizeof(struct Entity));

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

        if (map[currentFloor][randomy][randomx].walkable && flag == 0)
        {
            orc -> pos.x = randomx;
            orc -> pos.y = randomy;
            flag = 1;
            break;
        }
    }
    return orc;
}

void enemyPathFinding()
{     //http://www.roguebasin.com/index.php/Quick_Pathfinding_in_a_Dungeon  
      //Find path between enemy and player, activated when orc sees player
    //  Using BFS
    // orc position
    int originX = orc -> pos.x;
    int originY = orc -> pos.y;
    // player position
    int targetX = player -> pos.x;
    int targetY = player -> pos.y;

    //int weight = 0; //To be used in a future update

    int currentX = 0;
    int currentY = 0;

    // need for 'selected' variable ? 

    // mark adjacent positions with weight + 1
    // adjacent --> current; --y, --x, ++x, ++y
    struct Queue* queue = queueCreation();
    enqueue(queue, map[currentFloor][originY][originX]);
    visit(queue);

    while (isEmpty(queue) == 0)
    {
        if (currentX-- == 0 && map[currentFloor][currentY][currentX--].walkable == true)
        {   // operate on (x-1,y)
            map[currentFloor][currentY][currentX-1].found = map[currentFloor][currentY][currentX].found++;
            

        }
        else if (currentX++ == 0 && map[currentFloor][currentY][currentX++].walkable == true)
        {   //operate on (x+1,y)
            map[currentFloor][currentY][currentX+1].found = map[currentFloor][currentY][currentX].found++;
        }
        else if (currentY++ == 0 && map[currentFloor][currentY++][currentX].walkable == true)
        {   // operate on (x,y+1)
            map[currentFloor][currentY+1][currentX].found = map[currentFloor][currentY][currentX].found++;
        }
        else if (currentY-- == 0 && map[currentFloor][currentY--][currentX].walkable == true)
        {   // operate on (x,y-1)
            map[currentFloor][currentY-1][currentX].found = map[currentFloor][currentY][currentX].found++;
        
        }
        else    
        {
            
        }


        // once player has been found 
        if (currentX == targetX && currentY == targetY)
        {
            break;
        }
    }
}




