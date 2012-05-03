#ifndef TECHNOLOGY
#define TECHNOLOGY

#include "../graph/graph.h"

/*
    This is struct of technology. It only for technology tree (common for _all_
    players).
    Each player will have table with technologies' id and value (see definitions
    in game/model/definitions.h).
*/
typedef struct Technology
{
	int id;
    char * name;
    DynArray * requires_resources;
    DynArray * provides_units;
} Technology;

typedef struct TechnologyCommonInfo
{
    Node * tech_in_tree;
} TechnologyCommonInfo;

typedef struct TechnologyParseInfo
{
    DynArray * provides_technologies;
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

/*
    Destroys Technology.
*/
void destroyTechnology(unsigned char type, void * data);

#endif
