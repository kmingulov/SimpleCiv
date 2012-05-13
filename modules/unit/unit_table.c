#include <stdlib.h>

#include "../../game/world/definitions.h"
#include "../technology/technology.h"
#include "unit_table.h"

IntArray * createUnitTable(IntArray * tech_table, DynArray * techs_info, DynArray * units_info)
{
    IntArray * result = iaLengthCreate(units_info -> length);

    updateUnitTable(result, tech_table, techs_info);

    return result;
}

void updateUnitTable(IntArray * unit_table, IntArray * tech_table, DynArray * techs_info)
{
    for(int i = 0; i < tech_table -> length; i++)
    {
        if( iaGetByIndex(tech_table, i) == TECH_RESEARCHED )
        {
            IntArray * units = ((Technology *) ((Node *) daGetByIndex(techs_info, i)) -> data) -> provides_units;
            if(units != NULL)
            {
                for(int j = 0; j < units -> length; j++)
                {
                    int id = iaGetByIndex(units, j);
                    iaSetByIndex(unit_table, id, UNIT_AVAILABLE);
                }
            }
        }
    }
}
