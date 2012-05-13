#ifndef VIEW_CHOOSER
#define VIEW_CHOOSER

#include "../../modules/int_array/int_array.h"
#include "../../modules/city/city.h"
#include "../world/world.h"

/*
    Struct of view chooser (for some menus).
*/
typedef struct ViewChooser
{
    // Array of ids.
    IntArray * ids;
    // Current id.
    int current;
    // First row of the list with items.
    int start_r;
} ViewChooser;

/*
    Functions of creation and destruction chooser.
*/
ViewChooser * createTechChooser(World * world);
ViewChooser * createUnitChooser(World * world, City * city);
void destroyChooser(ViewChooser * chooser);

#endif
