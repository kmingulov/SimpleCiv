# object files to compile
OBJ = list.o dyn_array.o int_array.o graph.o cell.o landscape.o string_functions.o expat_handlers.o xml.o unit.o city.o player.o technology.o view.o world.o message.o control.o main.o

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# libs
LFLIB = -lexpat -lncurses -lm

# flags for linking
LFLAGS = $(FLAGS) $(LFLIB) $(DEBUG)

project: $(OBJ)
	gcc $(LFLAGS) -o project $(OBJ)

technology.o: modules/technology/technology.c
	gcc $(CFLAGS) modules/technology/technology.c

city.o: modules/city/city.c
	gcc $(CFLAGS) modules/city/city.c

unit.o: modules/unit/unit.c
	gcc $(CFLAGS) modules/unit/unit.c

cell.o: modules/cell/cell.c
	gcc $(CFLAGS) modules/cell/cell.c

landscape.o: modules/landscape/landscape.c
	gcc $(CFLAGS) modules/landscape/landscape.c

graph.o: modules/graph/graph.c
	gcc $(CFLAGS) modules/graph/graph.c

list.o: modules/list/list.c
	gcc $(CFLAGS) modules/list/list.c

dyn_array.o: modules/dyn_array/dyn_array.c
	gcc $(CFLAGS) modules/dyn_array/dyn_array.c

int_array.o: modules/int_array/int_array.c
	gcc $(CFLAGS) modules/int_array/int_array.c

string_functions.o: modules/parser/string_functions.c
	gcc $(CFLAGS) modules/parser/string_functions.c

expat_handlers.o: modules/parser/expat_handlers.c
	gcc $(CFLAGS) modules/parser/expat_handlers.c

xml.o: modules/parser/xml.c
	gcc $(CFLAGS) -lexpat modules/parser/xml.c

player.o: modules/player/player.c
	gcc $(CFLAGS) -lexpat modules/player/player.c
	
view.o: game/view/view.c
	gcc $(CFLAGS) game/view/view.c

world.o: game/world/world.c
	gcc $(CFLAGS) game/world/world.c
	
message.o: game/message/message.c
	gcc $(CFLAGS) game/message/message.c
	
control.o: game/control/control.c
	gcc $(CFLAGS) game/control/control.c
	
	
main.o: main.c
	gcc $(CFLAGS) main.c

clean:
	rm -f *.o test
