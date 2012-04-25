# object files to compile
OBJ = graph.o dyn_array.o map.o landscape.o model.o test.o

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

map.o: ../../modules/map/map.c
	gcc $(CFLAGS) ../../modules/map/map.c

landscape.o: ../../modules/landscape/landscape.c
	gcc $(CFLAGS) ../../modules/landscape/landscape.c

graph.o: ../../modules/graph/graph.c
	gcc $(CFLAGS) ../../modules/graph/graph.c

dyn_array.o: ../../modules/dyn_array/dyn_array.c
	gcc $(CFLAGS) ../../modules/dyn_array/dyn_array.c

model.o: ../../game/model/model.c
	gcc $(CFLAGS) ../../game/model/model.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
