#if 0
#!/bin/sh
gcc -Wall `sdl-config --cflags` tcpc.c -o tcpc `sdl-config --libs` -lSDL_net
 
exit
#endif

// UDP testing code for DARK MIR

 
#include "program.h"
#include "protokol.h"
#include "server.h"
 
// =============================================================================
IPaddress ip;/* Server address */
UDPsocket usd;
UDPpacket *t;
UDPpacket *r;

int quit, len;
//unsigned char tbuff[BUFF_SIZE];
//unsigned char rbuff[BUFF_SIZE];
unsigned char nick[NICKNAME_MAX]="NEW_PLAYER";
unsigned char *tp;

float f;
int ack=0;

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


  if (!(usd = SDLNet_UDP_Open(0))) {
	fprintf(stderr, "SDLNet_UDP_Open: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }

  /* Resolve server name  */
  if (SDLNet_ResolveHost(&ip, argv[1], atoi(argv[2])) == -1) {
	fprintf(stderr, "SDLNet_ResolveHost(%s %d): %s\n", argv[1], atoi(argv[2]), SDLNet_GetError());
	exit(EXIT_FAILURE);
  }

  /* Allocate memory for the packet */
   if (!(t = SDLNet_AllocPacket(512))) {
	fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
  if (!(r = SDLNet_AllocPacket(512))) {
	fprintf(stderr, "SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
  
 
  t->address.host = ip.host;	/* Set the destination host */
  t->address.port = ip.port;	/* And destination port */
  t->len = BUFF_SIZE;

 		tp = t->data;
		*tp = P_NEW_PLAYER;
		tp++;
		strncpy((char *) tp, (char *) nick, 31);

		printf("tbuff[0]: 0x%X\n",t->data[0]);
		printf("tbuff+1: %s\n", tp);

		UDP_SEND;

			POINT(1);
	while(ack == 0){
		UDP_RECV{
			ack = r->data[0];
			printf("0x%X\n", ack);
			POINT('A');
		}
	}
  /* Send messages */
  // =============================================================================
  quit = 2;
  while (quit > 0){

		tp = t->data;
		*tp = P_SPEED_UP;
		printf("tbuff[0]: 0x%X\n",t->data[0]);

		UDP_SEND;

		sleep(1);
		quit--;
 
  }

 		tp = t->data;
		*tp = P_LOGOUT;

  		UDP_SEND;
 
  SDLNet_UDP_Close(usd);
  SDLNet_Quit();
 
return EXIT_SUCCESS;
}
// =============================================================================




