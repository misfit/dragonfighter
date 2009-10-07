all: play

# Compiler
CC = gcc

# Included files
INCLUDE = .

# Object files
OBJ = main.o maps.o setup.o util.c

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

util.o: util.c commont.h
	$(CC) $(CFLAGS) util.c $(ALLEG)

clean:
	-rm *.o
	-rm play
	-rm *~
	-rm *.BAK