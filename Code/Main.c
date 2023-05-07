/*
File:           Main.c
Author:         Karri Korsu, Nestori Heiskanen
Description:    main file for rogue tutorial
*/

#include "Rogue.h"

int currentFloor = 0;
 

struct Entity* player;
struct Tile*** map;
struct Entity* coinArray;
struct Entity* orc;
struct Entity* stairs;


int main()
{   
    struct Position posStart;
    
    //int currentFloor = 0; //To be used in a future update
    //extern struct Floor* floorList; 

    
    setupCurses();
    
    time_t t = 0;
	srand((unsigned) time(&t));

    //floorList = generateFloor();

    map = mapTileCreation();

    posStart = mapSetup();  

    player = playerCreation(posStart);

    coinArray = coinCreation();
    
    orc = enemyCreation();

    stairs = stairsCreation();

    menuDraw(); // --> Engine.c/Gameloop starts

    quitGame();

    return 0;
}