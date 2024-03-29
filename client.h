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


  char player_list[MAX_PLAYERS][80];

#define MAX_SERVERS 16
#define SERVER_ADDRESS_MAX 256

  char server_list[MAX_SERVERS][SERVER_ADDRESS_MAX];

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
int Turbo(int);

int Fire(int wp);

int Get_ship_states();
int Get_weapon_states();
int Get_object_states();

int Get_player_list();
int Request_player_list();

//==============================================================================
int	Connect2server(const char *hostname);
int Load_server_list();

#endif
