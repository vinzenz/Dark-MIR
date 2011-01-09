

#include "program.h"
#include "client.h"


//==============================================================================
int	Connect2server(const char *hostname){
//==============================================================================
	// ==== SDL_NET_Init ====
	if (SDLNet_Init() == FAIL){
	  fprintf(stderr, "ERROR: SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	// Resolving the host 
  	if (SDLNet_ResolveHost(&ip, hostname, PORT) == FAIL){
		  fprintf(stderr, "ERROR: SDLNet_ResolveHost: %s\n", hostname);
		  fprintf(stderr, "ERROR: %s\n", SDLNet_GetError());
	    return FAIL;
    }


/*// === TCP ===   	
  // Open a connection with the IP provided ) 
  if (!(sd = SDLNet_TCP_Open(&ip))){
	fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
*/

  // === UDP ===   	
  if (!(usd = SDLNet_UDP_Open(0))) {
	  fprintf(stderr, "ERROR: SDLNet_UDP_Open: %s\n", SDLNet_GetError());
	  exit(EXIT_FAILURE);
  }


  // Allocate memory for the packet
  if (!(t = SDLNet_AllocPacket(512))) {
	  fprintf(stderr, "ERROR: SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	  exit(EXIT_FAILURE);
  }
  if (!(r = SDLNet_AllocPacket(512))) {
	  fprintf(stderr, "ERROR: SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	  exit(EXIT_FAILURE);
  }
 
  t->address.host = ip.host;	// Set the destination host 
  t->address.port = ip.port;	// And destination port 
  t->len = BUFF_SIZE;

	if(New_client() == OK){		// TELL "hello server"
		DEBUG("---==:: CONNECTED ::==---");
  }
	else{			
		ERROR("SERVER ERROR");
    return FAIL;
	}

    return OK;	
}
//==============================================================================
int Load_server_list(){
//==============================================================================

  strncpy(server_list[0], "undergroundlab.cz", 255);
  strncpy(server_list[1], "undergroundlab.cz", 255);
  strncpy(server_list[2], "127.0.0.1", 255);

  return OK;
}
//==============================================================================
