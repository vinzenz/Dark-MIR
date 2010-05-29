


#include "program.h"
#include "server.h"
#include "lod.h"
#include "ships.h"
#include "vesmir.h"
#include "zbrane.h"

#define TTY stdout
#define MAX_PLAYERS 2

#define BUFF_SIZE 512

/* Communication Protokol Description v0.01
 * 
 * Clients request
 *
 * 1. Byte = request code
 * 2. - ... data
 *
 *
 *  0x01 = new player
 *  0x02 = 
 *  0x03 =
 *
 *  0x10 = rotate right
 *  0x11 = rotate left
 *  0x12 = accelerate speed up
 *  0x13 = slow down
 *  0x14 = shift right
 *  0x15 = shift left
 *
 *  0x41 = fire 1. weapon
 *  0x42 = fire 2. weapon
 *  0x43 = fire 2. weapon
 *
 *  0xFF = logout
 */


/* Server answer
 * 
 * 1. Byte = answer code
 * 2. Byte ...N X position
 * N. Byte ...M Y position
 * N. Byte ...M angle
 * N. Byte ...M speed
 *
 *
 *
 */
typedef struct str_player{
	IPaddress  ip;	
	char nick[32];
	
	int score;
	T_ship ship;
	
} T_player;


T_player player[MAX_PLAYERS+1];

// Function prototypes
 //==============================================================================
int Init_server();
int Server();
int New_client(T_player *p);

int Inicializuj_objekty();
int Pohybuj_objekty();
int Detekuj_kolize();
 int Collision_detect(T_ship *ship, T_weapon *weapon );

// Global variables
 //==============================================================================
  TCPsocket sd, csd; /* Socket descriptor, Client socket descriptor */
  IPaddress ip, *remoteIP;

  int players = 0;	// count of
  unsigned char buffer[512];

 //==============================================================================
 //==============================================================================
int main(int argc, char **argv){
 //==============================================================================
  
  Init_server();
  Server();

 return EXIT_SUCCESS;
}

 //==============================================================================
