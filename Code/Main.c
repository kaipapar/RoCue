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
int main(int argc, char *argv[])
{     
    setupCurses(); ///< Sets up Ncurses rendering.
    
    //:::  Throw seeding into engine so that it can be either defined through randomization or read from file   :::
    time_t t = 0; 
    unsigned seed = time(&t); ///< Sets up the seed for random generation to start of epoch
    
    if (argc > 1)
    {
        for (int i = 1; i < argc; i++)
        {
            if (strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--seed") == 0)
                seed = checkSeed(seed, argv[i]);
            else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
            {
                endwin();
                printf("Usage: Just play the game!\n '-s' is the argument for seeding. \n ... \n Exiting.");
                exit(0);
            }
        }
    }
	srand(seed); ///< Randomization seeded!
    
    menuDraw(); // --> Engine.c/Gameloop starts

    return 0;
}