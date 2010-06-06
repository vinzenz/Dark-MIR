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

   Uint8 ID;

// FUNCTIONS
// =============================================================================
int New_client();
int Logout();

int Speed_up();
int Slow_down();
int Rotate_R();
int Rotate_L();
int Shift_R();
int Shift_L();

int Fire(int wp);

int Get_ship_state();
int Get_ship_states();



#endif
