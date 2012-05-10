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
    // How many turns have to spend on researching this technology.
    int turns;
    IntArray * requires_resources;
    IntArray * provides_units;
} Technology;

typedef struct TechnologyParseInfo
{
    IntArray * provides_technologies;
    Node * tech_in_tree;
} TechnologyParseInfo;

typedef struct TechnologyResearch
{
    int id;
    // How many turns we researching this technology.
    int turns;
    // How many gold it's cost.
    int delta;
} TechnologyResearch;

/*
    Creates new variable of type TechnologyParseInfo.
*/
TechnologyParseInfo * createTechnologyParseInfo();

/*
    Destroys TechnologyParseInfo.
*/
void destroyTechnologyParseInfo(void * data);

/*
    Destroys Node with technology.
*/
void destroyTechnologyCommonInfo(void * data);

/*
    Destroys Technology.
*/
void destroyTechnology(void * data);

/*
    Creates new research.
*/
TechnologyResearch * createResearch();

/*
    Destroys research.
*/
void destroyResearch(TechnologyResearch * tr);

/*
    Creates edges in technology tree.
*/
Node * createEdgesInTechnologyTree(DynArray * techs_data);

/*
    Creates technology status table.
*/
IntArray * createTechnologyStatus(DynArray * techs_info);

/*
    Updates technology status table for one technology.
*/
void updateTechnologyStatus(IntArray * techs_status, Node * tech);

#endif
