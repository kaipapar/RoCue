/**
 * @file Main.c
 * @brief This file is run first.
 * @authors Karri Korsu, Nestori Heiskanen 
*/
#include "Rogue.h"

/**
 * Sets up the run essential variables.
 * 
*/
int main()
{     
    setupCurses(); ///< Sets up Ncurses rendering.
    
    time_t t = 0; 
    unsigned seed = time(&t); ///< Sets up the seed for random generation to start of epoch
	srand(seed); ///< Randomization seeded!
    
    menuDraw(); // --> Engine.c/Gameloop starts

    return 0;
}