#ifndef TECHNOLOGY
#define TECHNOLOGY

#include "../dyn_array/dyn_array.h"
#include "../int_array/int_array.h"
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
    IntArray * requires_resources;
    IntArray * provides_units;
} Technology;

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

void * destroyTechCommonInfo(void * data);

/*
    Destroys Technology.
*/
void destroyTechnology(void * data);

/*
    Creates technology status table.
*/
IntArray * createTechnologyStatus(DynArray * techs_info);

/*
    Updates technology status table for one technology.
*/
void updateTechnologyStatus(IntArray * techs_status, Node * tech);

#endif
