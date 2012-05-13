#include <stdlib.h>

#include "technology_research.h"

TechnologyResearch * createResearch()
{
    TechnologyResearch * tr = malloc(sizeof(TechnologyResearch));
    tr -> id = -1;
    tr -> turns = 0;
    tr -> delta = 0;
    return tr;
}

void destroyResearch(TechnologyResearch * tr)
{
    free(tr);
}
