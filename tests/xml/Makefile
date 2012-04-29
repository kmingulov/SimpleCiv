# object files to compile
OBJ = test.o string_functions.o expat_handlers_config.o xml.o

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

string_functions.o: ../../modules/parser/string_functions.c
	gcc $(CFLAGS) -lexpat ../../modules/parser/string_functions.c

expat_handlers_config.o: ../../modules/parser/expat_handlers_config.c
	gcc $(CFLAGS) -lexpat ../../modules/parser/expat_handlers_config.c

xml.o: ../../modules/parser/xml.c
	gcc $(CFLAGS) -lexpat ../../modules/parser/xml.c

test.o: test.c
	gcc $(CFLAGS) -lexpat test.c

clean:
	rm -f *.o test
