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

int Speed_up(int);
int Slow_down(int);
int Rotate_R(int);
int Rotate_L(int);
int Shift_R(int);
int Shift_L(int);

int Fire(int wp);

int Get_ship_state();
int Get_ship_states();



#endif
