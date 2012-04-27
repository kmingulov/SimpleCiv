# object files to compile
OBJ = graph.o dyn_array.o cell.o world.o test.o

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# flags for linking
LFLAGS = $(FLAGS) -lm $(DEBUG)

test: $(OBJ)
	gcc $(LFLAGS) -o test $(OBJ)

cell.o: ../../modules/cell/cell.c
	gcc $(CFLAGS) ../../modules/cell/cell.c

graph.o: ../../modules/graph/graph.c
	gcc $(CFLAGS) ../../modules/graph/graph.c

dyn_array.o: ../../modules/dyn_array/dyn_array.c
	gcc $(CFLAGS) ../../modules/dyn_array/dyn_array.c

world.o: ../../game/world/world.c
	gcc $(CFLAGS) ../../game/world/world.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
