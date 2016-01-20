SimpleCiv
=========
**SimpleCiv** is a *really* simple clone of Civilization game. It's free software (released under GNU GPL v2 license), written in pure C, using ncurses and expat libraries.

Features:
* Technology tree and research, as in the original Civilization, but with several exceptions: you don't know, what the technologies are in the end of this tree; you can't research some technologies, if you don't have special nature resources for them.
* Hiring units and fighting.
* Multiplayer ("hot seat")

Or, in the nutshell, differents with Civilization:
* no buildings,
* no unit's experience or city's levels,
* no diplomacy,
* no AI,
* different technology tree implementation.

**SimpleCiv** is really simple :)

Compilation
-----------
In general, simply `make`. For notes about compilation look for [this article](https://github.com/Melkogotto/SimpleCiv/wiki/Compiling-for-Linux) (Linux) or for [this](https://github.com/Melkogotto/SimpleCiv/wiki/Compiling-for-Windows) (Windows).

Keyboard control
----------------
**Map window**
* *Arrow keys* — move map/unit.
* *Enter* — end turn.
* *Space* — choose unit to move or open city dialog to hire units.
* *c* — create city (choosed settler is needed).
* *b* — chop the forest (choosed lumberjack and forest on the cell are needed).
* *m* — build the mine (choosed miner are needed).
* *t* — open researching technologies dialog.
* *h* — show help.
* *i* — show unit info.
* *n* — show next unit (if selected) or city.
* *q* — quit game.

**Technologies dialog**
* *Up/down arrow keys* — choose technology.
* *Enter* — start researching (will terminate current researching).
* *q* — return to map.

**Hiring units dialog**
* *Up/down arrow keys* — choose unit.
* *Enter* — start hiring (will terminate current hiring).
* *q* — return to map.

Debug
-----
Use valgrind to find memory leaks and other unpleasant bugs (with memory):

    $ valgrind ./project

You need to know, what ncurses have a lot of memory "leaks". You can read more about this [here](http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks).

Concept
-------
You can find concept of this project in "docs" directory (mostly in Russian).