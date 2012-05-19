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

#ifndef EXPAT_HANDLERS_H
#define EXPAT_HANDLERS_H

/*
    Definitions for parser.
*/
// Count of states.
#define XML_STATES                  27

#define XML_NONE                    0

#define XML_MAP                     1
#define XML_MAP_ROWS                2
#define XML_MAP_COLUMNS             3

#define XML_PLAYERS                 4
#define XML_PLAYERS_COUNT           5
#define XML_PLAYERS_NAMES           6
#define XML_PLAYERS_CITIES          7

#define XML_UNIT                    8
#define XML_UNIT_ID                 9
#define XML_UNIT_NAME               10
#define XML_UNIT_CHAR               11
#define XML_UNIT_HEALTH             12
#define XML_UNIT_DAMAGE             13
#define XML_UNIT_MOVES              14
#define XML_UNIT_HIRING_TURNS       15
#define XML_UNIT_GOLD_DROP          16
#define XML_UNIT_PRIVILEGES         17
#define XML_UNIT_RESOURCES          18

#define XML_TECH                    19
#define XML_TECH_ID                 20
#define XML_TECH_NAME               21
#define XML_TECH_TURNS              22
#define XML_TECH_PROVIDES           23
#define XML_TECH_PROVIDES_UNITS     24
#define XML_TECH_PROVIDES_TECHS     25
#define XML_TECH_REQUIRES           26
#define XML_TECH_REQUIRES_RESOURCES 27

/*
    Struct for parser data.
*/
typedef struct XMLParserData
{
    void * data;
    int state;
} XMLParserData;

/*
    Handlers for parse.
*/
void elementStart(void * data, const char * name, const char ** attr);
void elementEnd(void * data, const char * name);
void elementContent(void * data, const char * s, int len);

#endif
