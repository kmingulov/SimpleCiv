#ifndef UNIT_TABLE
#define UNIT_TABLE

#include "../int_array/int_array.h"
#include "../dyn_array/dyn_array.h"

/*
    Creates unit table.
*/
IntArray * createUnitTable(IntArray * tech_table, DynArray * techs_info, DynArray * units_info);

/*
    Updates unit table.
*/
void updateUnitTable(IntArray * unit_table, IntArray * tech_table, DynArray * techs_info);

#endif
