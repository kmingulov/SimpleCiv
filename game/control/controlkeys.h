
#ifndef __CONTROLKEYS_H
#define __CONTROLKEYS_H

#include "../../modules/list/list.h"
#include "../world/world.h"
#include "../view/view.h"
#include "control.h"


List * pushKeyT (World * world, View * view, Control * control);
List * pushKeyQ (View * view, Control * control);
List * pushKeyH (View * view, Control * control);
List * pushKeyI (World * world, View * view,  Control * control);
List * pushKeyC (World * world, View * view,  Control * control);
List * pushKeyB (World * world, View * view,  Control * control);
List * pushKeyN (World * world, View * view,  Control * control);
List * pushKeyM (World * world, View * view,  Control * control);

#endif
