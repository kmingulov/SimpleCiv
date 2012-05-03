# object files to compile
OBJ = dyn_array.o int_array.o graph.o cell.o string_functions.o expat_handlers.o xml.o technology.o unit.o world.o test.o

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# flags for linking
LFLAGS = $(FLAGS) -lexpat $(DEBUG)

test: $(OBJ)
	gcc $(LFLAGS) -o test $(OBJ)

technology.o: ../../modules/technology/technology.c
	gcc $(CFLAGS) ../../modules/technology/technology.c

unit.o: ../../modules/unit/unit.c
	gcc $(CFLAGS) ../../modules/unit/unit.c

cell.o: ../../modules/cell/cell.c
	gcc $(CFLAGS) ../../modules/cell/cell.c

graph.o: ../../modules/graph/graph.c
	gcc $(CFLAGS) ../../modules/graph/graph.c

dyn_array.o: ../../modules/dyn_array/dyn_array.c
	gcc $(CFLAGS) ../../modules/dyn_array/dyn_array.c

int_array.o: ../../modules/int_array/int_array.c
	gcc $(CFLAGS) ../../modules/int_array/int_array.c

string_functions.o: ../../modules/parser/string_functions.c
	gcc $(CFLAGS) ../../modules/parser/string_functions.c

expat_handlers.o: ../../modules/parser/expat_handlers.c
	gcc $(CFLAGS) ../../modules/parser/expat_handlers.c

xml.o: ../../modules/parser/xml.c
	gcc $(CFLAGS) -lexpat ../../modules/parser/xml.c

world.o: ../../game/world/world.c
	gcc $(CFLAGS) ../../game/world/world.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
