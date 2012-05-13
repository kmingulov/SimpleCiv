#ifndef XML
#define XML

// Max amount of chars, that we read from xml-file and parse.
#define XML_MAX_CHARS    100000

// XML file types.
#define XML_CONFIG       0
#define XML_TECHNOLOGIES 1
#define XML_UNITS        2

/*
    Parses XML file with type and returns data.
*/
void * parseXML(int type);

#endif
