#include <stdlib.h>

#include "../../modules/player/player.h"
#include "../../modules/technology/technology.h"
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
            Technology * t = (Technology *) ((Node *) daGetByIndex(world -> techs_info, i)) -> data;
            // Checking for resources.
            if(t -> requires_resources == NULL)
            {
                // Nothing requires. Great.
                count++;
                iaPrepend(chooser -> ids, t -> id);
            }
            else
            {
                // Checking for each resource.
                char okay = 1;
                for(int j = 0; j < t -> requires_resources -> length; j++)
                {
                    // Getting resource id.
                    int id = iaGetByIndex(t -> requires_resources, j);
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
                    count++;
                    iaPrepend(chooser -> ids, t -> id);
                }
            }
            // It is current research?
            if(t -> id == player -> research -> id)
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
            iaPrepend(chooser -> ids, i);
            // It is current research?
            if(i == city -> hiring -> id)
            {
                chooser -> current = count;
            }
            count++;
        }
    }

    return chooser;
}

void destroyChooser(ViewChooser * chooser)
{
    iaDestroy(chooser -> ids);
    free(chooser);
}
