//==============================================================================
// DARK MIR server
//==============================================================================
//
// author:  Alexej.x [at] mail.ru
// license: GNU GPL-2
//
//==============================================================================

#include <math.h>

#include "program.h"
#include "vesmir.h"
#include "server.h"
#include "lod.h"
//#include "ships.h"
#include "zbrane.h"
//#include "weapons.h"

#include "protokol.h"
#include "objects.h"
#include "faction.h"


  float f;
  double D;
  int I;

//==============================================================================
// Global variables
//==============================================================================

  TCPsocket ssd;	// server listening socket
  TCPsocket sd; 	// server - client socket
  IPaddress ip, *remoteIP;

  UDPsocket ussd;	// server listening socket
  UDPsocket usd;	// client socket
  UDPpacket *t;		// transmit
  UDPpacket *r;		// recieve


  SDL_TimerID mv_timer = NULL;

  int players = 0;	// count of
  int live_players = 0;	// count of
  //unsigned char r->data[BUFF_SIZE];
  //unsigned char t->data[BUFF_SIZE];
  unsigned char *tp;		// r->data pointer
  int len=0;
  int p_id = 0;

//==============================================================================
// Function prototypes
//==============================================================================
int Init();
int Init_server();
int Server();
int New_client(T_player *p);
int Free_client(int id);


//==============================================================================
int Speed_up	(int id, int X);
int Slow_down	(int id, int X);
int Rotate_R	(int id, int X);
int Rotate_L	(int id, int X);
int Shift_R		(int id, int X);
int Shift_L		(int id, int X);
int Turbo		(int id, int X);

int Fire(int id, int wp);

int Send_ship_states();
int Send_weapon_states();
int Send_object_states();
int Send_player_list();

Uint32 Timed_loop(Uint32 interval, void *param);

int Pohybuj_objekty();
int Detekuj_kolize();
 static inline int Collision_detect(T_object *ship, T_object *weapon );
 static inline int Collision_detect_ships(T_object *ship1, T_object *ship2 );
int Time_to_live(T_object *weapon );

// ==============================================================================
// ==============================================================================
int main(int argc, char **argv){
// ==============================================================================

  Init();	
  Init_server();
  Initialize_objects(0);

  Server();

 return EXIT_SUCCESS;
}

