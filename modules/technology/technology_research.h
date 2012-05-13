#ifndef TECHNOLOGY_RESEARCH
#define TECHNOLOGY_RESEARCH

typedef struct TechnologyResearch
{
    // Id of the technology.
    int id;
    // How many turns we exploring this technology.
    int turns;
    // How many gold it's cost.
    int delta;
} TechnologyResearch;

/*
    Creates new research.
*/
TechnologyResearch * createResearch();

/*
    Destroys research.
*/
void destroyResearch(TechnologyResearch * tr);

#endif
