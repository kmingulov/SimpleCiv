#include <stdlib.h>

#include "technology.h"
#include "../../game/world/definitions.h"
#include "../dyn_array/dyn_array.h"
#include "../graph/graph.h"

TechnologyParseInfo * createTechnologyParseInfo()
{
    // Creating new data.
    TechnologyParseInfo * data = malloc(sizeof(TechnologyParseInfo));
    Technology * tech = malloc(sizeof(Technology));

    // Creating new node.
    data -> tech_in_tree = addNode(NULL, 0, NODE_TECHNOLOGY, tech);

    // NULLing all pointers (if something isn't defined in xml-file).
    data -> provides_technologies = NULL;
    tech -> name = NULL;
    tech -> requires_resources = NULL;
    tech -> provides_units = NULL;

    // Returning result.
    return data;
}

void destroyTechCommonInfo(void * data)
{
    Node * n = (Node *) data;
    daDestroy(n -> edges, &free);
    destroyTechnology(n -> data);
    free(n);
}

void destroyTechnologyParseInfo(void * data)
{
    TechnologyParseInfo * t = (TechnologyParseInfo *) data;
    if(t -> provides_technologies != NULL)
    {
        iaDestroy(t -> provides_technologies);
    }
    free(t);
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

IntArray * createTechnologyStatus(DynArray * techs_info)
{
    IntArray * result = iaLengthCreate(techs_info -> length);
    for(int i = 0; i < result -> length; i++)
    {
        // Getting node of technology.
        Node * tech = (Node *) daGetByIndex(techs_info, i);
        // If there is no «require» edges, set this technology to already
        // researched.
        if(getNeighbour(tech, EDGE_TECH_REQUIRES) == NULL)
        {
            iaSetByIndex(result, i, TECH_RESEARCHED);
        }
        else
        {
            iaSetByIndex(result, i, TECH_NOT_AVAILABLE);
        }
    }

    for(int i = 0; i < result -> length; i++)
    {
        if(iaGetByIndex(result, i) == TECH_RESEARCHED)
        {
            updateTechnologyStatus(result, daGetByIndex(techs_info, i));
        }
    }
    

    return result;
}

void updateTechnologyStatus(IntArray * techs_status, Node * tech)
{
    DynArray * edges = tech -> edges;
    for(int i = 0; i < edges -> length; i++)
    {
        Edge * edge = (Edge *) daGetByIndex(edges, i);
        // Checking only for «provides» edges.
        if(edge -> type == EDGE_TECH_PROVIDES)
        {
            // Getting target's edges.
            DynArray * t_edges = edge -> target -> edges;
            unsigned char success = 1;
            for(int j = 0; j < t_edges -> length; j++)
            {
                Edge * t_edge = (Edge *) daGetByIndex(t_edges, j);
                // Checking only for «requires» edges.
                if(t_edge -> type == EDGE_TECH_REQUIRES)
                {
                    Technology * t = (Technology *) t_edge -> target -> data;
                    // If technology already researched, go on! If no, break.
                    if(iaGetByIndex(techs_status, t -> id) != TECH_RESEARCHED)
                    {
                        success = 0;
                        break;
                    }
                }
            }
            // Player can research this technology.
            if(success == 1)
            {
                int id = ((Technology *) edge -> target -> data) -> id;
                iaSetByIndex(techs_status, id, TECH_AVAILABLE);
            }
        }
    }
}
