# object files to compile
OBJ = list.o test.o

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# libs
LFLIB =

# flags for linking
LFLAGS = $(FLAGS) $(LFLIB) $(DEBUG)

test: $(OBJ)
	gcc $(LFLAGS) -o test $(OBJ)

list.o: ../../modules/list/list.c
	gcc $(CFLAGS) ../../modules/list/list.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
