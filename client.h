#ifndef CLIENT_H
  #define CLIENT_H

#include "protokol.h"


// Global variables
//==============================================================================
//   TCPsocket ssd, sd; 	// Server Socket descriptor, Client socket descriptor
   UDPsocket usd;
   IPaddress ip, *remoteIP;

   UDPpacket *r;
   UDPpacket *t;

   char hostname[HOSTNAME_MAX];
   char nick[NICKNAME_MAX];



#endif
