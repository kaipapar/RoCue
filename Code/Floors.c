/**
 * @file Floors.c
 * @brief File for floor-struct related functions
 * @authors Karri Korsu, Nestori Heiskanen
*/
#include "Rogue.h"

/**
 * Creates an array of map data. This function is really crucial.
 * It initializes the game which is then rendered on the screen.
 * It kind of finalizes the initialization.
 * @param[in]:
 * @param[out]:
 * @return A floor struct array, containing map data
*/
struct Floor* floorArrayCreation()
{
    struct Floor* floorArray = calloc(MAP_DEPTH, sizeof(struct Floor));
    EC((struct Floor*)floorArray); ///< Checks that the calloc worked
    for (int i = 0; i < MAP_DEPTH; i++)
    {
            floorArray[i].map = mapTileCreation();
            floorArray[i].rooms = mapSetup(floorArray[i].map);
            floorArray[i].stairs = stairsCreation(floorArray[i].map);


            floorArray[i].coinArray = coinCreation(floorArray[i].map);            
            floorArray[i].orc = enemyCreation(floorArray[i].map);
    }
    return floorArray;
}