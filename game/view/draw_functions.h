#ifndef DRAW_FUNCTIONS
#define DRAW_FUNCTIONS

/*
    Clears block from (start_r, start_c) to (start_r + r, start_c + c) point.
*/
void clearBlock(int start_r, int start_c, int r, int c);

/*
    Draws box (start_r, start_c) to (start_r + r, start_c + c) point.
*/
void drawBox(int start_r, int start_c, int r, int c);

/*
    Draws vertical line from (start_r, c) to (start_r + r, c) point
*/
void drawVertLine(int start_r, int r, int c);

/*
    Draws horizontal line from (r, start_c) to (r, start_c + c) point
*/
void drawHorizLine(int start_r, int r, int c);


/*
    Put char string into the middle/right/left of row. Syntax is similar to
    printf function.
    TODO Add to putInMiddle/putInRight functions check for strlen(buffer) >
    length (string too long).
*/
void putInMiddle(int start_r, int start_c, int length, const char * format, ...);
void putInRight(int start_r, int start_c, int length, const char * format, ...);
void putInLeft(int start_r, int start_c, int length, const char * format, ...);

#endif
