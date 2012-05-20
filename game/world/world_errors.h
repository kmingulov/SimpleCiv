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

#ifndef WORLD_ERRORS_H
#define WORLD_ERRORS_H

#include "../../modules/dyn_array/dyn_array.h"

#include "world_properties.h"

/*
    Checks WorldProperties for errors.
    Returns 1 if everything is ok, else 0.
*/
int noErrorsInWorldProperties(FILE * log, WorldProperties * properties);

/*
    Checks units_info for errors.
    Returns 1 if everything is ok, else 0.
*/
int noErrorsInUnitsInfo(FILE * log, DynArray * units_info);

/*
    Checks units_info for errors.
    Returns 1 if everything is ok, else 0.
*/
int noErrorsInTechsData(FILE * log, DynArray * techs_data);

#endif
