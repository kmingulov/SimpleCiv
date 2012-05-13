#include <stdlib.h>

#include "../../game/world/definitions.h"
#include "technology_parse_info.h"
#include "technology.h"

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
        iaDestroy(t -> provides_technologies);
    }
    free(t);
}
