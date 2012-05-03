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

void destroyTechnologyParseInfo(void * data)
{
    TechnologyParseInfo * t = (TechnologyParseInfo *) data;
    if(t -> provides_technologies != NULL)
    {
        daDestroy(t -> provides_technologies, NULL);
    }
    free(t);
}

TechnologyCommonInfo * createTechnologyCommonInfo(TechnologyParseInfo * data)
{
    TechnologyCommonInfo * t = malloc(sizeof(TechnologyCommonInfo));

    t -> tech_in_tree = data -> tech_in_tree;

    return t;
}

void destroyTechnology(unsigned char type, void * data)
{
    Technology * t = (Technology *) data;

    if(t -> name != NULL)
    {
        free(t -> name);
    }

    if(t -> requires_resources != NULL)
    {
        daDestroy(t -> requires_resources, NULL);
    }

    if(t -> requires_resources != NULL)
    {
        daDestroy(t -> provides_units, NULL);
    }

    free(t);
}
