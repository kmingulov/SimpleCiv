# object files to compile
OBJ = dyn_array.o int_array.o curses_draws.o curses_textbox.o curses_chooser.o test.o

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

curses_textbox.o: ../../modules/widgets/curses_textbox.c
	gcc $(CFLAGS) ../../modules/widgets/curses_textbox.c

curses_chooser.o: ../../modules/widgets/curses_chooser.c
	gcc $(CFLAGS) ../../modules/widgets/curses_chooser.c

curses_draws.o: ../../modules/widgets/curses_draws.c
	gcc $(CFLAGS) ../../modules/widgets/curses_draws.c

test.o: test.c
	gcc $(CFLAGS) test.c

clean:
	rm -f *.o test
