#ifndef VIEW_TEXTBOX
#define VIEW_TEXTBOX

#include "../../modules/dyn_array/dyn_array.h"
#include "../../modules/int_array/int_array.h"

typedef struct ViewTextbox
{
    // Start point.
    int start_r, start_c;

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
ViewTextbox * createViewTextbox(int start_r, int start_c, int r, int c);

/*
    Adds formatted string to textbox (bold or not).
*/
void addString(ViewTextbox * tb, const char * format, ...);
void addBoldString(ViewTextbox * tb, const char * format, ...);

/*
    Draws textbox.
*/
void drawViewTextbox(ViewTextbox * tb);

/*
    Destroys textbox.
*/
void destroyViewTextbox(ViewTextbox * textbox);

#endif
