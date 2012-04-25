#ifndef XMLPARSER
#define XMLPARSER

#include <stdio.h>


typedef struct Techology
{
	int id;
	char * name;

} Technology;

typedef struct Unit
{
	int id;
} Unit;



void xml_read_info(int type, FILE *fi);



#endif //XMPLARSER __xmlparser_h
