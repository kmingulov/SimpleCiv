#include <stdlib.h>
#include <stdio.h>
#include "map.h"

Cell * createRow(int l)
{
    Cell * head = malloc(sizeof(Cell));
    Cell * previous = head;

    head -> territory = 0;

    for(int i = 0; i < l - 1; i++)
    {
        Cell * temp = malloc(sizeof(Cell));
        temp -> territory = 0;
        previous -> right = temp;
        temp -> left = previous;
        previous = temp;
    }

    previous -> right = head;
    head -> left = previous;

    return head;
}

void mergeRows(Cell * c1, Cell * c2)
{
    Cell * x1 = c1;
    Cell * x2 = c2;

    do
    {
        x1 -> bottom = x2;
        x2 -> top = x1;
        x1 = x1 -> right;
        x2 = x2 -> right;
    } while (x1 != c1 || x2 != c2);
}

Cell * createMap(int w, int h)
{
    Cell * head = createRow(h);
    Cell * row = head;

    for(int i = 0; i < w; i++)
    {
        Cell * new_row = createRow(h);
        mergeRows(row, new_row);
        row = new_row;
    }

    mergeRows(row, head);

    return head;
}

void destroyRow(Cell * row)
{
    Cell * current = row;

    do
    {
        Cell * temp = current -> right;
        free(current);
        current = temp;
    } while(current != row);
}

void destroyMap(Cell * head)
{
    Cell * current = head;

    do
    {
        Cell * temp = current -> bottom;
        destroyRow(current);
        current = temp;
    } while(current != head);
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

char isWhereCell(Cell * c, char t)
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
