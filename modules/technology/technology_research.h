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

#ifndef TECHNOLOGY_RESEARCH_H
#define TECHNOLOGY_RESEARCH_H

/*
    Struct of player's research.
*/
typedef struct TechnologyResearch
{
    // Id of the technology.
    int id;

    // How many turns we exploring this technology.
    int turns;

    // How many gold it's cost.
    int delta;
} TechnologyResearch;

/*
    Creates new research.
*/
TechnologyResearch * createResearch();

/*
    Destroys the research.
*/
void destroyResearch(TechnologyResearch * tr);

#endif
