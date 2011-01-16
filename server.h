#ifndef SERVER_H 
 #define SERVER_H 

#include "objects.h"
//==============================================================================
#define PORT  		7111
#define BUFF_SIZE 128	

#define MAX_PLAYERS 4 


#define TTY stdout
#define SEED 1

//==============================================================================
// GLOBAL variables
//==============================================================================
typedef struct str_player{
	IPaddress  ip;	
	char nick[32];
	Sint16 score;
	
	T_object ship;
  //	TCPsocket sd;	
  //  UDPsocket usd;
	Uint8 channel;
	Uint8 alive;

	Uint8 faction;

} T_player;

  int players;	// count of
  int live_players;	// count of

  T_player player[MAX_PLAYERS+1];


//==============================================================================
#endif
