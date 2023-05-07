/*
@File    :   Queue.c
@Time    :   22.04.2023 15:40:37
@Author  :   Karri Korsu
@Version :   1.0
@Contact :   karri.korsu@edu.turkuamk.fi
@Desc    :   None
*/

#include "Rogue.h"


struct Queue* queueCreation()
{
    struct Queue* queue = calloc(STACKLIMIT, sizeof(struct Queue));
    queue->end = -1;
    queue->front = 0;

    
    return queue;
}
void enqueue(struct Queue *queue, struct Tile tile)
{   
    if (isFull(queue))
    {
        printf("\nOverflow!!");
    }
    else
    {
        queue->data[queue->end] = tile;
        queue->end++;
    }
}
struct Tile dequeue(struct Queue *queue)
{
    if (isEmpty(queue))
    {
        printf("\nUnderflow!!");
    }
    else
    {
        queue->front++;
    }
    return queue->data[queue->front--];
}
//  Returns the end element of the queue    
struct Tile end(struct Queue *queue)
{
    return queue->data[queue->end];
}
//  Returns false if not empty  
bool isEmpty(struct Queue *queue)
{
    int flag = false;
    if (queue->end < 1)
    {
        flag = true;
    }
    return flag;
}
//  Returns false if not full   
bool isFull(struct Queue *queue)
{
    int flag = false;
    if (queue->end == STACKLIMIT)
    {
        flag = true;
    }
    return flag;
}

void visit(struct Queue *queue) //int y, int x
{
    //map[y][x].visited = true;
    queue->data[queue->front].visited = true;
}

