all: play

# Compiler
CC = gcc

# Included files
INCLUDE = .

# Object files
OBJ = main.o input.o setup.o player.o teardown.o util.o scroller.o map.o

# Allegro option
# Arch Linux
#ALLEG = -L/usr/lib -Wl,--export-dynamic -lalleg-4.2.2 -lalleg_unsharable

# Ubuntu Linux
ALLEG = -L/usr/lib -Wl,--export-dynamic -lalleg -lm -lXxf86vm -lXcursor -lXpm -lXext -lX11 -lpthread -ldl

# Development options
CFLAGS = -g -Wall -c

# Release options
# CFLAGS = -O -Wall -ansi

play: $(OBJ)
	$(CC) -o play $(OBJ) $(ALLEG)

main.o: main.c common.h
	$(CC) $(CFLAGS) main.c $(ALLEG)

input.o: input.c common.h
	$(CC) $(CFLAGS) input.c $(ALLEG)

setup.o: setup.c common.h
	$(CC) $(CFLAGS) setup.c $(ALLEG)

player.o: player.c common.h
	$(CC) $(CFLAGS) player.c $(ALLEG)

teardown.o: teardown.c common.h
	$(CC) $(CFLAGS) teardown.c $(ALLEG)

util.o: util.c common.h
	$(CC) $(CFLAGS) util.c $(ALLEG)

scroller.o: scroller.c common.h
	$(CC) $(CFLAGS) scroller.c $(ALLEG)

map.o: map.c common.h
	$(CC) $(CFLAGS) map.c $(ALLEG)

clean:
	-rm *.o
	-rm play
	-rm *~
	-rm *.BAK