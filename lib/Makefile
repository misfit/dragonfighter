all: dragonfighter

# Compiler
CC = gcc

# Included files
INCLUDE = .

# Allegro option
ALLEG = -L/usr/lib -Wl,--export-dynamic -lalleg-4.2.2 -lalleg_unsharable

# Development options
CFLAGS = -g -Wall -ansi -c

# Release options
# CFLAGS = -O -Wall -ansi

dragonfighter: main.o setup.o input.o hero.o maps.o
	$(CC) -o dragonfighter main.o setup.o input.o hero.o maps.o $(ALLEG)

main.o: main.c dragonfighter.h maps.h
	$(CC) $(CFLAGS) main.c $(ALLEG)

setup.o: setup.c dragonfighter.h
	$(CC) $(CFLAGS) setup.c $(ALLEG)

input.o: input.c dragonfighter.h
	$(CC) $(CFLAGS) input.c $(ALLEG)

hero.o: hero.c dragonfighter.h
	$(CC) $(CFLAGS) hero.c $(ALLEG)

maps.o: maps.c dragonfighter.h maps.h
	$(CC) $(CFLAGS) maps.c $(ALLEG)

clean:
	rm *.o
	rm dragonfighter
	rm *~