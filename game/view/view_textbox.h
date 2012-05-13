#ifndef VIEW_TEXTBOX
#define VIEW_TEXTBOX

#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/int_array/int_array.h"

typedef struct ViewTextbox
{
    // Sizes.
    int r, c;

    // Page count.
    int pages_count;

    // Current page.
    int current_page;

    // Lines per page.
    int lines_per_page;

    // Array of char strings.
    DynArray * lines;

    // Array of line's properties: bold or not.
    IntArray * properties;
} ViewTextbox;

/*
    Creates new textbox.
*/
ViewTextbox * createViewTextbox(int r, int c, int lines_per_page);

/*
    Adds string to textbox.
*/
void addString(ViewTextbox * tb, char * string, int bold);

/*
    Draws textbox.
*/
void drawViewTextbox(ViewTextbox * tb);

/*
    Destroys textbox.
*/
void destroyViewTextbox(ViewTextbox * textbox);

#endif