// ==============================================================================
int Init(){
// ==============================================================================
	
	srand(SEED);

	if (SDL_Init(SDL_SERVER_SUBSYSTEMS)==-1){
		fprintf(stderr, "ERROR:  SDL subsystems init: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

  return OK;	
}

// ==============================================================================
int Init_server(){
// ==============================================================================
  
  if (SDLNet_Init() == FAIL){
	fprintf(stderr, "ERROR: SDLNet_Init: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }

// ---- TCP ----
/*
 
  // Resolving the host using NULL make network interface to listen
  if (SDLNet_ResolveHost(&ip, NULL, PORT) == FAIL){
	fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
 
  // Open a connection with the IP provided (listen on the host's port) 
  if (!(ssd = SDLNet_TCP_Open(&ip))){
	fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
*/

// ---- UDP ----

  usd = SDLNet_UDP_Open(PORT);

  if(usd == NULL) {
	fprintf(stderr, "ERROR: SDLNet_UDP_Open: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }

  if (!(r = SDLNet_AllocPacket(BUFF_SIZE))) {
	fprintf(stderr, "ERROR: SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }
  if (!(t = SDLNet_AllocPacket(BUFF_SIZE))) {
	fprintf(stderr, "ERROR: SDLNet_AllocPacket: %s\n", SDLNet_GetError());
	exit(EXIT_FAILURE);
  }

  fprintf(TTY, "------------===[ DARK MIR ]===------------\n");
  fprintf(TTY, "> server listen on UDP port %d\n", PORT);

 return OK;
}


//==============================================================================
int Server(){
//==============================================================================

  int quit=0;

  mv_timer = SDL_AddTimer(SERVER_TIME_INTERVAL, Timed_loop, NULL);  // MOVE
			


while (1){

	SDL_Delay(10);		// free CPU

/*
if (SDLNet_UDP_Recv(ussd, p)) {
	printf("UDP Packet incoming\n");
	printf("\tChan:    %d\n", p->channel);
	printf("\tData:    %s\n", (char *)p->data);
	printf("\tLen:     %d\n", p->len);
	printf("\tMaxlen:  %d\n", p->maxlen);
	printf("\tStatus:  %d\n", p->status);
	printf("\tAddress: %x %x\n", p->address.host, p->address.port);

*/	
 
 // ===== ---- ===== ---- ===== ---- ===== ---- ===== 

  quit = 0;
  while (!quit){

	UDP_RECV{
//		*remoteIP = (r->address);
		printf("0x%2X \n", r->data[0]);

		for(p_id = 0; p_id < players; p_id++){		// player identification
			if(player[p_id].channel == r->channel){
			//	POINT(p_id);
				break;	
			}
		}

	}else continue;



	switch(r->data[0]){

	  	case P_NEW_PLAYER: 			// NEW PLAYER
			New_client(&player[players]);
			break;
	  
	  	case P_ROTATE_R:	 	
			Rotate_R(p_id, START);
			break;
	  	case P_STOP_ROTATE_R: 	
			Rotate_R(p_id, STOP);
			break;

	  	case P_ROTATE_L: 	
			Rotate_L(p_id, START);
			break;
	  	case P_STOP_ROTATE_L: 	
			Rotate_L(p_id, STOP);
			break;


		case P_SPEED_UP:  
			Speed_up(p_id, START);
			break;
		case P_STOP_SPEED_UP:  
			Speed_up(p_id, STOP);
			break;

		case P_SLOW_DOWN: 
			Slow_down(p_id, START);
			break;
		case P_STOP_SLOW_DOWN: 
			Slow_down(p_id, STOP);
			break;

		case P_SHIFT_R:
			Shift_R(p_id, START);
			break;
		case P_STOP_SHIFT_R:
			Shift_R(p_id, STOP);
			break;

		case P_SHIFT_L: 
			Shift_L(p_id, START);
			break;
		case P_STOP_SHIFT_L: 
			Shift_L(p_id, STOP);
			break;
			
		case P_TURBO: 
			Turbo(p_id, START);
			break;
		case P_STOP_TURBO: 
			Turbo(p_id, STOP);
			break;

		case P_FIRE_0:   
		case P_FIRE_1:   
		case P_FIRE_2:    
		case P_FIRE_3:     
		case P_FIRE_4:     
		case P_FIRE_5:     
		case P_FIRE_6:     
		case P_FIRE_7:     
		case P_FIRE_8:     
		case P_FIRE_9:     
		case P_FIRE_A:     
		case P_FIRE_B:     
		
      // HERE should be some control if the weapon is equiped	
			Fire(p_id, r->data[0] - P_FIRE_0);
			break;

		case P_PLAYER_LIST:
			Send_player_list(p_id);
			break;

	  	case P_LOGOUT: 	
			Free_client(p_id);
	//		quit = 1;
			break;

	  default:  fprintf(TTY, "invalid packet OP code\n");

	}
  			
  } 
/* Close the client socket */
  //SDLNet_TCP_Close(sd);
  SDLNet_FreePacket(t);
  SDLNet_FreePacket(r);
  SDLNet_UDP_Close(usd);
 
}
 

  //SDLNet_TCP_Close(ssd);
  //SDLNet_UDP_Close(ussd);		// server listening socket

  SDL_RemoveTimer(mv_timer);
  SDLNet_Quit();

 return OK;
}

//==============================================================================
Uint32 Timed_loop(Uint32 interval, void *param){
//==============================================================================

	Pohybuj_objekty();

	Detekuj_kolize();


	return interval;
}
//==============================================================================
//==============================================================================
int New_client(T_player *p){
//==============================================================================
  int id=0;
  p = NULL;

  // Prepare new packet
  memset(t->data, 0xFF ,BUFF_SIZE);

  t->address = r->address;
  t->len = BUFF_SIZE;
  tp = t->data;

	if(live_players >= MAX_PLAYERS){
		*tp = P_LOGOUT;				// server is full
		UDP_CHANNEL_SEND(-1);
		fprintf(TTY, "S: attempt to connect: servers is full \n");
		return FAIL;
	}
	else{
		*tp = P_NEW_PLAYER;			// player joined
		tp++;

		for(id=0; id < players; id++){  // find first not .alive player
			if(! player[id].alive){       // and use his slot 
					p = &player[id];
					break;
			}
		}	
		if( p == NULL){
			p = &player[players];
			players++;
		}
		*tp = id;	 			// player ID
		live_players++;

	fprintf(TTY, "S: New_client id:%2d: connected\n", id);
	fprintf(TTY, "S: new nick: %s\n", &r->data[2]);

		p->channel = SDLNet_UDP_Bind(usd, id, &r->address);
		p->alive = 1;
		p->score = 0;
    p->faction = ((Uint8*)(r->data))[1];
		strncpy(p->nick, ((char *)r->data)+2, 32);

    extern T_object SHIP_RED_RX;
    extern T_object SHIP_BLUE_RX;
    extern T_object SHIP_GREEN_ZX;

  if(p->faction == RED)
  	  p->ship = SHIP_RED_RX;
	else 
    if(p->faction == BLUE)
			p->ship = SHIP_BLUE_RX;
    else 
			p->ship = SHIP_GREEN_ZX;

		p->ship.X = (MAX_X/2); 
		p->ship.Y = (MAX_Y/2); 
		p->ship.health	= p->ship.MAX_health;
		p->ship.speed 	= 0.0;
		p->ship.angle 	= 0;
		p->ship.manevr	= 0;
		p->ship.shift 	= 0;
		p->ship.wp_1 	= p->ship.MAX_wp_1;
		//printf("WP1: %d\n", player[i].ship.wp_1);
		p->ship.wp_2 	= p->ship.MAX_wp_2;
		p->ship.wp_3 	= p->ship.MAX_wp_3;
		p->ship.acceleration	= 0;
		p->ship.alive	= 1;
		p->ship.destroyed	= 0;

    tp++;
		*tp = p->faction;	 			// player ID
	}
	UDP_CHANNEL_SEND(p->channel);
	
 return OK;
}

//==============================================================================
int Free_client(int id){
//==============================================================================

	fprintf(TTY, "S: Client id:%2d: disconnected\n", id);

	player[id].alive = 0;
	live_players--;
/*
	// DELETE PLAYER - shift player[] array
	for(int i=id; i < players-1; i++){
		player[i] = player[i+1];
		POINT(i);
	}

	players--;
*/
 return OK;
}

//==============================================================================
int Speed_up(int id, int X){
//==============================================================================
	
  //player[id].ship.speed += player[id].ship.acceleration;	
  if( X == STOP)
  	player[id].ship.acceleration = 0;
  else
  	player[id].ship.acceleration = + player[id].ship.MAX_acceleration;	
  

 // printf("acceleration: %f\n", (double) player[id].ship.acceleration);


  /*tp = t->data;
  *tp =  P_SPEED_UP;
  tp++;
  memcpy(tp, &player[id].ship.speed, sizeof(float));

*/
 return OK;
}
//==============================================================================
int Slow_down(int id, int X){
//==============================================================================
	
  if( X == STOP)
  	player[id].ship.acceleration = 0;
  else		  
  	player[id].ship.acceleration = - player[id].ship.MAX_acceleration;	
/*
  tp = t->data;
  *tp =  P_SLOW_DOWN;
  tp++;
  memcpy(tp, &player[id].ship.speed, sizeof(float));

*/
 return OK;
}

//==============================================================================
int Rotate_R(int id, int X){
//==============================================================================

  if(X == STOP)		
  	player[id].ship.manevr = 0;
  else	
  	player[id].ship.manevr = - player[id].ship.MAX_manevr;	

/*
  tp = t->data;
  *tp =  P_ROTATE_R;
  tp++;
  memcpy(tp, &player[id].ship.angle, sizeof(float));

*/
 return OK;
}
//==============================================================================
int Rotate_L(int id, int X){
//==============================================================================
	

  if(X == STOP)		
  	player[id].ship.manevr = 0;
  else	
  	player[id].ship.manevr = + player[id].ship.MAX_manevr;	
/*
  tp = t->data;
  *tp =  P_ROTATE_L;
  tp++;
  memcpy(tp, &player[id].ship.angle, sizeof(float));

*/
 return OK;
}
//==============================================================================
int Shift_R(int id, int X){
//==============================================================================
	
  if(X == STOP)		
  	player[id].ship.shift = 0;
  else
  	player[id].ship.shift = - player[id].ship.MAX_shift;
/*
  tp = t->data;
  *tp =  P_SHIFT_R;
  tp++;
  memcpy(tp, &player[id].ship.shift, sizeof(float));

*/
 return OK;
}
//==============================================================================
int Shift_L(int id, int X){
//==============================================================================
	
  if(X == STOP)		
  	player[id].ship.shift = 0;
  else
  	player[id].ship.shift = + player[id].ship.MAX_shift;
/*
  tp = t->data;
  *tp =  P_SHIFT_L;
  tp++;
  memcpy(tp, &player[id].ship.shift, sizeof(float));

*/
 return OK;
}

//==============================================================================
int Turbo(int id, int X){
//==============================================================================
	
  if(X == STOP)		
  	player[id].ship.turbo = 0;
  else
  	player[id].ship.turbo = 1;
/*
  tp = t->data;
  *tp =  P_SHIFT_L;
  tp++;
  memcpy(tp, &player[id].ship.shift, sizeof(float));

*/
 return OK;
}

//==============================================================================

//==============================================================================
int Fire(int id, int wp){
//==============================================================================
  int i;

  int x= 		player[id].ship.X ;
  int y= 		player[id].ship.Y ;
  double angle = ((player[id].ship.angle + 90) * M_PI / 180  );
  int dx= 		cos(angle) * 25;
  int dy= 		sin(angle) * 25;

	for( i= WP; i < MAX_OBJECTS; i++){		// find first not .alive weapon
			if(! object[i].alive) break;      // and use this slot 
	}	
	if(i >= MAX_OBJECTS - 1)					    // no not .alive slote
			return FAIL;
	

	switch(wp){
	
		// === PRIMARY WEAPONS ===	
		case LASER:
			//printf("TEST: WP1: %d\n", player[id].ship.wp_1);
			if(	player[id].ship.wp_1 <= 0)
				return FAIL;

			player[id].ship.wp_1 -= 1;
      i = Create_object(WEAPON, LASER, 0, x, y);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
			break;

		case ENERGY_LASER:
			if(	player[id].ship.wp_1 <= 0)
				return FAIL;

			player[id].ship.wp_1 -= 1;
      i = Create_object(WEAPON, ENERGY_LASER, 0, x, y);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
			//object[i] = ZX_Q1;
			break;
/*
		// === SECONDARY WEAPONS ===	
		case ROCKET:
			if(	player[id].ship.wp_2 <= 0)
				return FAIL;

			player[id].ship.wp_2--;
			object[i] = RX_R1;
			break;
*/
		case MICRO_MISSILE:
			if(	player[id].ship.wp_2 <= 0)
				return FAIL;

			player[id].ship.wp_2 -= 1;
      i = Create_object(WEAPON, MICRO_MISSILE, 0, x, y);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
			
			break;

		case GUIDED_MISSILE:
			if(	player[id].ship.wp_3 <= 0)
				return FAIL;

			player[id].ship.wp_3 -= 1;

      i = Create_object(WEAPON, GUIDED_MISSILE, 0, x, y);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
			break;

		case ROCKET:
		case MULTI_MISSILE:
			if(	player[id].ship.wp_2 <= 0)
				return FAIL;

			player[id].ship.wp_2 -= 1;
      // WRITE IT
      printf("player angle + 90: %G\n", player[id].ship.angle + 90);
      while(angle > 2 * M_PI) angle -= 2 * M_PI;
      while(angle < 0) angle += 2 * M_PI;
   

      /*
      if((angle >      0)&&(angle < M_PI/2   )){ dx = - dx; dy = + dy; }
      if((angle > M_PI/2)&&(angle < M_PI     )){ dx = - dx; dy = + dy; }
      if((angle > M_PI  )&&(angle < M_PI*3/2 )){ dx = - dx; dy = + dy; }
      if((angle > M_PI*3/2  )&&(angle < M_PI*4/2 )){ dx = - dx; dy = + dy; }
      */
       dx = - dx; dy = + dy; 

      i = Create_object(WEAPON, ROCKET, 0, x + dx, y + dy);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
      i = Create_object(WEAPON, ROCKET, 0, x - dx, y - dy);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;

      printf("angle: %3.2F   x: %4d y: %4d  dx: %2d dy %2d\n",
              angle * 180/M_PI,  x, y, dx, dy);

      return OK;
    // ----------------------------------------
		case MISSILE_BURST:
			if(	player[id].ship.wp_2 <= 0)
				return FAIL;

			player[id].ship.wp_2 -= 1;
      // WRITE IT
      printf("player angle + 90: %G\n", player[id].ship.angle + 90);
      while(angle > 2 * M_PI) angle -= 2 * M_PI;
      while(angle < 0) angle += 2 * M_PI;
   

      /*
      if((angle >      0)&&(angle < M_PI/2   )){ dx = - dx; dy = + dy; }
      if((angle > M_PI/2)&&(angle < M_PI     )){ dx = - dx; dy = + dy; }
      if((angle > M_PI  )&&(angle < M_PI*3/2 )){ dx = - dx; dy = + dy; }
      if((angle > M_PI*3/2  )&&(angle < M_PI*4/2 )){ dx = - dx; dy = + dy; }
      */
       dx = - dx; dy = + dy; 

      i = Create_object(WEAPON, MICRO_MISSILE, 0, x + dx, y + dy);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
      i = Create_object(WEAPON, MICRO_MISSILE, 0, x + dx/2, y + dy/2);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
      i = Create_object(WEAPON, MICRO_MISSILE, 0, x - dx/2, y - dy/2);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;
      i = Create_object(WEAPON, MICRO_MISSILE, 0, x - dx, y - dy);
	    object[i].angle = 	player[id].ship.angle;
	    object[i].faction = player[id].faction;

      printf("angle: %3.2F   x: %4d y: %4d  dx: %2d dy %2d\n",
              angle * 180/M_PI,  x, y, dx, dy);

      return OK;
			break;

	}
	object[i].angle = 	player[id].ship.angle;
	object[i].X = 		player[id].ship.X;
	object[i].Y = 		player[id].ship.Y;
	object[i].faction = 	player[id].ship.faction;
	object[i].alive =     	1;
	object[i].destroyed = 	0;

 return OK;
}

//==============================================================================
int Send_ship_states(){
//==============================================================================
// WARNING possible resending incorect one incorrect paket every running this function
  Uint8 *tp = t->data;

  // New packet
	  tp = t->data;
	  memset(t->data, 0xFF ,BUFF_SIZE);
  	*tp = P_SHIP_STATES;											// OP CODE
  	tp++;
	  *tp = PACKET_NUMBER++;										// PACKET_NUMBER
	  tp++;


  // ------------------------------------------------------------
  for(Uint8 i=0; i < players; i++){		

    // FULL PACKET -> SEND IT
    if(tp - t->data >= BUFF_SIZE-1) {	
      for(Uint8 x = 0; x < players; x++){
        if(player[x].alive){
          UDP_CHANNEL_SEND(player[x].channel);
        //fprintf(TTY, "> player: %d channel: %d\n", x, player[x].channel);
        }
  	  }
	  tp = t->data;
	  memset(t->data, 0xFF ,BUFF_SIZE);
  	*tp = P_SHIP_STATES;											// OP CODE
  	tp++;
	  *tp = PACKET_NUMBER++;										// PACKET_NUMBER
	  tp++;
	 }

	*tp = i;                                       // ID
	tp++;
	*tp = SHIP;                                    // TYPE
	tp++;

	*((Sint32 *)tp) = player[i].ship.X;             // X
	//fprintf(TTY,"<< X: %4d\n", *((Sint32 *)tp));	
	tp += sizeof(Sint32);
	*((Sint32 *)tp) = player[i].ship.Y;             // Y
	tp += sizeof(Sint32);
	*((float *)tp) = player[i].ship.speed;          // SPEED
	tp += sizeof(float);
	*((float *)tp) = player[i].ship.angle;          // ANGLE
	tp += sizeof(float);
	*((int *)tp) = player[i].ship.health;           // DAMAGE
	tp += sizeof(int);
	*((int *)tp) = player[i].ship.faction;          // FACTION
	tp += sizeof(int);

  }

  // ------------------------------------------------------------
  // SEND REST OF DATA
  for(int x = 0; x < players; x++){
    if(player[x].alive){
      UDP_CHANNEL_SEND(player[x].channel);
      //fprintf(TTY, "> player: %d channel: %d\n", x, player[x].channel);
    }
  }
	
   	memset(t->data, 0xFF ,BUFF_SIZE);
	return OK;
}
//==============================================================================

// WARNING nektera zasilaci funkce zpusobuje nove vyslani naposledy vyslaneho paketu
//==============================================================================
int Send_object_states(){
//==============================================================================

  Uint8 *tp = NULL;

      // Prepare new packet
      tp = t->data;
      memset(t->data, 0xFF ,BUFF_SIZE);
      *tp = P_OBJECT_STATES;										// OP CODE
      tp++;


// HERE POSSIBLE PROBLEM !!!
  for(int a = 32; a < MAX_OBJECTS; a++){
    if(! object[a].alive)	continue;  

    // Send information: Object was destroyed
	  if(object[a].destroyed){
      object[a].alive = 0;
		  object[a].X = 0;								
		  object[a].Y = 0;							
    }


    // --- fill packet with informations ---
		*(Uint32 *)tp = (Uint32) a;             // ID
		tp += sizeof(Uint32);

		*tp = object[a].descriptor;						  // DESCRIPTOR
		tp++;
		*tp = object[a].type;										// TYPE
		tp++;
		*tp = object[a].model;								  // TYPE model
		tp++;
		*tp = object[a].faction;							  // FACTION
		tp++;

		*((Uint32 *)tp) = object[a].X;					// X
		tp += sizeof(Uint32);
		*((Uint32 *)tp) = object[a].Y;					// Y
		tp += sizeof(Uint32);
		*((float *)tp) = object[a].angle;				// ANGLE
		tp += sizeof(float);

    // Packet is full -> send it
  	if(tp - t->data + 5 * sizeof(Uint32) >= BUFF_SIZE-1) {	

	    for(int x = 0; x < players; x++){
	      if(! player[x].alive) continue;
		    UDP_CHANNEL_SEND(player[x].channel);
		    //fprintf(TTY, "> player: %d channel: %d\n", x, player[x].channel);
      }

      // Prepare new packet
      tp = t->data;
      memset(t->data, 0xFF ,BUFF_SIZE);
      *tp = P_OBJECT_STATES;										// OP CODE
      tp++;
	 }
  }
  
	// send the rest of it	
  for(int x = 0; x < players; x++){
    if(! player[x].alive) continue;
    UDP_CHANNEL_SEND(player[x].channel);
    //fprintf(TTY, "> player: %d channel: %d\n", x, player[x].channel);
  }

  memset(t->data, 0xFF ,BUFF_SIZE);
	return OK;
}


//==============================================================================
int Send_player_list(){
//==============================================================================	
Uint8 *tp; 

  for(int id = 0; id < players; id++){
	    if(! player[id].alive) continue;

		printf(">list %d\n", id);
     	tp = t->data;
    	memset(t->data, 0xFF ,BUFF_SIZE);

    	*tp = P_PLAYER_LIST;					// OP_code
    	tp++;	

		*(tp) = id;							// ID
		tp++;	
		 *(tp) = player[id].ship.type;				// TYPE
		tp++;	
		*((Sint16 *)tp) = player[id].score;			// SCORE 
		printf("PLAYER: %d  SCORE: %d\n",id, player[id].score);
		tp++;
		tp++;
		strncpy((char *)tp, player[id].nick,  NICKNAME_MAX-1);	// NICK
		tp += NICKNAME_MAX;

  	
  	for(int x = 0; x < players; x++){
	    if(! player[x].alive) continue;
		UDP_CHANNEL_SEND(player[x].channel);
		fprintf(TTY, "> player_list: player: %d channel: %d\n", x, player[x].channel);
    }
  }
 
   	memset(t->data, 0xFF ,BUFF_SIZE);
	return OK;
}

//==============================================================================
//==============================================================================
//=============================================================================
//
//==============================================================================
//==============================================================================
//==============================================================================
int Pohybuj_objekty(){
//==============================================================================

  float x,y,v;
  float distance = 99999;
  float min_distance = 99999;

  for(int i=0; i < players; i++){

	//  === Zdravi lodi ===
 	if(player[i].ship.health < 0)
		  player[i].ship.health = 0;

	//  === Pohyb lodi ===
	if(! player[i].alive) continue;
	if(! player[i].ship.alive) continue;

	player[i].ship.angle += player[i].ship.manevr;
	//printf("angle: %f\n", (double) player[i].ship.angle);

	player[i].ship.speed += player[i].ship.acceleration + 
			2 * player[i].ship.turbo * player[i].ship.acceleration ;
	
	// ==== speed limit ====
 	if(player[i].ship.speed < 0)
		  player[i].ship.speed = 0;

	if(player[i].ship.speed > 
    (player[i].ship.MAX_speed + player[i].ship.turbo * player[i].ship.MAX_speed) ){

		player[i].ship.speed =  
      player[i].ship.MAX_speed + player[i].ship.turbo * player[i].ship.MAX_speed ;
			//player[i].ship.acceleration = 0;

	}


		
	// ==== angle limit ====
  if(player[i].ship.angle > 360)
    player[i].ship.angle -= 360;
  if(player[i].ship.angle < 0)
    player[i].ship.angle += 360;

	// ==== position change ====
	player[i].ship.X += round(
    player[i].ship.speed * cos(((float)player[i].ship.angle/180)*M_PI)
	  + player[i].ship.shift * cos(((float)(player[i].ship.angle+90)/180)*M_PI));
   
	player[i].ship.Y -= round(
    player[i].ship.speed * sin(((float)player[i].ship.angle/180)*M_PI)
		+ player[i].ship.shift * sin(((float)(player[i].ship.angle+90)/180)*M_PI));	


  if( player[i].ship.shift > 0)
	  player[i].ship.shift -= 0.10;
  if( player[i].ship.shift < 0)
	  player[i].ship.shift += 0.10;
  

	// ==== position limits ====
	// RIGHT  DOWN 
	if(player[i].ship.X > MAX_X) 
			player[i].ship.X = MAX_X;
	if(player[i].ship.Y > MAX_Y) 
			player[i].ship.Y = MAX_Y;

	// LEFT  UP
  if(player[i].ship.X < 0) 
    player[i].ship.X = 0;
  if(player[i].ship.Y < 0) 
    player[i].ship.Y = 0;

  }
	Send_ship_states();

	// === PROJECTILS (WEAPONS) movement ===
	
  for (int i= WP; i < MAX_OBJECTS; i++){
	int n = 0;

	  if(! object[i].alive) continue;

	  Time_to_live(&object[i]);

    // === Guided missile ===
	  if(object[i].type == GUIDED_MISSILE){

		// Find the nearest enemy ship
    for(int j = 0; j < players; j++){
      if(! player[j].alive) continue;
      if(player[j].ship.faction == object[i].faction) continue;

			x = player[j].ship.X - object[i].X;
			y = player[j].ship.Y - object[i].Y;

			//distance = (x * x) + (y * y);
			distance = sqrt((x * x) + (y * y));
		
			if(distance < min_distance){
				n = j;
				min_distance = distance;
			}			
    } // for
		
		// Set angle 
		// WARINING kvadranty a znamenka
    #define G_RANGE 3000
		if(distance > 100 && distance < G_RANGE){
			x = player[n].ship.X - object[i].X;
			y = player[n].ship.Y - object[i].Y;

			//x = object[i].X - player[n].ship.X;
			//y = object[i].Y - player[n].ship.Y;
			v = y / x;


			if(y > 0){
				if(x > 0){	// I (4)
					object[i].angle =  360 - (180/M_PI) * atan(v);
					//printf("x: %5f y: %5f ALFA: %f\n",x, y, (double) object[i].angle);
				}
				else{		// II (3)
					object[i].angle = 180 - (180/M_PI) * atan(v);
					//printf("x: %5f y: %5f ALFA: %f\n",x, y, (double) object[i].angle);
				}
			}
			else{
				if(x > 0){	// IV (1)
					object[i].angle = 360 - (180/M_PI) * atan(v);
					//printf("x: %5f y: %5f ALFA: %f\n",x, y, (double) object[i].angle);
				}
				else{		// III (2)
					object[i].angle = 180 - (180/M_PI) * atan(v);
					//printf("x: %5f y: %5f ALFA: %f\n",x, y, (double) object[i].angle);
				}
			}


//			v = v - trunc(v) * M_PI;
/*
			if((v > M_PI_2) && ( v < M_PI))
				weapon[i].angle = 270 + (180/M_PI) * atan(v);
			if((v < 0) && ( v > - M_PI_2))
				weapon[i].angle = -1 *  (180/M_PI) * atan(v);

			if((v > 0) && ( v < M_PI_2))
				weapon[i].angle =   (180/M_PI) * atan(v);
			else
				weapon[i].angle =    (180/M_PI) * atan(v);
*/				
		 }
	  }

	  object[i].X += object[i].speed * cos(((float)object[i].angle/180)*M_PI);
	  object[i].Y -= object[i].speed  * sin(((float)object[i].angle/180)*M_PI); 	

	   // ==== position limits ====
	  // RIGHT  DOWN 
	  if(object[i].X > MAX_X) 
			object[i].destroyed = 1;
	  if(object[i].Y > MAX_Y) 
			object[i].destroyed = 1;

	  // LEFT  UP
	  if(object[i].X < 0) 
			object[i].destroyed = 1;
	  if(object[i].Y < 0) 
			object[i].destroyed = 1;

  }
	//Send_weapon_states();
	Send_object_states();

 return OK;
}


//==============================================================================
//==============================================================================
int Detekuj_kolize(){
//==============================================================================

  int diff;  
  int new;

  // ------------------------------------------------------------
  // Object vs Object
  // ------------------------------------------------------------
	for(int i=WP; i < MAX_OBJECTS; i++){
    if(! object[i].alive) continue;

	  for(int z=NT; z < MAX_OBJECTS; z++){
      if(! object[z].alive) continue;
      if( object[i].destroyed) break;
      if( object[z].destroyed) continue;
 
     
      if(Collision_detect(&object[i], &object[z])){ 
   
        object[i].health -= object[z].damage; 
        object[z].health -= object[i].damage; 
        

        if(object[i].health < 0){
          //new = Create_object (NATURE, EXPLOSION, object[i].faction, object[i].X, object[i].Y); 
          object[i].destroyed = 1;
        }  
        if(object[z].health < 0){
          //new = Create_object(NATURE, EXPLOSION, object[z].faction, object[z].X, object[z].Y); 
          object[z].destroyed = 1;
        }
      }

    }
  };
  // ------------------------------------------------------------
  // Player vs object
  // ------------------------------------------------------------
  for(int x=0; x < players; x++){		
  	if(! player[x].ship.alive) continue;

    for(int y=0; y < players; y++){		
      // ------------------------------------------------------------
      // Ship vs Ship
      // ------------------------------------------------------------
		  if((x != y) && (Collision_detect_ships(&player[x].ship, &player[y].ship))){
        diff = player[x].ship.health - player[y].ship.health;

        // Small ships -> both destroyed
        player[x].ship.health = 0;
        player[y].ship.health = 0;
     

      }
    }


	  for(int i=0; i < MAX_OBJECTS; i++){
		  if(!object[i].alive) continue;
  		if(object[i].type == EXPLOSION) continue;		// ignore

  		if(object[i].faction == player[x].ship.faction) continue;


    // Waapon vs Ship
		if(Collision_detect(&player[x].ship, &object[i])){
		//POINT(99);
			// MAKE DAMAGE
			player[x].ship.health -= object[i].damage;
			// DISABLE PROJECTIL and CREATE EXPLOSION
			object[i].alive = 1;
			object[i].speed = 0;
			object[i].damage= 0;
			object[i].ttl = EXPLOSION_TTL;
			object[i].type = EXPLOSION;
			// sending until server quits, so TODO

  		// WINNING TEAM BONUS

	    if(player[x].ship.health <= 0){
	  	  for(int z=0; z < players; z++){
		  	  if(object[i].faction == player[z].ship.faction){
			      player[z].score += 1;
  				  player[z].ship.wp_1 =  player[z].ship.MAX_wp_1;
  				  player[z].ship.wp_2 =  player[z].ship.MAX_wp_2;
  				  player[z].ship.wp_3 =  player[z].ship.MAX_wp_3;

			    }
        }

		  }
    }

  }		
	

	if(player[x].ship.health <= 0){
				printf("# SHIP n.%3d DESTROYED\n",x);
				//player[x].ship.speed= 0;
				player[x].ship.alive = 0;
				//player[x].score -= 1;
				


				Send_player_list();
				POINT(111);

				//Respawn(&player[x]);
				player[x].ship.X = (MAX_X/4) + rand() % (MAX_X/2);
				player[x].ship.Y = (MAX_Y/4) + rand() % (MAX_Y/2);
				player[x].ship.alive = 1;
				player[x].ship.health = player[x].ship.MAX_health;
				POINT(211);
				player[x].ship.wp_1 	= player[x].ship.MAX_wp_1;
				POINT(311);
				player[x].ship.wp_2 	= player[x].ship.MAX_wp_2;
				POINT(411);
				player[x].ship.wp_3 	= player[x].ship.MAX_wp_3;
				POINT(511);
				player[x].ship.speed = 0.1;
				POINT(611);
				printf("RESPAWN: %d \n",player[x].ship.wp_2);
				POINT(711);
			}

  } 

  return OK;
}

//==============================================================================
static inline int Collision_detect(T_object *ship, T_object *weapon ){
//==============================================================================


  int c = (fabs(ship->X - weapon->X) < (50  >> 1)) &&
  	  (fabs(ship->Y - weapon->Y) < (50 >> 1));

 /*
  int c = (fabs(ship->X - weapon->X) < (ship->img->w  >> 1)) &&
  	  (fabs(ship->Y - weapon->Y) < (ship->img->h >> 1));
 */
  //if(c)	printf("COLLISION: X: %d Y: %d\n",(int)(ship->X), (int)(ship->Y));

  return c && (ship != weapon);
}
//==============================================================================
static inline int Collision_detect_ships(T_object *ship1, T_object *ship2 ){
//==============================================================================


  int c = (fabs(ship1->X - ship2->X) < (50  >> 1)) &&
  	  (fabs(ship1->Y - ship2->Y) < (50 >> 1));

 /*
  int c = (fabs(ship->X - weapon->X) < (ship->img->w  >> 1)) &&
  	  (fabs(ship->Y - weapon->Y) < (ship->img->h >> 1));
 */
  //if(c)	printf("COLLISION: X: %d Y: %d\n",(int)(ship->X), (int)(ship->Y));

  return c && (ship1 != ship2);
}

//==============================================================================
int Time_to_live(T_object *weapon ){
//==============================================================================
/*
  if (ship != NULL){
		  ship->ttl -= 1;
		  if(ship->ttl <= 0){
		  }
  }
*/

  if(weapon->type == SHIP) return OK;

  if (weapon != NULL){
		  weapon->ttl -= 1;

		  if(weapon->ttl <= 0){
			if(weapon->type == EXPLOSION){
				weapon->destroyed = 1;
				return OK;
			}

			weapon->alive 	= 1;
			weapon->speed  /= 4;
			weapon->damage	= 0;
			weapon->ttl 	= EXPLOSION_TTL;
			weapon->type = EXPLOSION;

		  }
  }
  else return FAIL;

  return OK;
}
//==============================================================================
// EOF
