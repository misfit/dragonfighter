all: play

# Compiler
CC = gcc

# Included files
INCLUDE = .

# Object files
OBJ = main.o maps.o setup.o util.o input.o eventhand.o maphand.o player.o \
scroller.o 

# Allegro option
# For Arch Linux:
#ALLEG = -L/usr/lib -Wl,--export-dynamic -lalleg-4.2.2 -lalleg_unsharable
# For Xubuntu 9.04:
ALLEG = -L/usr/lib -Wl,--export-dynamic -lalleg -lm -lXxf86vm -lXcursor -lXpm -lXext -lX11 -lpthread -ldl

# Development options
CFLAGS = -g -Wall -ansi -c

# Release options
# CFLAGS = -O -Wall -ansi

play: $(OBJ)
	$(CC) -o play $(OBJ) $(ALLEG)

main.o: main.c common.h
	$(CC) $(CFLAGS) main.c $(ALLEG)

maps.o: maps.c common.h
	$(CC) $(CFLAGS) maps.c $(ALLEG)

setup.o: setup.c common.h
	$(CC) $(CFLAGS) setup.c $(ALLEG)

util.o: util.c common.h
	$(CC) $(CFLAGS) util.c $(ALLEG)

input.o: input.c common.h
	$(CC) $(CFLAGS) input.c $(ALLEG)

eventhand.o: eventhand.c common.h
	$(CC) $(CFLAGS) eventhand.c $(ALLEG)

maphand.o: maphand.c common.h
	$(CC) $(CFLAGS) maphand.c $(ALLEG)

player.o: player.c common.h
	$(CC) $(CFLAGS) player.c $(ALLEG)

scroller.o: scroller.c common.h
	$(CC) $(CFLAGS) scroller.c $(ALLEG)

clean:
	-rm *.o
	-rm play
	-rm *~
	-rm *.BAK