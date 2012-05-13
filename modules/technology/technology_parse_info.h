#ifndef TECHNOLOGY_PARSE_INFO
#define TECHNOLOGY_PARSE_INFO

#include "../int_array/int_array.h"
#include "../graph/graph.h"

typedef struct TechnologyParseInfo
{
    IntArray * provides_technologies;
    Node * tech_in_tree;
} TechnologyParseInfo;

/*
    Creates new variable of type TechnologyParseInfo.
*/
TechnologyParseInfo * createTechnologyParseInfo();

/*
    Destroys TechnologyParseInfo.
*/
void destroyTechnologyParseInfo(void * data);

#endif
