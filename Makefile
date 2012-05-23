#
#	SimpleCiv is simple clone of Civilization game, using ncurses library.
#	Copyright (C) 2012 by K. Mingulov, A. Sapronov.
#
#	This program is free software; you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation; either version 2 of the License, or
#	(at your option) any later version.
#
#	This program is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License along
#	with this program; if not, write to the Free Software Foundation, Inc.,
#	51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
#

# common modules
OBJ_COMMON = list.o dyn_array.o int_array.o

# graph and map
OBJ_GRAPH = graph.o map.o landscape.o

# unit
OBJ_UNIT = unit.o unit_common_info.o unit_hiring.o unit_table.o

# city
OBJ_CITY = city.o

# technology
OBJ_TECH = technology.o technology_parse_info.o technology_research.o technology_table.o

# player
OBJ_PLAYER = player.o

# fog
OBJ_FOG = fog.o

# errors checking and log
OBJ_ERRORS = world_errors.o log.o

# parsing
OBJ_PARSE = string_functions.o expat_handlers.o xml.o

# helpful for ncurses and view
OBJ_NCURSES = curses_draws.o curses_chooser.o curses_textbox.o view_settings.o view_textbox.o

# main modules
OBJ_MAIN = world.o view.o control.o message.o main.o

# all objects
OBJ = $(OBJ_COMMON) $(OBJ_GRAPH) $(OBJ_UNIT) $(OBJ_CITY) $(OBJ_TECH) $(OBJ_PLAYER) $(OBJ_FOG) $(OBJ_ERRORS) $(OBJ_PARSE) $(OBJ_NCURSES) $(OBJ_MAIN)

# test mode
ifeq ($(t), 1)
	TEST_MODE = -DTEST_MODE=1
else
	TEST_MODE = -DTEST_MODE=0
endif

# compilation target
ifeq ($(win32), 1)
	CC = i686-w64-mingw32-gcc
	LFLIB = -lexpat -lpdcurses -lm
	BIN = simpleciv.exe
	TARGET = -DWIN32
else
	CC = gcc
	LFLIB = -lexpat -lncurses -lm
	BIN = simpleciv
	TARGET =
endif

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG) $(TARGET) $(TEST_MODE)

# flags for linking
LFLAGS = $(FLAGS) $(DEBUG)

# target
simpleciv: $(OBJ)
	$(CC) $(LFLAGS) -o $(BIN) $(OBJ) $(LFLIB)

# common modules
list.o: modules/list/list.c
	$(CC) $(CFLAGS) modules/list/list.c

dyn_array.o: modules/dyn_array/dyn_array.c
	$(CC) $(CFLAGS) modules/dyn_array/dyn_array.c

int_array.o: modules/int_array/int_array.c
	$(CC) $(CFLAGS) modules/int_array/int_array.c

# graph and map
graph.o: modules/graph/graph.c
	$(CC) $(CFLAGS) modules/graph/graph.c

map.o: modules/map/map.c
	$(CC) $(CFLAGS) modules/map/map.c

landscape.o: modules/landscape/landscape.c
	$(CC) $(CFLAGS) modules/landscape/landscape.c

# unit
unit.o: modules/unit/unit.c
	$(CC) $(CFLAGS) modules/unit/unit.c

unit_common_info.o: modules/unit/unit_common_info.c
	$(CC) $(CFLAGS) modules/unit/unit_common_info.c

unit_hiring.o: modules/unit/unit_hiring.c
	$(CC) $(CFLAGS) modules/unit/unit_hiring.c

unit_table.o: modules/unit/unit_table.c
	$(CC) $(CFLAGS) modules/unit/unit_table.c

# city
city.o: modules/city/city.c
	$(CC) $(CFLAGS) modules/city/city.c

# technology
technology.o: modules/technology/technology.c
	$(CC) $(CFLAGS) modules/technology/technology.c

technology_parse_info.o: modules/technology/technology_parse_info.c
	$(CC) $(CFLAGS) modules/technology/technology_parse_info.c

technology_research.o: modules/technology/technology_research.c
	$(CC) $(CFLAGS) modules/technology/technology_research.c

technology_table.o: modules/technology/technology_table.c
	$(CC) $(CFLAGS) modules/technology/technology_table.c

# player
player.o: modules/player/player.c
	$(CC) $(CFLAGS) modules/player/player.c

# fog
fog.o: modules/fog/fog.c
	$(CC) $(CFLAGS) modules/fog/fog.c

# errors checking and log
world_errors.o: game/world/world_errors.c
	$(CC) $(CFLAGS) game/world/world_errors.c

log.o: modules/log/log.c
	$(CC) $(CFLAGS) modules/log/log.c

# parsing
string_functions.o: modules/parser/string_functions.c
	$(CC) $(CFLAGS) modules/parser/string_functions.c

expat_handlers.o: modules/parser/expat_handlers.c
	$(CC) $(CFLAGS) modules/parser/expat_handlers.c

xml.o: modules/parser/xml.c
	$(CC) $(CFLAGS) modules/parser/xml.c

# helpful for ncurses and view
curses_draws.o: modules/widgets/curses_draws.c
	$(CC) $(CFLAGS) modules/widgets/curses_draws.c

curses_chooser.o: modules/widgets/curses_chooser.c
	$(CC) $(CFLAGS) modules/widgets/curses_chooser.c

curses_textbox.o: modules/widgets/curses_textbox.c
	$(CC) $(CFLAGS) modules/widgets/curses_textbox.c

view_settings.o: game/view/view_settings.c
	$(CC) $(CFLAGS) game/view/view_settings.c

view_textbox.o: game/view/view_textbox.c
	$(CC) $(CFLAGS) game/view/view_textbox.c

# main
world.o: game/world/world.c
	$(CC) $(CFLAGS) game/world/world.c

view.o: game/view/view.c
	$(CC) $(CFLAGS) game/view/view.c

control.o: game/control/control.c
	$(CC) $(CFLAGS) game/control/control.c

message.o: game/message/message.c
	$(CC) $(CFLAGS) game/message/message.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

# clean
clean:
	rm -f *.o simpleciv simpleciv.exe tests/*/*.o tests/*/test