int Init_server(){
 //==============================================================================
 
  if (SDLNet_Init() == FAIL){
	fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
 
/* Resolving the host using NULL make network interface to listen */
  if (SDLNet_ResolveHost(&ip, NULL, PORT) == FAIL){
	fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
 
/* Open a connection with the IP provided (listen on the host's port) */
  if (!(sd = SDLNet_TCP_Open(&ip))){
	fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
 


 return OK;
}


//==============================================================================
int Server(){
//==============================================================================

  int quit, quit2;
	/* Wait for a connection, send data and term */
  quit = 0;
while (!quit){

  /* This check the sd if there is a pending connection.
   * If there is one, accept that, and open a new socket for communicating */
  if ((csd = SDLNet_TCP_Accept(sd))){
  
  /* Now we can communicate with the client using csd socket
   * sd will remain opened waiting other connections */
 
  /* Get the remote address */
  if ((remoteIP = SDLNet_TCP_GetPeerAddress(csd))){
 	 /* Print the address, converting in the host format */
	printf("Host connected: %x %d\n", 
		SDLNet_Read32(&remoteIP->host), SDLNet_Read16(&remoteIP->port));
/*
	if( players < MAX_PLAYERS ){
		if(New_client(&player[players]) == OK){
			players++;
		}
	}

*/
  }
  else
	fprintf(stderr, "SDLNet_TCP_GetPeerAddress: %s\n", SDLNet_GetError());
  quit2 = 0;
  while (!quit2){

  if (SDLNet_TCP_Recv(csd, buffer, 512) > 0){


	switch(buffer[0]){


	  case 0x01: 			// NEW PLAYER
		New_client(&player[players]);
			break;
	  case 0x10: 	


	  case 0xFF: 	
		quit2 = 1;
		printf("Terminate connection\n");
	}
  			
 }
 }
 
/* Close the client socket */
  SDLNet_TCP_Close(csd);
 }
}
 
  SDLNet_TCP_Close(sd);
  SDLNet_Quit();

 return OK;
}





//==============================================================================
int New_client(T_player *p){
//==============================================================================

	fprintf(TTY, "S: New_client\n");
	if (SDLNet_TCP_Recv(csd, buffer, 512) > 0){
 
		printf("S: new nick: %s\n", buffer);
		//strncpy(p->nick, buffer, 32);
		bzero(buffer, BUFF_SIZE);

		p->score = 0;

		p->ship = SHIP_RED_RX;
  	}
 


 return OK;
}

//==============================================================================
int Free_client(T_player *p){
//==============================================================================

 return OK;
}

//==============================================================================
//==============================================================================
//==============================================================================
// 	COPY FROM CLIENT
//==============================================================================
int Inicializuj_objekty(){
//==============================================================================
	// Specifika vlastni lodi	
	// ====================
	SHIP_RED_RX.img = IMG_RED_RX;
	SHIP_RED_RX.img_m = IMG_RED_RX_move;
	SHIP_RED_RX.img_c = IMG_RED_RX_crap;
	SHIP_RED_RX.strana = RED;


	SHIP_BLUE_RX.img = IMG_BLUE_RX;
	SHIP_BLUE_RX.img_m = IMG_BLUE_RX_move;
	SHIP_BLUE_RX.img_c = IMG_BLUE_RX_crap;
	SHIP_BLUE_RX.strana = BLUE;

	lode[0] = SHIP_RED_RX;
	//lode[0] = SHIP_BLUE_RX;
	
	my_ship = &lode[0];	
	
	// Specifika cizi lodi
	// ====================
	lode[1] = SHIP_BLUE_RX;
	lode[1].speed = 0.1; // angle ve stupnich
	lode[1].angle = -125; // angle ve stupnich
	
	lode[1].X = 3450;
	lode[1].Y = 3450;
	
	pocet_lodi   = 1;
	pocet_laseru = 0;
	pocet_raket  = 0;

 return OK;
}

//==============================================================================
int Pohybuj_objekty(){
//==============================================================================
//
	//  === Pohyb lodi ===
	my_ship->angle += manevr;
	my_ship->speed += zrychleni;	
	
	X += my_ship->speed * cos(((float)my_ship->angle/180)*M_PI)
	       	+ my_ship->uhyb * cos(((float)(my_ship->angle+90)/180)*M_PI);

	Y -= my_ship->speed * sin(((float)my_ship->angle/180)*M_PI)
	       	+ my_ship->uhyb * sin(((float)(my_ship->angle+90)/180)*M_PI);	


	for (int i=1; i<=pocet_lodi; i++){
	  if(! lode[i].alive) continue;
	  lode[i].X += lode[i].speed * cos(((float)lode[i].angle/180)*M_PI);
	  lode[i].Y -= lode[i].speed  * sin(((float)lode[i].angle/180)*M_PI); 	
	}

	// === Pohyb projektilu(strel) ===
	//
	for (int i=0; i<=pocet_laseru; i++){
	  if(! lasers[i].alive) continue;
	  lasers[i].X += lasers[i].speed * cos(((float)lasers[i].angle/180)*M_PI);
	  lasers[i].Y -= lasers[i].speed  * sin(((float)lasers[i].angle/180)*M_PI); 	
	}
	
	for (int i=0; i<=pocet_raket; i++){
	  if(! rockets[i].alive) continue;
	  rockets[i].X += rockets[i].speed * cos(((float)rockets[i].angle/180)*M_PI);
	  rockets[i].Y -= rockets[i].speed * sin(((float)rockets[i].angle/180)*M_PI); 
	}
		

 return OK;
}


//==============================================================================
int Detekuj_kolize(){
//==============================================================================

  for(int x=1; x <= pocet_lodi; x++){		
  	if(! lode[x].alive) continue;

	for(int i=0; i <= pocet_raket; i++){
		if(!rockets[i].alive) continue;
		if(Collision_detect(&lode[x], &rockets[i])){
			// DISABLE PROJECTIL
			rockets[i].alive = 0;
			rockets[i].X = 0;
			rockets[i].Y = 0;
			rockets[i].speed = 0;
			// MAKE DAMAGE
			lode[x].poskozeni += rockets[i].damage;
			if(lode[x].poskozeni > lode[x].MAX_poskozeni){
				printf("# SHIP n.%3d DESTROYED\n",x);
				lode[x].speed= 0;
				lode[x].X = 0;
				lode[x].Y = 0;
				lode[x].alive = 0;
			}

		}
	}

	for(int i=0; i <= pocet_laseru; i++){
		if(!lasers[i].alive) continue;
		if(Collision_detect(&lode[x], &lasers[i])){
			// DISABLE PROJECTIL
			lasers[i].alive = 0;
			lasers[i].X = 0;
			lasers[i].Y = 0;
			lasers[i].speed = 0;
			// MAKE DAMAGE
			lode[x].poskozeni += lasers[i].damage;
			if(lode[x].poskozeni > lode[x].MAX_poskozeni){
				printf("# SHIP n.%3d DESTROYED\n",x);
				lode[x].speed= 0;
				//lode[x].X = 0;
				//lode[x].Y = 0;
				//lode[x].alive = 0;
			}
		}
	}
  } 

return OK;
}

//==============================================================================
int Collision_detect(T_ship *ship, T_weapon *weapon ){
//==============================================================================

  int c = (fabs(ship->X - weapon->X) < (ship->img->w  >> 1)) &&
  	  (fabs(ship->Y - weapon->Y) < (ship->img->h >> 1));

  //if(c)	printf("COLLISION: X: %d Y: %d\n",(int)(ship->X), (int)(ship->Y));

  return c;
}

