

#include "program.h"
#include "vesmir.h"
#include "server.h"
#include "lod.h"
#include "ships.h"
#include "zbrane.h"
#include "weapons.h"

#include "protokol.h"

#define TTY stdout
#define MAX_PLAYERS 2



typedef struct str_player{
	IPaddress  ip;	
	char nick[32];
	
	int score;
	T_ship ship;
//	TCPsocket sd;	
//  UDPsocket usd;
	Uint8 channel;
	Uint8 alive;

} T_player;


T_player player[MAX_PLAYERS+1];


float f;
double D;
int I;




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

int Fire(int id, int wp);

int Send_ship_state();
int Send_ship_states();

Uint32 Timed_loop(Uint32 interval, void *param);

int Inicializuj_objekty();
int Pohybuj_objekty();
int Detekuj_kolize();
 int Collision_detect(T_ship *ship, T_weapon *weapon );

// Global variables
 //==============================================================================
  SDL_TimerID mv_timer = NULL;

  TCPsocket ssd;	// server listening socket
  TCPsocket sd; 	// server - client socket
  IPaddress ip, *remoteIP;

  UDPsocket ussd;	// server listening socket
  UDPsocket usd;	// client socket
  UDPpacket *t;		// transmit
  UDPpacket *r;		// recieve

  int players = 0;	// count of
  int live_players = 0;	// count of
  //unsigned char r->data[BUFF_SIZE];
  //unsigned char t->data[BUFF_SIZE];
  unsigned char *tp;		// r->data pointer
  int len=0;
  int p_id = 0;
// ==============================================================================
// ==============================================================================
int main(int argc, char **argv){
// ==============================================================================

  Init();	
  Init_server();
  Inicializuj_objekty();

  Server();

 return EXIT_SUCCESS;
}

