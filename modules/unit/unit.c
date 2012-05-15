#include <stdlib.h>
#include <math.h>

#include "../../game/world/definitions.h"
#include "../graph/graph.h"
#include "../cell/cell.h"
#include "unit_common_info.h"
#include "unit.h"

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

void destroyUnit(World * world, Unit * unit)
{
    // TODO Awful. Maybe rewrite?
    Player * player = unit -> owner;

    // Removing unit from map.
    int r = unit -> r; int c = unit -> c;
    Node * n = getCell(world -> graph_map, r, c);
    Edge * edge;
    for(int i = 0; i < n -> edges -> length; i++)
    {
        edge = n -> edges -> data[i];
        if(edge -> type == EDGE_CELL_UNIT)
        {
            break;
        }
    }
    // Removing node with unit.
    destroyNode(edge -> target);
    // Removing pointer to him from map.
    daRemoveByPointer(n -> edges, edge, &free);

    // Removing pointer to him from owner's list.
    listDeleteByPointer(player -> units, unit, NULL);
}

void unitsFight(World * world, Unit ** unit1, Unit ** unit2)
{
    DynArray * units_info = world -> units_info;

    // Getting units' info.
    UnitCommonInfo * u1 = (UnitCommonInfo *) daGetByIndex(units_info, (* unit1) -> unit_id);
    UnitCommonInfo * u2 = (UnitCommonInfo *) daGetByIndex(units_info, (* unit2) -> unit_id);

    // Calculating max damage.
    double damage1 = (double) (* unit1) -> health / u1 -> max_health * u1 -> max_damage;
    double damage2 = (double) (* unit2) -> health / u2 -> max_health * u2 -> max_damage;

    // Random damage between 70% and 100% of damage1/damage2.
    damage1 *= ((double) (rand() % 7 + 4.0f)) / 10.0f;
    damage2 *= ((double) (rand() % 7 + 4.0f)) / 10.0f;

    // Fight!
    (* unit1) -> health -= ceil(damage2);
    (* unit2) -> health -= ceil(damage1);

    // Checking there're alive or not.
    if( (* unit1) -> health <= 0 )
    {
        // Player2 getting drop.
        (* unit2) -> owner -> gold += u1 -> gold_drop;
        // Destroing unit.
        destroyUnit(world, * unit1);
        * unit1 = NULL;
    }
    if( (* unit2) -> health <= 0 )
    {
        // Player1 getting drop.
        (* unit1) -> owner -> gold += u2 -> gold_drop;
        // Destroing unit.
        destroyUnit(world, * unit2);
        * unit2 = NULL;
    }
}

void developUnit(void * data, DynArray * info)
{
    Unit * unit = (Unit *) data;
    UnitCommonInfo * unit_info = (UnitCommonInfo *) daGetByIndex(info, unit -> unit_id);

    // Unit needs money.
    if(unit -> owner -> gold <= 3)
    {
        // No money, no honey.
        unit -> health -= ceil(0.1f * unit_info -> max_health);
        if(unit -> health < 0)
        {
            // But he can't die from hunger.
            unit -> health = ceil((float) 0.1f * unit_info -> max_health);
        }
    }
    else
    {
        unit -> owner -> gold -= 3;
        if(unit -> moves == unit_info -> max_moves)
        {
            if(unit -> health + 0.1f * unit_info -> max_health < unit_info -> max_health)
            {
                unit -> health = unit -> health + 0.1f * unit_info -> max_health;
            }
            else
            {
                unit -> health = unit_info -> max_health;
            }
        }
    }

    unit -> moves = unit_info -> max_moves;
}

int moveUnit(World * world, Node * current_cell, int direction)
{
    // Getting edge to unit.
    Edge * edge;
    for(int i = 0; i < current_cell -> edges -> length; i++)
    {
        edge = current_cell -> edges -> data[i];
        if(edge -> type == EDGE_CELL_UNIT)
        {
            break;
        }
    }

    Unit * unit = (Unit *) edge -> target -> data;
    UnitCommonInfo * u_info = (UnitCommonInfo *) daGetByIndex(world -> units_info, unit -> unit_id);
    Node * destination = getNeighbour(current_cell, direction);

    // Unit cannot go any more.
    if(unit -> moves == 0)
    {
        return 0;
    }

    // Unit is a ship?
    if(u_info -> privileges != NULL && iaSearchForData(u_info -> privileges, UNIT_PRVL_CAN_FLOAT) != -1)
    {
        // Cannot go to the land, if there is no city.
        if( ((Cell *) destination -> data) -> territory != CELL_TYPE_WATER && getNeighbour(destination, EDGE_CELL_CITY) == NULL )
        {
            return 0;
        }
    }

    // Cannot go to the water.
    if(((Cell *) destination -> data) -> territory == CELL_TYPE_WATER)
    {
        // Not a ship.
        if(u_info -> privileges == NULL || iaSearchForData(u_info -> privileges, UNIT_PRVL_CAN_FLOAT) == -1)
        {
            return 0;
        }
    }

    // There is another unit?
    if(getNeighbour(destination, EDGE_CELL_UNIT) != NULL)
    {
        Node * neighbour = getNeighbour(destination, EDGE_CELL_UNIT);
        Unit * another_unit = (Unit *) neighbour -> data;
        // Fight!
        if(another_unit -> owner != unit -> owner)
        {
            unit -> moves = 0;
            unitsFight(world, &unit, &another_unit);
            return 2;
        }
        return 0;
    }

    if(getNeighbour(destination, EDGE_CELL_CITY != NULL))
    {
        Node * neighbour = getNeighbour(destination, EDGE_CELL_CITY);
        City * city = (City *) neighbour -> data;
        // Fight!
        if(city -> owner != unit -> owner)
        {
            unit -> moves = 0;
            unitcityFight(world,&unit, &city);
            return 2;
        }
        return 0;
    }

    // Motion.
    unit -> moves--;
    switch(direction)
    {
        case EDGE_CELL_TOP:    unit -> r--; break;
        case EDGE_CELL_BOTTOM: unit -> r++; break;
        case EDGE_CELL_RIGHT:  unit -> c++; break;
        case EDGE_CELL_LEFT:   unit -> c--; break;
    }

    if(unit -> r >= world -> properties -> map_r)
    {
        unit -> r %= world -> properties -> map_r;
    }
    else if(unit -> r < 0)
    {
        unit -> r += world -> properties -> map_r;
    }

    if(unit -> c >= world -> properties -> map_c)
    {
        unit -> c %= world -> properties -> map_c;
    }
    else if(unit -> c < 0)
    {
        unit -> c += world -> properties -> map_c;
    }

    daRemoveByPointer(current_cell -> edges, edge, NULL);
    daPrepend(destination -> edges, edge);

    return 1;
}


void unitcityFight(World * world, Unit ** unit1, City ** city)
{

    DynArray * units_info = world -> units_info;

    // Getting units' info.
    //~ UnitCommonInfo * u1 = (UnitCommonInfo *) daGetByIndex(units_info, (* unit1) -> unit_id);
    /* если в городе есть юниты, то пройтись циклом по всем и
     * вызвать unitsFight(world,unit,unit in city)
     * если нет юнитов, то city -> owner = unit -> owner
     * если это был город игрока и (последний юнит), то убить игрока
     * */

}
