#ifndef TECHNOLOGY_TABLE
#define TECHNOLOGY_TABLE

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"
#include "../graph/graph.h"
#include "../player/player.h"
#include "technology.h"

/*
    Creates technology status table.
*/
IntArray * createTechnologyTable(DynArray * techs_info);

/*
    Updates technology status table for one technology.
*/
void updateTechnologyTable(IntArray * tech_table, Node * tech);

/*
    Checkes available with technology or no.
    Looks for player's resources (function updateTechnologyStatus() doesn't do
    this).
    Returns 1 if available, 0 if no.
*/
int checkForResources(Technology * tech, Player * player);

#endif
