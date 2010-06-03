#ifndef CLIENT_H
  #define CLIENT_H

#include "protokol.h"

#define PORT  		7111

// Global variables
//==============================================================================
   TCPsocket ssd, sd; 	/* Server Socket descriptor, Client socket descriptor */
   IPaddress ip, *remoteIP;

   char hostname[HOSTNAME_MAX];
   char nick[NICKNAME_MAX];

#endif
