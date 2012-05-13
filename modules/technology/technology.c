#include <stdlib.h>

#include "../../game/world/definitions.h"
#include "../graph/graph.h"

#include "technology.h"
#include "technology_parse_info.h"

void destroyTechnologyCommonInfo(void * data)
{
    Node * n = (Node *) data;
    daDestroy(n -> edges, &free);
    destroyTechnology(n -> data);
    free(n);
}

void destroyTechnology(void * data)
{
    Technology * t = (Technology *) data;

    if(t -> name != NULL)
    {
        free(t -> name);
    }

    if(t -> requires_resources != NULL)
    {
        iaDestroy(t -> requires_resources);
    }

    if(t -> provides_units != NULL)
    {
        iaDestroy(t -> provides_units);
    }

    free(t);
}

Node * createEdgesInTechnologyTree(DynArray * techs_data)
{
    // Passing each technology.
    for(int i = 0; i < techs_data -> length; i++)
    {
        TechnologyParseInfo * current = (TechnologyParseInfo *) daGetByIndex(techs_data, i);
        IntArray * provides = current -> provides_technologies;
        // For each neighbour creating two edges (TECH_PROVIDES and
        // TECH_REQUIRES).
        if(provides != NULL)
        {
            for(int j = 0; j < provides -> length; j++)
            {
                // Getting neighbour.
                int id = iaGetByIndex(provides, j);
                TechnologyParseInfo * neighbour = (TechnologyParseInfo *) daGetByIndex(techs_data, id);
                // Creating two edges.
                addEdge(current -> tech_in_tree, neighbour -> tech_in_tree, EDGE_TECH_PROVIDES);
                addEdge(neighbour -> tech_in_tree, current -> tech_in_tree, EDGE_TECH_REQUIRES);
            }
        }
    }

    // Returning first technology.
    return ((TechnologyParseInfo *) daGetByIndex(techs_data, 0)) -> tech_in_tree;
}
