# object files to compile whole project
OBJ = map.o landscape.o cui.o cui-print.o main.o

# all libs' flags
LIBS = -lm -lncurses

# debug flag
DEBUG = -g

# common flags
FLAGS = -std=c99 -Wall -pedantic

# flags for compilation object files
CFLAGS = $(FLAGS) -c $(DEBUG)

# flags for linking
LFLAGS = $(FLAGS) $(DEBUG)

project: $(OBJ)
	gcc $(LFLAGS) $(LIBS) -o project $(OBJ)

main.o: main.c
	gcc $(CFLAGS) -lm main.c

map.o: modules/map/map.c
	gcc $(CFLAGS) -lm modules/map/map.c

landscape.o: modules/landscape/landscape.c
	gcc $(CFLAGS) -lm modules/landscape/landscape.c

cui.o: modules/cui/cui.c
	gcc $(CFLAGS) -lncurses modules/cui/cui.c

cui-print.o: modules/cui/cui-print.c
	gcc $(CFLAGS) -lncurses modules/cui/cui-print.c

clean:
	rm -f *.o project
