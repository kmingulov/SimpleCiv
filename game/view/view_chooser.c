#include <stdlib.h>

#include "../../modules/player/player.h"
#include "../../modules/technology/technology.h"
#include "../../modules/technology/technology_table.h"
#include "../../modules/unit/unit_common_info.h"
#include "../world/definitions.h"
#include "view_chooser.h"

ViewChooser * createTechChooser(World * world)
{
    ViewChooser * chooser = malloc(sizeof(ViewChooser));

    chooser -> ids = iaCreate();
    chooser -> current = -1;
    chooser -> start_r = -1;

    Player * player = (Player *) world -> graph_players -> data;

    int count = 0;
    for(int i = 0; i < player -> available_techs -> length; i++)
    {
        int value = iaGetByIndex(player -> available_techs, i);
        if(value == TECH_AVAILABLE)
        {
            Technology * tech = (Technology *) ((Node *) daGetByIndex(world -> techs_info, i)) -> data;
            // Adding to array, if player have enough resources.
            if(checkForResources(tech, player) == 0)
            {
                iaPrepend(chooser -> ids, tech -> id);
            }
            // It is current research?
            if(tech -> id == player -> research -> id)
            {
                chooser -> current = count - 1;
            }
        }
    }

    return chooser;
}

ViewChooser * createUnitChooser(World * world, City * city)
{
    ViewChooser * chooser = malloc(sizeof(ViewChooser));

    chooser -> ids = iaCreate();
    chooser -> current = -1;
    chooser -> start_r = -1;

    Player * player = (Player *) world -> graph_players -> data;

    int count = 0;
    for(int i = 0; i < player -> available_units -> length; i++)
    {
        int value = iaGetByIndex(player -> available_units, i);
        if(value == UNIT_AVAILABLE)
        {
            UnitCommonInfo * u_info = daGetByIndex(world -> units_info, i);
            // Checking for resources.
            if(u_info -> resources == NULL)
            {
                // Nothing requires. Great.
                iaPrepend(chooser -> ids, i);
                // It is current hiring?
                if(i == city -> hiring -> id)
                {
                    chooser -> current = count;
                }
                count++;
            }
            else
            {
                // Checking for each resource.
                char okay = 1;
                for(int j = 0; j < u_info -> resources -> length; j++)
                {
                    // Getting resource id.
                    int id = iaGetByIndex(u_info -> resources, j);
                    // Does player have this resources?
                    if(iaGetByIndex(player -> resources, id) == 0)
                    {
                        // Sad but true.
                        okay = 0;
                        break;
                    }
                }
                // You're lucky man.
                if(okay == 1)
                {
                    iaPrepend(chooser -> ids, i);
                    // It is current hiring?
                    if(i == city -> hiring -> id)
                    {
                        chooser -> current = count;
                    }
                    count++;
                }
            }
        }
    }

    return chooser;
}

void destroyChooser(ViewChooser * chooser)
{
    iaDestroy(chooser -> ids);
    free(chooser);
}