// ==============================================================================
int Init(){
// ==============================================================================

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


	SDL_Delay(1);		// free CPU

/*
if (SDLNet_UDP_Recv(ussd, p)) {
	printf("UDP Packet incoming\n");
	printf("\tChan:    %d\n", p->channel);
	printf("\tData:    %s\n", (char *)p->data);
	printf("\tLen:     %d\n", p->len);
	printf("\tMaxlen:  %d\n", p->maxlen);
	printf("\tStatus:  %d\n", p->status);
	printf("\tAddress: %x %x\n", p->address.host, p->address.port);

// Quit if packet contains "quit" 
if (strcmp((char *)p->data, "quit") == 0)
	quit = 1;

	//continue; // ------ ^
*/
		
 
 // ===== ---- ===== ---- ===== ---- ===== ---- ===== 

  quit = 0;
  while (!quit){

	UDP_RECV{
//		*remoteIP = (r->address);
		printf("0x%2X \n", r->data[0]);

		for(p_id = 0; p_id < players; p_id++){		// player identification
			if(player[p_id].channel == r->channel){
				POINT(p_id);
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
			
		case P_FIRE_0:   
		case P_FIRE_1:   
		case P_FIRE_2:    
		case P_FIRE_3:     
			
			player[p_id].ship.health -= 10;
			//Fire(p_id, r->data[0] - P_FIRE_0);
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

	//Detekuj_kolize();

	return interval;
}
//==============================================================================
//==============================================================================
int New_client(T_player *p){
//==============================================================================
  int id=0;
  p = NULL;


	// ACK
	t->address = r->address;
  	t->len = BUFF_SIZE;
	tp=t->data;

	if(live_players >= MAX_PLAYERS){
		*tp = P_LOGOUT;				// server is full
		UDP_CHANNEL_SEND(-1);
		fprintf(TTY, "S: attempt to connect: servers is full \n");
		return FAIL;
	}
	else{
		*tp = P_NEW_PLAYER;			// player joined
		tp++;						// 

		for(id=0; id < players; id++){	// find first not .alive player
			if(! player[id].alive){		// and use his slot 
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
	fprintf(TTY, "S: new nick: %s\n", &r->data[1]);

		p->channel = SDLNet_UDP_Bind(usd, id, &r->address);
		p->alive = 1;
		p->score = 0;
		strncpy(p->nick, (char *)r->data, 32);

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

  printf("acceleration: %f\n", (double) player[id].ship.acceleration);


  /*tp = t->data;
  *tp =  P_SPEED_UP;
  tp++;
  memcpy(tp, &player[id].ship.speed, sizeof(float));

  UDP_SEND;
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

  UDP_SEND;
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

  UDP_SEND;
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

  UDP_SEND;
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

//  UDP_SEND;
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

//  UDP_SEND;
*/
 return OK;
}

//==============================================================================

//==============================================================================
int Fire(int id, int wp){
//==============================================================================

	switch(wp){
		
		case LASER:
			if(pocet_laseru < MAX_LASER-1){
				pocet_laseru++;
				lasers[pocet_laseru] = RX_laser;
				lasers[pocet_laseru].angle = player[id].ship.angle;
				lasers[pocet_laseru].X = player[id].ship.X;;
				lasers[pocet_laseru].Y = player[id].ship.Y;;
				lasers[pocet_laseru].strana = player[id].ship.strana;
			}
			else{

			}	
			break;

		case ROCKET:
			
			if(pocet_raket < MAX_ROCKET-1){
				pocet_raket++;
				rockets[pocet_raket] = RX_R1;
				rockets[pocet_raket].angle = player[id].ship.angle;
				rockets[pocet_raket].X = player[id].ship.X;
				rockets[pocet_raket].Y = player[id].ship.Y;
				rockets[pocet_raket].strana = player[id].ship.strana;
			}
	}	

 return OK;
}

/*
//==============================================================================
int Send_ship_state(int i){
//==============================================================================
printf(">>> sending ship state <<<\n");
fflush(stdout);
	unsigned char *tp = t->data;
	*tp = P_STATE;
	tp++;	
	*( (float *)tp) = player[i].ship.X;
	//fprintf(TTY,"<< X: %4f\n", (double) *((float *)tp));
	tp += sizeof(float);
	*( (float *)tp) = player[i].ship.Y;
	tp += sizeof(float);
	*( (float *)tp) = player[i].ship.speed;
	tp += sizeof(float);
	*( (float *)tp) = player[i].ship.angle;

	UDP_SEND;
	
	return OK;
} 
*/
//==============================================================================
int Send_ship_states(){
//==============================================================================


  Uint8 *tp = t->data;

  memset(t->data, 0xFF ,BUFF_SIZE);
  *tp = P_SHIP_STATES;											// OP CODE
  tp++;

  for(int i=0; i < players; i++){		

	*tp = i;													// ID
	tp++;
	*tp = SHIP;													// TYPE
	tp++;

	*((float *)tp) = player[i].ship.X;							// X
//	fprintf(TTY,"<< X: %4f\n", (double) *((float *)tp));	
	tp += sizeof(float);
	*((float *)tp) = player[i].ship.Y;							// Y
	tp += sizeof(float);
	*((float *)tp) = player[i].ship.speed;						// SPEED
	tp += sizeof(float);
	*((float *)tp) = player[i].ship.angle;						// ANGLE
	tp += sizeof(float);
	*((int *)tp) = player[i].ship.health;						// DAMAGE
	tp += sizeof(int);

//printf("|| sending ship states ==__ \n");
fflush(stdout);
  }

  for(int x = 0; x < players; x++){
	if(player[x].alive){
		UDP_CHANNEL_SEND(player[x].channel);
		fprintf(TTY, "> player: %d channel: %d\n", x, player[x].channel);
	}
  }
	
	return OK;
}
//==============================================================================
//==============================================================================
//=============================================================================
//
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

	
	
	for(int i=0; i < MAX_PLAYERS; i++){
		if(i % 2)
			player[i].ship = SHIP_RED_RX;
		else
			player[i].ship = SHIP_BLUE_RX;

		player[i].ship.X = (MAX_X/2) + (i * 200);
		player[i].ship.Y = (MAX_Y/2) + (i * 200);
		player[i].ship.health	= player[i].ship.MAX_health;
		player[i].ship.speed 	= 0.0;
		player[i].ship.angle 	= 0;
		player[i].ship.manevr	= 0;
		player[i].ship.shift 	= 0;
		player[i].ship.acceleration	= 0;
		player[i].ship.alive	= 1;
	}

	pocet_raket = 0;
	pocet_laseru = 0;
	players = 0;


 return OK;
}

//==============================================================================
int Pohybuj_objekty(){
//==============================================================================
//

  for(int i=0; i < players; i++){

	//  === Zdravi lodi ===
 	if(player[i].ship.health < 0)
		  player[i].ship.health = 0;

	//  === Pohyb lodi ===
	if(! player[i].alive) continue;
	if(! player[i].ship.alive) continue;

	player[i].ship.angle += player[i].ship.manevr;
	printf("angle: %f\n", (double) player[i].ship.angle);

	player[i].ship.speed += player[i].ship.acceleration;	
	
	// ==== speed limit ====
 	if(player[i].ship.speed < 0)
		  player[i].ship.speed = 0;
	if(player[i].ship.speed > player[i].ship.MAX_speed) 
			player[i].ship.speed =  player[i].ship.MAX_speed;

		
	// ==== angle limit ====
  	if(player[i].ship.angle > 360)
		player[i].ship.angle -= 360;
	if(player[i].ship.angle < 0)
		player[i].ship.angle += 360;

	// ==== position change ====
	player[i].ship.X += player[i].ship.speed * cos(((float)player[i].ship.angle/180)*M_PI)
	       	+ player[i].ship.shift * cos(((float)(player[i].ship.angle+90)/180)*M_PI);

	player[i].ship.Y -= player[i].ship.speed * sin(((float)player[i].ship.angle/180)*M_PI)
			+ player[i].ship.shift * sin(((float)(player[i].ship.angle+90)/180)*M_PI);	


	player[i].ship.shift /= 1.02;

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

	// === projectiles movement ===
	
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
//==============================================================================
int Detekuj_kolize(){
//==============================================================================

  for(int x=0; x < players; x++){		
  	if(! player[x].ship.alive) continue;

	for(int i=0; i <= pocet_raket; i++){
		if(!rockets[i].alive) continue;
		if(Collision_detect(&player[x].ship, &rockets[i])){
			// DISABLE PROJECTIL
			rockets[i].alive = 0;
			rockets[i].X = 0;
			rockets[i].Y = 0;
			rockets[i].speed = 0;
			// MAKE DAMAGE
			player[x].ship.health -= rockets[i].damage;
			if(player[x].ship.health <= 0){
				printf("# SHIP n.%3d DESTROYED\n",x);
				player[x].ship.speed= 0;
				player[x].ship.X = 0;
				player[x].ship.Y = 0;
				player[x].ship.alive = 0;
			}

		}
	}

	for(int i=0; i <= pocet_laseru; i++){
		if(!lasers[i].alive) continue;
		if(Collision_detect(&player[x].ship, &lasers[i])){
			// DISABLE PROJECTIL
			lasers[i].alive = 0;
			lasers[i].X = 0;
			lasers[i].Y = 0;
			lasers[i].speed = 0;
			// MAKE DAMAGE
			player[x].ship.health -= lasers[i].damage;
			if(player[x].ship.health <= 0){
				printf("# SHIP n.%3d DESTROYED\n",x);
				player[x].ship.speed= 0;
				player[x].ship.X = 0;
				player[x].ship.Y = 0;
				player[x].ship.alive = 0;
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

