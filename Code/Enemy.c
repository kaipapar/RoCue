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
/**
 * Finds the shortest path to a player and returns it as an array of position structs

struct Position* enemyPathFinding(struct Entity* orc, struct Entity* player, struct Tile** map)
{     //http://www.roguebasin.com/index.php/Quick_Pathfinding_in_a_Dungeon  
      //Find path between enemy and player, activated when orc sees player
    //  Using BFS
    // Local map though which is the 
    struct Tile** localMap = map;
    // orc position
    struct Position origin = orc->pos;
    // player position
    struct Position target = player->pos;

    //int weight = 0; //To be used in a future update

    struct Position currentNode = {0,0};

    // need for 'selected' variable ? 

    // mark adjacent positions with weight + 1
    // adjacent --> current; --y, --x, ++x, ++y
    struct Queue* queue = queueCreation();

    currentNode = origin;
    
    enqueue(queue, map[currentNode.y][currentNode.x]);
    visit(queue);   // This needs to alter the data in map

    while (!isEmpty(queue)) ///< While queue is not empty visit neighbours of current 
    {
        //  current = deque
        currentNode = deque(queue);
        // visit neighbours
        if ( && map[currentY][currentX--].walkable == true)
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
    struct Position* shortestPath = calloc(STACKLIMIT, sizeof(struct Position));
    return shortestPath;
}
*/
/**
 * Returns a new position which is closer to end than original position.
*/
struct Position getCloser(struct Entity *start, struct Entity *end)
{
    struct Position newPos = start->pos; ///< local position to be returned
    if (abs(start->pos.x-1 - end->pos.x) < abs(start->pos.x - end->pos.x)) //-> step left
        newPos.x--;
    else if (abs(start->pos.x+1 - end->pos.x) < abs(start->pos.x - end->pos.x)) //-> step right
        newPos.x++;
    else if (abs(start->pos.y-1 - end->pos.x) < abs(start->pos.y - end->pos.x)) //-> step up
        newPos.y--;
    else if (abs(start->pos.y+1 - end->pos.x) < abs(start->pos.y - end->pos.x)) //-> step down
        newPos.y++;

    return newPos;
}
/**
 * Generates an array of directions.
*/
struct Position* getDirections(struct Entity *start, struct Entity *end)
{
    // cursor 
    int cursor = 0;
    // 
    struct Position* directions = calloc(STACKLIMIT, sizeof(struct Position));
    struct Entity *localStart = start;
    struct Entity *localEnd = end;
    while (localStart->pos.y != localEnd->pos.y && localStart->pos.x != localEnd->pos.x)
    {
        // add locations to directions
        directions[cursor] = getCloser(directions[cursor--], end); // Start here
        cursor++;
    }
    return directions;
}
void moveEnemy(struct Entity *start, struct Position newPos)
{
    start->pos.y = newPos.y;
    start->pos.x = newPos.x;
}


