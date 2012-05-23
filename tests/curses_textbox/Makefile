# object files to compile
OBJ = dyn_array.o int_array.o draw_functions.o view_textbox.o test.o

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# flags for linking
LFLAGS = $(FLAGS) -lm $(DEBUG)

test: $(OBJ)
	gcc $(LFLAGS) -o test $(OBJ) -lncurses

dyn_array.o: ../../modules/dyn_array/dyn_array.c
	gcc $(CFLAGS) ../../modules/dyn_array/dyn_array.c

int_array.o: ../../modules/int_array/int_array.c
	gcc $(CFLAGS) ../../modules/int_array/int_array.c

view_textbox.o: ../../game/view/view_textbox.c
	gcc $(CFLAGS) ../../game/view/view_textbox.c

draw_functions.o: ../../game/view/draw_functions.c
	gcc $(CFLAGS) ../../game/view/draw_functions.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
