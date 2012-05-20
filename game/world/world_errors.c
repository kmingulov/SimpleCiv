/*

    SimpleCiv is simple clone of Civilization game, using ncurses library.
    Copyright (C) 2012 by K. Mingulov, A. Sapronov.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include <stdio.h>

#include "../../modules/log/log.h"

#include "definitions.h"
#include "world_errors.h"

int noErrorsInWorldProperties(FILE * log, WorldProperties * properties)
{
    if(properties == NULL)
    {
        addToLog(log, "ERROR (config.xml)\tFile doesn't exist or corrupted");
        return 0;
    }

    // Check for world sizes.
    if(properties -> map_r <= MIN_WORLD_SIZE_R || properties -> map_c <= MIN_WORLD_SIZE_C)
    {
        addToLog(log, "ERROR (config.xml)\tWorld sizes is too small. %d and %d for rows and columns required at least", MIN_WORLD_SIZE_R, MIN_WORLD_SIZE_C);
        return 0;
    }

    // Check there is enough players' names.
    if(properties -> players_count > properties -> player_names -> length)
    {
        addToLog(log, "ERROR (config.xml)\tToo few players' names");
        return 0;
    }

    // Check there is enough cities' names.
    if(properties -> players_count > properties -> player_cities -> length)
    {
        addToLog(log, "ERROR (config.xml)\tToo few cities' names");
        return 0;
    }

    return 1;
}

int noErrorsInUnitsInfo(FILE * log, DynArray * units_info)
{
    if(units_info == NULL)
    {
        addToLog(log, "ERROR (resources/units.xml)\tfile doesn't exist or corrupted");
        return 0;
    }

    return 1;
}

int noErrorsInTechsData(FILE * log, DynArray * techs_data)
{
    if(techs_data == NULL)
    {
        addToLog(log, "ERROR (resources/technologies.xml)\tfile doesn't exist or corrupted");
        return 0;
    }

    return 1;
}
