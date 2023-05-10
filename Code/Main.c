/**
 * @file Main.c
 * @brief This file is run first.
 * @authors Karri Korsu, Nestori Heiskanen 
*/
#include "Rogue.h"

int currentFloor = 0;

/**
 * Sets up the run essential variables.
 * 
*/
int main()
{   
    //int currentFloor = 0; //To be used in a future update
    //extern struct Floor* floorList; 
    
    setupCurses();
    
    time_t t = 0; 
	srand((unsigned) time(&t)); ///< Sets up the seed for random generation to start of epoch

    //floorList = generateFloor();
/*
    map = mapTileCreation();

    posStart = mapSetup();  

    player = playerCreation(posStart);

    coinArray = coinCreation();
    
    orc = enemyCreation();

    stairs = stairsCreation();
*/
    menuDraw(); // --> Engine.c/Gameloop starts

    //  quitGame(); nECESSARY?

    return 0;
}