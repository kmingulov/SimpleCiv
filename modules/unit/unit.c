#include <stdlib.h>
#include <math.h>

#include <ncurses.h>
#include <stdio.h>

#include "../../game/world/definitions.h"
#include "../graph/graph.h"
#include "../technology/technology.h"
#include "../dyn_array/dyn_array.h"
#include "unit.h"

UnitCommonInfo * createUnitCommonInfo()
{
    UnitCommonInfo * unit = malloc(sizeof(UnitCommonInfo));

    unit -> name = NULL;
    unit -> max_health = 0;
    unit -> max_damage = 0;
    unit -> max_moves = 0;

    return unit;
}

void destroyUnitCommonInfo(void * data)
{
    UnitCommonInfo * unit = (UnitCommonInfo *) data;
    free(unit -> name);
    free(unit);
}

IntArray * createUnitStatus(IntArray * techs_status, DynArray * techs_info, DynArray * units_info)
{
    IntArray * result = iaLengthCreate(units_info -> length);

    for(int i = 0; i < techs_status -> length; i++)
    {
        if( iaGetByIndex(techs_status, i) == TECH_RESEARCHED )
        {
            IntArray * units = ((Technology *) ((Node *) daGetByIndex(techs_info , i)) -> data) -> provides_units;
            if(units != NULL)
            {
                for(int j = 0; j < units -> length; j++)
                {
                    int id = iaGetByIndex(units, j);
                    iaSetByIndex(result, id, UNIT_AVAILABLE);
                }
            }
        }
    }

    return result;
}

Unit * createUnit(World * world, unsigned int r, unsigned int c, unsigned char unit_id, Player * player)
{
    // Cell (r,c) already have a unit.
    if(getNeighbour( getCell(world -> graph_map, r, c), EDGE_CELL_UNIT ) != NULL)
    {
        return NULL;
    }

    // Allocate some memory.
    Unit * unit = malloc(sizeof(Unit));
    UnitCommonInfo * info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit_id);
    Node * node = createGraph(NODE_UNIT, unit);

    // Copying basic info.
    unit -> unit_id = unit_id;
    unit -> health = info -> max_health;
    unit -> moves = info -> max_moves;

    // Adding owner info.
    unit -> owner = player;
    listPrepend(player -> units, unit);

    // Adding coordinates.
    unit -> r = r;
    unit -> c = c;
    addEdge(getCell(world -> graph_map, r, c), node, EDGE_CELL_UNIT);

    return unit;
}

void unitsFight(DynArray * units_info, Unit * unit1, Unit * unit2)
{
    // Getting units' info.
    UnitCommonInfo * u1 = (UnitCommonInfo *) daGetByIndex(units_info, unit1 -> unit_id);
    UnitCommonInfo * u2 = (UnitCommonInfo *) daGetByIndex(units_info, unit2 -> unit_id);

    // Calculating max damage.
    double damage1 = (double) unit1 -> health / u1 -> max_health * u1 -> max_damage;
    double damage2 = (double) unit2 -> health / u2 -> max_health * u2 -> max_damage;

    // Random damage between 70% and 100% of damage1/damage2.
    damage1 *= ((double) (rand() % 7 + 3.0f)) / 10.0f;
    damage2 *= ((double) (rand() % 7 + 3.0f)) / 10.0f;

    // Fight!
    unit1 -> health -= ceil(damage2);
    unit2 -> health -= ceil(damage1);
}

void developUnit(void * data, DynArray * info)
{
    Unit * unit = (Unit *) data;

    UnitCommonInfo * unit_info = (UnitCommonInfo *) daGetByIndex(info, unit -> unit_id);

    if
    (
        unit -> moves == unit_info -> max_moves &&
        unit -> health +1 <= unit_info -> max_health
    )
        unit -> health = unit -> health +1;

    unit -> moves = unit_info-> max_moves;
}

void moveUnit(Node * current_cell, int dir)
{
    Edge * edge;
    for(int i = 0; i < current_cell -> edges -> length; i++)
    {
        edge = current_cell -> edges -> data[i];
        if(edge -> type == EDGE_CELL_UNIT)
        {
            break;
        }
    }
    daRemoveByPointer(current_cell -> edges, edge, NULL);
    daPrepend(getNeighbour(current_cell, EDGE_CELL_TOP) -> edges, edge);
}
