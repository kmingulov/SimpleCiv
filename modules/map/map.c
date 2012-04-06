#include <stdlib.h>
#include "map.h"

// TODO GOVNOCOD
// Optimise!
Cell * createMap(int w, int h)
{
    Cell * map_head = NULL;
    // Previous line.
    Cell * previous = NULL;

    for(int i = 0; i < w; i++)
    {
        Cell * head = malloc(sizeof(Cell));
        if(map_head == NULL)
        {
            map_head = head;
        }
        if(previous != NULL)
        {
            head -> top = previous;
            previous -> bottom = head;
        }
        // Creating new doubly circular linked list.
        Cell * current = head;
        for(int j = 0; j < h - 1; j++)
        {
            // Allocate memory for new cell.
            Cell * temp = malloc(sizeof(Cell));
            // Connect left and right.
            current -> right = temp;
            temp -> left = current;
            // Connect two lines.
            if(i != 0)
            {
                previous -> bottom = current;
                current -> top = previous;
                previous = previous -> right;
            }
            // Go on!
            current = temp;
        }
        // Connect two lines.
        if(i != 0)
        {
            previous -> bottom = current;
            current -> top = previous;
            previous = previous -> right;
        }
        // Connect the head and end.
        current -> right = head;
        head -> left = current;
        // New line.
        previous = head;
    }

    // Connect the first line and the last.
    Cell * temp1 = map_head, * temp2 = previous;
    
    for(int i = 0; i < w; i++)
    {
        temp2 -> bottom = temp1;
        temp1 -> top = temp2;
        temp1 = temp1 -> right;
        temp2 = temp2 -> right;
    }

    return map_head;
}

void destroyMap(Cell * head, int w, int h)
{
    Cell * current = head;
    for(int i = 0; i < w; i++)
    {
        Cell * next_line = current -> bottom;
        for(int j = 0; j < h; j++)
        {
            Cell * temp = current -> right;
            free(current);
            current = temp;
        }
        current = next_line;
    }
}

Cell * getCell(Cell * cell, int offset_x, int offset_y)
{
    Cell * current = cell;
    int temp = offset_x;

    while(temp != 0)
    {
        if(temp > 0)
        {
            current = current -> right;
            temp--;
        }
        else if(temp < 0)
        {
            current = current -> left;
            temp++;
        }
    }

    temp = offset_y;

    while(temp != 0)
    {
        if(temp > 0)
        {
            current = current -> top;
            temp--;
        }
        else if(temp < 0)
        {
            current = current -> bottom;
            temp++;
        }
    }

    return current;
}

Cell * getLeft(Cell * cell)
{
    return getCell(cell, -1, 0);
}

Cell * getRight(Cell * cell)
{
    return getCell(cell, 1, 0);
}

Cell * getTop(Cell * cell)
{
    return getCell(cell, 0, 1);
}

Cell * getBottom(Cell * cell)
{
    return getCell(cell, 0, -1);
}

Cell * getCellByNumber(Cell * c, int i)
{
    switch(i)
    {
        case 0:
            return c -> top;
        break;

        case 1:
            return c -> right;
        break;

        case 2:
            return c -> bottom;
        break;

        case 3:
            return c -> left;
        break;
    }

    return NULL;
}

char isWhereCell(Cell * c, int t)
{
    for(int i = 0; i < 4; i++)
    {
        if(getCellByNumber(c, i) -> territory == t)
        {
            return 1;
        }
    }

    return 0;
}
