/*

    SimpleCiv is simple clone of Civilization game, using ncurses library.
    Copyright (C) 2012 by K. Mingulov, A. Sapronov.

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

*/

#include <stdio.h>
#include <stdlib.h>

#include "modules/log/log.h"
#include "game/world/world.h"
#include "game/view/view.h"
#include "game/control/control.h"
#include "game/message/message.h"

int main()
{
    // Creating log.
    FILE * log = startLog();

    // Creating world and view and control.
    World * world = createWorld(log);
    View * view = createView(world);
    Control * control = createControl();

    if(world == NULL || view == NULL || control == NULL)
    {
        printf("An error has occurred. For details look to the LOG file.\n");
        endLog(log);
        return 1;
    }

    // Init first message.
    List * queue = listCreate();
    listPrepend(queue, createMessage(VIEW_REDRAW_ALL));

    // Infinite loop.
    while(true)
    {
        // Process the view. Redraws some elements. Depends on action: control
        // decides what view needs to redraw.
        if(viewProcess(world, view, queue) == 0)
        {
            // Good bye.
            break;
        }

        int key = getch();

        // Processes the control. Does something with the world. Depends on the
        // key.
        queue = controlProcess(world, view, control, key);
    }

    // Destroing everything.
    destroyControl(control);
    destroyView(view);
    destroyWorld(world);
    endLog(log);

    return 0;
}
