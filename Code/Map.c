/**
*@file    :   Map.c
*@time    :   14.04.2023 18:28:12
*@author  :   Karri Korsu, Nestori Heiskanen
*@version :   1.0
*@contact :   karri.korsu@edu.turkuamk.fi
*@description:   None
*/


#include "Rogue.h"

/**
 *   Creates a 2d array of tiles for the map, returns pointer to pointer
 */
struct Tile** mapTileCreation()
{
    struct Tile** tiles = calloc(MAP_HEIGHT, sizeof(struct Tile**));
    EC((struct Tile**) tiles);
    
    // v Unsure if necessary
    //tiles = calloc(MAP_WIDTH, sizeof(struct Tile*));
    //EC((struct Tile*) tiles);

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        // how does this work. tiles = map_width x pointers to tiles.
        // tiles[y] --> one tile from those tiles?? Why calloc?
        // isn't this like saying int x = calloc(1, sizeof(int))
        tiles[y] = calloc(MAP_WIDTH, sizeof(struct Tile));  
        //EC((struct Tile) tiles[y]);

        for (int x = 0; x < MAP_WIDTH; x++)
        {
            tiles[y][x].ch = '#';   // walls
            tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
            tiles[y][x].walkable = false;
            tiles[y][x].transparent = false;
            tiles[y][x].visible = false;
            tiles[y][x].seen = false;
            tiles[y][x].found = 0;
        }
    }
    return tiles;
}

/**
 * Adding an area on the map to walk on
*/
struct Room* mapSetup(struct Tile** map)
// #accessthroughpointers
{
    int y = 0;
    int x = 0;
    int height = 0;
    int width = 0;
    int n_rooms = 0;

    n_rooms = (rand() % 11) + 5;

    struct Room* rooms = calloc(n_rooms, sizeof(struct Room));
    EC((struct Room*)rooms);


    for (int i = 0; i < n_rooms; i++)
    {
        y = (rand() % (MAP_HEIGHT - 10)) + 1;
        x = (rand() % (MAP_WIDTH - 20)) + 1;
        height = (rand() % 7) + 3;
        width = (rand() % 15) + 5;
        rooms[i] = roomCreation(y, x, height, width);
        addRoomToMap(rooms[i], map);

        if (i > 0)
        {
            roomConnections(rooms[i-1].center, rooms[i].center, map);
        }
    }
    return rooms;
}

struct Position getStartPos(struct Room* rooms)
{
    struct Position posStart;
    posStart.y = rooms[0].center.y;
    posStart.x = rooms[0].center.x;

    return posStart;
}

struct Entity* stairsCreation(struct Tile** map)
{
    struct Entity* stairs = calloc(1, sizeof(struct Entity));
    EC((struct Entity*) stairs);
    stairs -> ch = '<';
    stairs -> color = COLOR_PAIR(COIN_COLOR);
    stairs -> visible = true;
    stairs -> transparent = false;
    stairs -> points = 1000;

    int flag = 0;

    while (true)
    {
        int randomx = rand() % 100;
        int randomy = rand() % 25;

        if (map[randomy][randomx].walkable && flag == 0)
        {
            stairs -> pos.x = randomx;
            stairs -> pos.y = randomy;
            flag = 1;
            break;
        }
    }
    return stairs;
}