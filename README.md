SimpleCiv
=========
**SimpleCiv** is *really* simple clone of Civilization game. It's free software (released under GNU GPL v2 license), written in pure C, using ncurses and expat libraries *(unfortunely, we don't use all power of ncurses)*.

Features:
* technology tree and researchs, as in original Civilization, but with several exception: you don't know, what the technologies are in the end of this tree; you can't research some technology, if you don't have special nature resource.
* hiring units and fighting between them
* multiplayer («hot seat»)

Or, in the nutshell, differents with Civilization:
* no buildings
* no unit's experience or city's levels
* no diplamacy
* no AI
* different technology tree implementation

**SimpleCiv** is really simple :)

Compilation
------------
In general, simply `make`. For notes about compilation look for [this article](https://github.com/Melkogotto/SimpleCiv/wiki/Compiling-for-Linux) (Linux) or for [this](https://github.com/Melkogotto/SimpleCiv/wiki/Compiling-for-Windows) (Windows).

There is no install rule in Makefile, because of this [picture](http://img99.imageshack.us/img99/3278/makeinstallandkitten.png).

Debug
-----
Use valgrind to find memory leaks and other unpleasant bugs (with memory):

    $ valgrind ./project

You need to know, what ncurses have a lot of memory "leaks". You can read more about this [here](http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks).

Concept
-------
You can find concept of this project in "docs" directory.

Keyboard control
----------------
**Map window**
* *Arrow keys* — move map/unit.
* *Enter* — end turn.
* *Space* — choose unit to move or open city dialog to hire units.
* *c* — create city (choosed settler is needed).
* *t* — open researching technologies dialog.
* *q* — quit game.

**Technologies dialog**
* *Up/down arrow keys* — choose technology.
* *Enter* — start researching (will terminate current researching).
* *q* — return to map.

**Hiring units dialog**
* *Up/down arrow keys* — choose unit.
* *Enter* — start hiring (will terminate current hiring).
* *q* — return to map.
