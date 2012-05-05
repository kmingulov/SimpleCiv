#include <stdlib.h>

#include "../city/city.h"
#include "cell.h"

Node * createRow(int l)
{
    Cell * head = malloc(sizeof(Cell));
    head -> territory = 0;
    head -> resources = 0;

    // Creating row.
    Node * row_head = createGraph(NODE_CELL, head);
    Node * previous = row_head;

    for(int i = 0; i < l - 1; i++)
    {
        // Creating new cell.
        Cell * temp = malloc(sizeof(Cell));
        temp -> territory = 0;
        temp -> resources = 0;
        // Adding this cell to row (+ edge from previous to new).
        Node * new = addNode(previous, EDGE_CELL_RIGHT, NODE_CELL, temp);
        // Adding edge (from new to previous).
        addEdge(new, previous, EDGE_CELL_LEFT);
        // Going on.
        previous = new;
    }

    // Add last edges.
    addEdge(previous, row_head, EDGE_CELL_RIGHT);
    addEdge(row_head, previous, EDGE_CELL_LEFT);

    return row_head;
}

void mergeRows(Node * n1, Node * n2)
{
    Node * x1 = n1;
    Node * x2 = n2;

    do
    {
        addEdge(x1, x2, EDGE_CELL_BOTTOM);
        addEdge(x2, x1, EDGE_CELL_TOP);
        x1 = getNeighbour(x1, EDGE_CELL_RIGHT);
        x2 = getNeighbour(x2, EDGE_CELL_RIGHT);
    } while (x1 != n1 || x2 != n2);
}

Node * createMap(int max_r, int max_c)
{
    Node * head = createRow(max_c);
    Node * row = head;

    for(int i = 0; i < max_r - 1; i++)
    {
        // Creating new row.
        Node * new_row = createRow(max_c);
        // Merging two rows.
        mergeRows(row, new_row);
        // Going on.
        row = new_row;
    }

    mergeRows(row, head);

    return head;
}

void destroyUnitsAndCities(Node * parent, Node * child, Edge * edge)
{
    if(edge -> type == EDGE_CELL_UNIT)
    {
        destroyNode(child);
    }
    else if(edge -> type == EDGE_CELL_CITY)
    {
        free( ((City *) child -> data) -> name );
        destroyNode(child);
    }
}

void destroyMap(Node * map_head, int max_r, int max_c)
{
    Node * current = map_head;
    Node * next_row = current;

    for(int i = 0; i < max_r; i++)
    {
        next_row = getNeighbour(next_row, EDGE_CELL_BOTTOM);
        for(int j = 0; j < max_c; j++)
        {
            // Destroing units and cities.
            foreachNeighbour(current, &destroyUnitsAndCities);
            // Getting next.
            Node * next = getNeighbour(current, EDGE_CELL_RIGHT);
            // Removing this node and all it's edges.
            destroyNode(current);
            // Going on.
            current = next;
        }
        current = next_row;
        // At first next_row = getNeighbour(next_row, EDGE_CELL_BOTTOM); was
        // here, but it was moved because at final step we deleted all map and
        // have no cell to getNeighbour() => segmentation fault.
    }
}

Node * getCell(Node * map_head, int r, int c)
{
    Node * result = map_head;

    for(int i = 0; i < r; i++)
    {
        result = getNeighbour(result, EDGE_CELL_BOTTOM);
    }

    for(int i = 0; i < c; i++)
    {
        result = getNeighbour(result, EDGE_CELL_RIGHT);
    }

    return result;
}
