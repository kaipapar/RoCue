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

/**
 * Initializes the enemy entity
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
 * Returns a new position which is closer to end than original position.
*/
struct Position getCloser(struct Position start, struct Position end, struct Tile** map)
{
    struct Position newPos = start; ///< local position to be returned
    
    // Is is possible to do without these added variables? 
    // When I tried doing arithmetic inside if clauses bugs appeared.
    struct Position startMin = start;
    startMin.x--;
    startMin.y--;
    
    struct Position startMax = start;
    startMax.x++;
    startMax.y++;

    if (map[start.y][startMin.x].walkable == true && abs(startMin.x - end.x) <= abs(start.x - end.x)) 
    //-> step left
        newPos.x--;
    else if (map[newPos.y][startMax.x].walkable == true && abs(startMax.x - end.x) <= abs(start.x - end.x)) 
    //-> step right
        newPos.x++;
    else if (map[startMin.y][newPos.x].walkable == true && abs(startMin.y - end.y) <= abs(start.y - end.y)) 
    //-> step up
        newPos.y--;
    else if (map[startMax.y][newPos.x].walkable == true && abs(startMax.y - end.y) <= abs(start.y - end.y)) 
    //-> step down
        newPos.y++;
    else
        newPos.x = 0, newPos.y = 0;

    return newPos;
}

/**
 * A default random path for the enemy to follow when player is not seen
*/
struct Position randomPath(struct Position start, struct Tile** map)
{
    int random = rand() % 5; 

    struct Position startMin = start;
    startMin.x--;
    startMin.y--;
    
    struct Position startMax = start;
    startMax.x++;
    startMax.y++;

    switch (random)
    {
        case 0:
        // --> step left
            if (map[start.y][startMin.x].walkable == true)
                start.x--;
            break;
        case 1:
        //  --> step right
            if (map[start.y][startMax.x].walkable == true)
                start.x++;
            break;
        case 2:
        //  --> step up
            if (map[startMin.y][start.x].walkable == true)
                start.y--;
            break;
        case 3:
        // --> step down
            if (map[startMax.y][start.x].walkable == true)
                start.y++;
            break;
        case 4:
        // --> do nothing
            break;
        default:
            break;
    }
    return start;
}

void moveEnemy(struct Entity *start, struct Position newPos, struct Tile** map)
{
    if (map[newPos.y][newPos.x].walkable == true)
    {
        start->pos.y = newPos.y;
        start->pos.x = newPos.x;
    }
}


//:::::  Not used :::::
/**
 * Generates an array of directions.
*/
struct Position* getDirections(struct Entity *start, struct Entity *end, struct Tile** map)
{
    // cursor 
    int cursor = 0;
    int lastcursor = cursor-1;
    // 
    struct Position* directions = calloc(STACKLIMIT, sizeof(struct Position));
    directions[cursor] = start->pos;

    while (directions[cursor].y != end->pos.y && directions[cursor].x != end->pos.x)
    {
        // add locations to directions
        cursor++;
        lastcursor++;
        directions[cursor] = getCloser(directions[lastcursor], end->pos, map); // Start here
        //cursor++;
    }
    return directions;
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



