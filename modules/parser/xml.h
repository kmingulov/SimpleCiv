#ifndef XML
#define XML

#define XML_MAX_CHARS 1000

#include "../../game/world/world.h"

/*
    Parses config file and returns WorldProperties.
*/
WorldProperties * parseConfig(char * filename);

#endif
