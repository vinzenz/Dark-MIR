# Dark Mir makefile
# copyright Alexej alexej.x@mail.ru
# (c) 2008-2010
# license GNU GPL3

TARGET = mir
SERVER_TARGET = server
CFLAGS = --std=c99 -Wall -pedantic -g $(shell sdl-config --cflags)  -O2 -DDEBUG 
LDFLAGS = $(shell sdl-config --libs) -lSDL_image -lSDL_ttf  -lSDL_gfx -lSDL_net -lm
OPTIMALIZE = -O2

CC = gcc

MODULES = program.o images.o vesmir.o kresli.o lod.o
SERVER_MODULES = server.o



.PHONY: all run clean ci

all: $(MODULES)  $(SERVER_TARGET) client
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(TARGET) $(MODULES)

program.o: program.c program.h images.h
images.o: images.c images.h program.h
vesmir.o: vesmir.c  program.h images.h vesmir.h lod.h ships.h protokol.h
kresli.o: kresli.c images.h program.h lod.h
lod.o: lod.c lod.h program.h zbrane.h weapons.h


client: client.o
	$(CC) $(CFLAGS) $(LDFLAGS)  -o client client.o

client.o: client.c server.h program.h protokol.h

server: $(SERVER_MODULES)
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(SERVER_TARGET) $(SERVER_MODULES)

server.o: server.c server.h program.h protokol.h

run:
	./mir


clean:
	rm -f $(TARGET)
	rm -f $(SERVER_TARGET)
	rm -f $(MODULES)
	rm -f $(SERVER_MODULES)

ci: 
	svn ci

