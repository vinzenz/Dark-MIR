u===============================================================================
# Dark Mir makefile
# copyright Alexej alexej.x@mail.ru
# (c) 2008-2010
# license GNU GPL3
#===============================================================================

TARGET = mir
SERVER_TARGET = server
CFLAGS = --std=c99 -Wall -pedantic  $(shell sdl-config --cflags)  -O2  -g
LDFLAGS = $(shell sdl-config --libs) -lSDL_image -lSDL_ttf -lSDL_net -lm -lSDL_gfx
OPTIMALIZE = -O2

CC=$(CROSS)gcc
LD=$(CROSS)ld
AR=$(CROSS)ar

MODULES = program.o images.o vesmir.o kresli.o lod.o protokol.o menu.o network.o garbage.o configure.o objects.o debug.o
SERVER_MODULES = server.o objects.o

#===============================================================================


.PHONY: all run local gdb clean ci

#===============================================================================
all: $(TARGET)   $(SERVER_TARGET) 
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(TARGET) $(MODULES) 

c: clean $(TARGET)   $(SERVER_TARGET) 
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(TARGET) $(MODULES) 


$(TARGET): $(MODULES)
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(TARGET) $(MODULES) -DCLIENT

program.o: program.c program.h images.h client.h
images.o: images.c program.h images.h 
vesmir.o: vesmir.c  program.h images.h vesmir.h lod.h ships.h protokol.h objects.h
kresli.o: kresli.c program.h images.h lod.h
lod.o: lod.c lod.h program.h zbrane.h weapons.h
protokol.o: protokol.c program.h protokol.h client.h
menu.o: menu.c program.h protokol.h client.h menu.h
network.o: network.c program.h protokol.h client.h 
garbage.o: garbage.c program.h images.h
configure.o: configure.c program.h images.h
objects.o: objects.c program.h images.h objects.h weapons.h asteroids.h zbrane.h
debug.o: debug.c program.h objects.h


#===============================================================================
udp_client: udp_client.o
	$(CC) $(CFLAGS) $(LDFLAGS)  -o udp_client udp_client.o

udp_client.o: udp_client.c server.h program.h protokol.h		
#client.o: client.c server.h program.h protokol.h		# TCP

#===============================================================================
$(SERVER_TARGET): $(SERVER_MODULES)
	$(CC) $(CFLAGS) $(LDFLAGS)  -o $(SERVER_TARGET) $(SERVER_MODULES) -DSERVER

server.o: server.c server.h program.h protokol.h lod.h ships.h zbrane.h weapons.h



#===============================================================================
clean:
	rm -f *.o
	rm -f client
	rm -f $(TARGET)
	rm -f $(SERVER_TARGET)
	rm -f $(MODULES)
	rm -f $(SERVER_MODULES)

ci: 
	svn ci

#===============================================================================
run: all
	(./server &) || killall server && ./server &
	./mir 

#===============================================================================
local:
	./mir -n $(USER)   localhost

#===============================================================================
l:
	./mir -r 4 -n Alexej   localhost

#===============================================================================
gdb:
	gdb --args ./mir -n $(USER)   localhost
