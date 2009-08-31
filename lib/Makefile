all: dragonfighter

# Compiler
CC = gcc

# Included files
INCLUDE = .

# Object files
OBJ = main.o dragonfighter.o mappyal.o

# Allegro option
ALLEG = -L/usr/lib -Wl,--export-dynamic -lalleg-4.2.2 -lalleg_unsharable

# Development options
CFLAGS = -g -Wall -ansi -c

# Release options
# CFLAGS = -O -Wall -ansi

dragonfighter: $(OBJ)
	$(CC) -o dragonfighter $(OBJ) $(ALLEG)

main.o: main.c dragonfighter.h
	$(CC) $(CFLAGS) main.c $(ALLEG)

dragonfighter.o: dragonfighter.c dragonfighter.h maps.h
	$(CC) $(CFLAGS) dragonfighter.c $(ALLEG)

mappyal.o: mappyal.c mappyal.h
	$(CC) mappyal.c -02 -Wall -c -o mappyal.o

clean:
	rm *.o
	rm dragonfighter
	rm *~