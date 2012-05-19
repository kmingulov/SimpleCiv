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
#include <stdlib.h>
#include <string.h>
#include <expat.h>

#include "../../game/world/world.h"
#include "../dyn_array/dyn_array.h"
#include "xml.h"
#include "expat_handlers.h"

void * parseXML(int type)
{
    // Creating variables for parse.
    void * data = NULL;
    FILE * file = NULL;

    // What about type?
    switch(type)
    {
        case XML_CONFIG:
            data = malloc(sizeof(WorldProperties));
            file = fopen("config.xml", "r");
        break;

        case XML_UNITS:
            data = daCreate();
            file = fopen("resources/units.xml", "r");
        break;

        case XML_TECHNOLOGIES:
            data = daCreate();
            file = fopen("resources/technologies.xml", "r");
        break;

        default:
            return NULL;
        break;
    }

    // Initializing parser data.
    XMLParserData * p_data = malloc(sizeof(XMLParserData));
    p_data -> data = data;
    p_data -> state = XML_NONE;

    // If there is no file…
    if(file == NULL)
    {
        free(data);
        free(p_data);
        return NULL;
    }

    // Reading data.
    char * xml = calloc(XML_MAX_CHARS + 1, sizeof(char));
    fread(xml, sizeof(char), XML_MAX_CHARS, file);
    fclose(file);

    // Creating and setting up parser.
    XML_Parser parser = XML_ParserCreate(NULL);
    XML_SetUserData(parser, p_data);
    XML_SetElementHandler(parser, &elementStart, &elementEnd);
    XML_SetCharacterDataHandler(parser, &elementContent);

    // Parsing xml file.
    if(!XML_Parse(parser, xml, strlen(xml), 0))
    {
        free(data);
        free(p_data);
        free(xml);
        XML_ParserFree(parser);
        return NULL;
    }

    // Freeing auxiliary data.
    free(p_data);
    free(xml);
    XML_ParserFree(parser);

    // Returning data.
    return data;
}
