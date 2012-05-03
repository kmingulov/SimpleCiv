#include <stdlib.h>

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

Node * createMap(int w, int h)
{
    Node * head = createRow(w);
    Node * row = head;

    for(int i = 0; i < h - 1; i++)
    {
        // Creating new row.
        Node * new_row = createRow(w);
        // Merging two rows.
        mergeRows(row, new_row);
        // Going on.
        row = new_row;
    }

    mergeRows(row, head);

    return head;
}

void destroyMap(Node * map_head, int w, int h)
{
    Node * current = map_head;
    Node * next_row = current;

    for(int i = 0; i < h; i++)
    {
        next_row = getNeighbour(next_row, EDGE_CELL_BOTTOM);
        for(int j = 0; j < w; j++)
        {
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
