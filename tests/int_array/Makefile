# object files to compile
OBJ = int_array.o test.o

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# flags for linking
LFLAGS = $(FLAGS) $(DEBUG)

test: $(OBJ)
	gcc $(LFLAGS) -o test $(OBJ)

int_array.o: ../../modules/int_array/int_array.c
	gcc $(CFLAGS) ../../modules/int_array/int_array.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
