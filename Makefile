# Dark Mir makefile
# copyright Alexej alexej.x@mail.ru
# (c) 2008
# license GNU GPL3

TARGET = mir
CFLAGS = --std=c99 -Wall -pedantic -g $(shell sdl-config --cflags)  -O2 -DDEBUG
LDFLAGS = $(shell sdl-config --libs) -lSDL_image -lSDL_ttf  -lSDL_gfx -lm
OPTIMALIZE = -O2

CC = gcc

MODULY = program.o images.o vesmir.o kresli.o lod.o



all: $(MODULY)
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(TARGET) $(MODULY)

program.o: program.c program.h images.h
images.o: images.c images.h program.h
vesmir.o: vesmir.c  program.h images.h vesmir.h
kresli.o: kresli.c images.h program.h lod.h
lod.o: lod.c lod.h program.h zbrane.h

mir:
	./mir


clean:
	rm -f $(TARGET)
	rm -f $(MODULY)

ci: 
	svn ci

