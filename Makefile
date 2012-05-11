# object files to compile
OBJ = list.o dyn_array.o int_array.o graph.o cell.o landscape.o string_functions.o expat_handlers.o xml.o unit.o city.o player.o technology.o draw_functions.o view.o world.o message.o control.o main.o

# compilation target
ifeq ($(win32), 1)
	CC = i686-w64-mingw32-gcc
	LFLIB = -lexpat -lpdcurses -lm
	BIN = simpleciv.exe
	TARGET = -Dwin32
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
CFLAGS = $(FLAGS) -c $(DEBUG) $(TARGET)

# flags for linking
LFLAGS = $(FLAGS) $(DEBUG)

simpleciv: $(OBJ)
	$(CC) $(LFLAGS) -o $(BIN) $(OBJ) $(LFLIB)

technology.o: modules/technology/technology.c
	$(CC) $(CFLAGS) modules/technology/technology.c

city.o: modules/city/city.c
	$(CC) $(CFLAGS) modules/city/city.c

unit.o: modules/unit/unit.c
	$(CC) $(CFLAGS) modules/unit/unit.c

cell.o: modules/cell/cell.c
	$(CC) $(CFLAGS) modules/cell/cell.c

landscape.o: modules/landscape/landscape.c
	$(CC) $(CFLAGS) modules/landscape/landscape.c

graph.o: modules/graph/graph.c
	$(CC) $(CFLAGS) modules/graph/graph.c

list.o: modules/list/list.c
	$(CC) $(CFLAGS) modules/list/list.c

dyn_array.o: modules/dyn_array/dyn_array.c
	$(CC) $(CFLAGS) modules/dyn_array/dyn_array.c

int_array.o: modules/int_array/int_array.c
	$(CC) $(CFLAGS) modules/int_array/int_array.c

string_functions.o: modules/parser/string_functions.c
	$(CC) $(CFLAGS) modules/parser/string_functions.c

expat_handlers.o: modules/parser/expat_handlers.c
	$(CC) $(CFLAGS) modules/parser/expat_handlers.c

xml.o: modules/parser/xml.c
	$(CC) $(CFLAGS) -lexpat modules/parser/xml.c

player.o: modules/player/player.c
	$(CC) $(CFLAGS) -lexpat modules/player/player.c

draw_functions.o: game/view/draw_functions.c
	$(CC) $(CFLAGS) game/view/draw_functions.c

view.o: game/view/view.c
	$(CC) $(CFLAGS) game/view/view.c

world.o: game/world/world.c
	$(CC) $(CFLAGS) game/world/world.c

message.o: game/message/message.c
	$(CC) $(CFLAGS) game/message/message.c

control.o: game/control/control.c
	$(CC) $(CFLAGS) game/control/control.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -f *.o simpleciv simpleciv.exe tests/*/*.o tests/*/test
