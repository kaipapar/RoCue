/*
File:           Rogue.h
Authors:        Karri Korsu, Nestori Heiskanen, Joona Luttinen 
Description:    Header for rogue tutorial
*/

#ifndef ROGUE_H
#define ROGUE_H

#ifdef __unix__
#include <ncurses.h>
#include <menu.h>
#else
#include <curses.h>
#include "WINmenu.h"
#endif

#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>


// colour pairs
#define VISIBLE_COLOR 1
#define SEEN_COLOR 2
#define COIN_COLOR 1

//  macros for map dimensions
#define MAP_DEPTH 25
#define MAP_HEIGHT 25
#define MAP_WIDTH 100

//  macros for item amounts
#define COIN_COUNT 5

// macro for queue size
#define STACKLIMIT 100

/*  Struct to store positions of "objects"  */
struct Position
{
    int y;
    int x;
};

/*  Struct to store characteristics of tile "objects"   */
struct Tile 
{
    char ch;
    bool walkable; // Used to check can the space be moved to
    int color; // Color of rendered character in axis 0 (black) - 7 (white)
    bool transparent; // Does the tile block FoV 
    bool visible; // Is the tile visible to player
    bool seen; // Rendered by the engine after the tile leaves player's FoV
    int found; // Needed for pathfinding
    bool visited; // needed for pathfinding
};

/*  Attributes of a dungeon */
struct Room
{
    int roomHeight;
    int roomWidth;
    struct Position pos;
    struct Position center;
};

/*  Struct to store positions and representations of "objects"  */
struct Entity
{
    struct Position pos; //x,y coordinates
    char ch;      // what the object is represented as in ASCII form
    int color; // color of rendered character in axis 0 (black) - 7 (white)

    bool visible;
    bool transparent;
    int points;
    int value;
    bool collected;
};

/*  Queue struct for pathfinding    */
struct Queue
{
    int end;                        ///< end of the queue
    int front;                      ///< front of the queue
    struct Tile data[STACKLIMIT];   ///< data is an array which contains tiles in the queue
};


/*      PLAYER STRUCT HERE :::  */

/*      ITEM STRUCT HERE :::    
INHERITS FROM ENTITY AND TILE
*/

/**
 * Struct which holds floor specific data
*/
struct Floor
{
    /// @brief map related 
    struct Tile** map;
    struct Room* rooms;     // do these need their own pointers  
    struct Entity* stairs;  // if they are only accessed through Floor?
    struct Position posStart; 

    /// @brief entities   
    struct Entity* orc; 
    struct Entity* coinArray;

};

// Draw.c
void mapDrawing(struct Tile** map);
void entityDrawing(struct Entity* entity);
void entitiesDrawing(struct Entity* entityArray, int entityCount);
void allDraw(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
void infoBoxDraw(struct Entity* player, int* currentFloorPTR, struct Floor* floorArray);

// Engine.c
void setupCurses();
void gameLoop(); ///< Initializes all variables
void upkeep(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
bool gameOver(struct Entity* player);
void quitGame(struct Entity* player, struct Floor* floorArray); ///< Doesn't take currentFloor as argument because all floors are freed
void EC(void *pointer); 

// Map.c
struct Tile** mapTileCreation();
struct Room* mapSetup(struct Tile** map);
struct Position getStartPos(struct Room* rooms);
struct Entity* stairsCreation(struct Tile** map);

// Player.c
struct Entity* playerCreation(struct Position posStart);
void inputHandling(int input, struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
void playerMovement(struct Position newPos, struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
void endTurn(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
void interact(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
void changeFloor(int floorChange, int* currentFloorPTR);

// Room.c
struct Room roomCreation(int y, int x, int height, int width);
void addRoomToMap(struct Room room, struct Tile** map);
void roomConnections(struct Position centerSelf, struct Position centerOther, struct Tile** map);

// Fov.c
void createFOV(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
void clearFOV(struct Entity* player, struct Floor* floorArray, int* currentFloorPTR);
int getDistance(struct Position origin, struct Position target);
bool isInMap(int y, int x);
bool lineOfSight(struct Position origin, struct Position target, struct Tile** map);
int getSign(int a);

// Items.c
struct Entity* coinCreation(struct Tile** map);

// Enemy.c
struct Entity* enemyCreation(struct Tile** map);
struct Position* enemyPathFinding(struct Entity* orc, struct Entity* player, struct Tile** map);
struct Position getCloser(struct Position start, struct Position end, struct Tile** map);
struct Position* getDirections(struct Entity *start, struct Entity *end, struct Tile** map);
void moveEnemy(struct Entity *start, struct Position newPos, struct Tile** map);
struct Position randomPath(struct Position start, struct Tile** map);


// Queue.c
struct Queue* queueCreation();
void enqueue(struct Queue *queue, struct Tile tile);
struct Tile dequeue(struct Queue *queue);
struct Tile end(struct Queue *queue);
bool isEmpty(struct Queue *queue);
bool isFull(struct Queue *queue);
void visit(struct Queue *queue);

// Floors.c
struct Floor* floorArrayCreation();

//MenuUnix.c
void menuDraw();

//extern int currentFloor;

//extern struct Position posStart;

#endif
