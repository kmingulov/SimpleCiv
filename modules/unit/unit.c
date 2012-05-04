#include <stdlib.h>

#include "../../game/world/definitions.h"
#include "../graph/graph.h"
#include "../technology/technology.h"
#include "unit.h"

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
