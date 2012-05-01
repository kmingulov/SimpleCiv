#ifndef TECHNOLOGY
#define TECHNOLOGY

/*
    This is struct of technology. It only for technology tree (common for _all_
    players).
    Each player will have table with technologies' id and value (see definitions
    in game/model/definitions.h).
*/
typedef struct Techology
{
	int id;
} Technology;

typedef struct TechnologyCommonInfo
{
    char * name;
    DynArray * require_resources;
    Node * tech_in_tree;
} TechnologyCommonInfo;

typedef struct TechnologyParseInfo
{
    char * name;
    DynArray * provide_units;
    DynArray * provide_technologies;
    DynArray * require_resources;
    Node * tech_in_tree;
}

#endif
