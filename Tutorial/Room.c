/*
@File    :   room.c
@Time    :   14.04.2023 20:07:56
@Author  :   Karri Korsu, Nestori Heiskanen
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/

#include "Rogue.h"

struct Room roomCreation(int y, int x, int height, int width)
{
    struct Room newRoom;

    newRoom.pos.y = y;
    newRoom.pos.x = x;
    newRoom.roomHeight = height;
    newRoom.roomWidth = width;
    newRoom.center.y = y + (int)(height / 2);
    newRoom.center.x = x + (int)(width / 2);    

    return newRoom;
}

void addRoomToMap(struct Room room)
{
    for (int y = room.pos.y; y < room.pos.y + room.roomHeight; y++)
    {
        for (int x = room.pos.x; x < room.pos.x + room.roomWidth; x++)
        {
            map[currentFloor][y][x].ch = '.';
            map[currentFloor][y][x].walkable = true;
            map[currentFloor][y][x].transparent = true;
        }
    }
}

// Draws new room connections between the centers of 2 rooms and builds hallways on the map
void roomConnections(struct Position centerSelf, struct Position centerOther)
{
    struct Position temp;
    
    temp.x = centerSelf.x;
    temp.y = centerSelf.y;

    while (true)
    {
        if (abs((temp.x - 1) - centerOther.x) < abs(temp.x - centerOther.x))
        {
            temp.x--;
        }
        else if (abs((temp.x + 1) - centerOther.x) < abs(temp.x - centerOther.x))
        {
            temp.x++;
        }
        else if (abs((temp.y + 1) - centerOther.y) < abs(temp.y - centerOther.y))
        {
            temp.y++;
        }
        else if (abs((temp.y - 1) - centerOther.y) < abs(temp.y - centerOther.y))
        {
            temp.y--;
        }
        else
        {
            break;
        }
        
        map[currentFloor][temp.y][temp.x].ch = '.';
        map[currentFloor][temp.y][temp.x].walkable = true;
        map[currentFloor][temp.y][temp.x].transparent = true;
    }
}