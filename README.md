Weird clone of Civilization game
================================

This is a clone of Civilization game. There is no name now. But it will be. Soon.

Concept
-------
You can find concept of this project in concept directory.

Requirements
------------
At all:
* ncurses

For compiling only:
* gcc
* make

Installation
------------
It's too easy:

    $ make

There is no install rule in Makefile. Because of this [picture](http://img99.imageshack.us/img99/3278/makeinstallandkitten.png).

Debug
-----
Use valgrind to find memory leaks and other unpleasant bugs (with memory):

    $ valgrind ./project

You need to know, what ncurses have a lot of memory "leaks". You can read more about this [here](http://invisible-island.net/ncurses/ncurses.faq.html#config_leaks).

Tests
-----
You can find tests for modules in tests directory. Compile them by simple `make`.

Tests use some of the modules and test *all* their functions (if possible with asserts).
