#if 0
#!/bin/sh
gcc -Wall `sdl-config --cflags` tcpc.c -o tcpc `sdl-config --libs` -lSDL_net
 
exit
#endif
 
 
#include "program.h"
#include "protokol.h"
#include "server.h"
 
// =============================================================================
IPaddress ip;/* Server address */
TCPsocket sd;/* Socket descriptor */
int quit, len;
unsigned char tbuff[BUFF_SIZE];
unsigned char rbuff[BUFF_SIZE];
unsigned char nick[32]="NEW_PLAYER";
unsigned char *tp;

float f;

// =============================================================================
int main(int argc, char **argv){

// === INIT === 
  /* Simple parameter checking */
  if (argc < 3){
	fprintf(stderr, "Usage: %s host port\n", argv[0]);
	exit(EXIT_FAILURE);
  }
 
  if (SDLNet_Init() < 0){
	fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
 
/* Resolve the host we are connecting to */
  if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) < 0){
	fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
 
/* Open a connection with the IP provided (listen on the host's port) */
  if (!(sd = SDLNet_TCP_Open(&ip))){
	fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }

 		tp=tbuff;
		*tp = P_NEW_PLAYER;
		tp++;
		strncpy((char *) tp, (char *) nick, 31);
		printf("tbuff[0]: 0x%X\n",tbuff[0]);
		printf("tbuff+1: %s\n", tp);

		len = tp - &tbuff[0] +32 ;
		SEND;
		bzero(tbuff, BUFF_SIZE);

	/* Send messages */
	// =============================================================================
  quit = 2;
  while (quit > 0){

		//printf("Write something:\n>");
		tp=tbuff;
		*tp = P_SPEED_UP;
		printf("tbuff: 0x%X\n",tbuff[0]);

		SEND;

		sleep(1);
		quit--;
 
  }
		tp=rbuff;
  		RECV;
		tp++;
		f= *((float *) tp);
		printf("rbuff+1: %f ", (double) f);

 		tp=tbuff;
		*tp = P_LOGOUT;

  		SEND;
 
  SDLNet_TCP_Close(sd);
  SDLNet_Quit();
 
return EXIT_SUCCESS;
}
// =============================================================================




