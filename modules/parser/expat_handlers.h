#ifndef EXPAT_HANDLERS
#define EXPAT_HANDLERS

#include "../../game/world/world.h"

/*
    Definitions for parser.
*/
#define XML_NONE                    0

#define XML_MAP                     1
#define XML_MAP_WIDTH               2
#define XML_MAP_HEIGHT              3

#define XML_PLAYERS                 4
#define XML_PLAYERS_COUNT           5
#define XML_PLAYERS_NAMES           6

#define XML_UNIT                    7
#define XML_UNIT_ID                 8
#define XML_UNIT_NAME               9
#define XML_UNIT_HEALTH             10
#define XML_UNIT_DAMAGE             11

#define XML_TECH                    12
#define XML_TECH_ID                 13
#define XML_TECH_NAME               14
#define XML_TECH_PROVIDES           15
#define XML_TECH_PROVIDES_UNITS     16
#define XML_TECH_PROVIDES_TECHS     17
#define XML_TECH_REQUIRES           18
#define XML_TECH_REQUIRES_RESOURCES 19

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
