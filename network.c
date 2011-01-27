

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

  int RC = !OK;
  int count = 0;
  while(RC != OK){
    count++;
    fprintf(D_OUT, "Connecting ... try [%1d]\n", count);
    if(count > 3){
		  ERROR("SERVER IS NOT RESPONDING");
      return FAIL;
    }
    RC = New_client();		// TELL "hello server"
  }

  DEBUG("---==:: CONNECTED ::==---");
  return OK;	
}


//==============================================================================
int Load_server_list(){
//==============================================================================

  strncpy(server_list[0], "undergroundlab.cz", 255);

  
  #define SERVER_LIST_FILE "SERVER_LIST"
  FILE *file;
  char buffer[SERVER_ADDRESS_MAX];

  file = fopen(SERVER_LIST_FILE, "r");

  int i = 1;
  while(i < MAX_SERVERS){

      if(fgets( buffer, SERVER_ADDRESS_MAX, file) == NULL) break;
      buffer[strlen(buffer)-1] = '\0';
      strncpy(server_list[i], buffer, 255);

      DEBUG("reading server address")
      i++;
  }
  strncpy(server_list[i], "127.0.0.1", 255);
  fclose(file);
  return OK;
}
//==============================================================================
