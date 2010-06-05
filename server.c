

#include "program.h"
#include "server.h"
#include "lod.h"
#include "ships.h"
#include "vesmir.h"
#include "zbrane.h"

#include "protokol.h"

#define TTY stdout
#define MAX_PLAYERS 2



typedef struct str_player{
	IPaddress  ip;	
	char nick[32];
	
	int score;
	T_ship ship;
	TCPsocket sd;	

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
int Speed_up(int id);
int Slow_down(int id);
int Rotate_R(int id);
int Rotate_L(int id);
int Shift_R(int id);
int Shift_L(int id);

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
  //unsigned char r->data[BUFF_SIZE];
  //unsigned char t->data[BUFF_SIZE];
  unsigned char *tp;		// r->data pointer
  int len=0;
  int p_id = 0;
 //==============================================================================
 //==============================================================================
int main(int argc, char **argv){
 //==============================================================================

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
	}else continue;


	
	switch(r->data[0]){

	  	case P_NEW_PLAYER: 			// NEW PLAYER
			New_client(&player[players]);
			break;
	  
	  	case P_ROTATE_R: 	
			Rotate_R(p_id);
			break;

	  	case P_ROTATE_L: 	
			Rotate_L(p_id);
			break;


		case P_SPEED_UP:  
			Speed_up(p_id);
			break;

		case P_SLOW_DOWN: 
			Slow_down(p_id);
			break;

		case P_SHIFT_R:
			Shift_R(p_id);
			break;

		case P_SHIFT_L: 
			Shift_L(p_id);
			break;
			
		case P_FIRE_1:   
		case P_FIRE_2:    
		case P_FIRE_3:     
			break;


	  case P_LOGOUT: 	
			Free_client(p_id);
	//		quit = 1;
			break;
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
  mv_timer = SDL_AddTimer(SERVER_TIME_INTERVAL, Timed_loop, NULL);  // MOVE

	Pohybuj_objekty();

	return OK;
}
//==============================================================================
//==============================================================================
int New_client(T_player *p){
//==============================================================================

	fprintf(TTY, "S: New_client id:%2d: connected\n", players);
	fprintf(TTY, "S: new nick: %s\n", &r->data[1]);
	strncpy(p->nick, (char *)r->data, 32);

	p->score = 0;
	p->ship = SHIP_RED_RX;


	// ACK
	t->address = r->address;
  	t->len = BUFF_SIZE;
	tp=t->data;
	if(players >= MAX_PLAYERS)
		*tp = P_LOGOUT;				// server is full
	else{
		players++;
		*tp = P_NEW_PLAYER;			// player joined
	}
	UDP_SEND;
	
 return OK;
}

//==============================================================================
int Free_client(int id){
//==============================================================================

	fprintf(TTY, "S: Client id:%2d: disconnected\n", id);

	// DELETE PLAYER - shift player[] array
	for(int i=id; i < players-1; i++){
		player[i] = player[i+1];
		POINT(i);
	}

	players--;

 return OK;
}

//==============================================================================
int Speed_up(int id){
//==============================================================================
	
  player[id].ship.speed += player[id].ship.zrychleni;	

  if(player[id].ship.speed > player[id].ship.MAX_speed)
		  player[id].ship.speed = player[id].ship.MAX_speed;	

  /*tp = t->data;
  *tp =  P_SPEED_UP;
  tp++;
  memcpy(tp, &player[id].ship.speed, sizeof(float));

  UDP_SEND;
*/
 return OK;
}
//==============================================================================
int Slow_down(int id){
//==============================================================================
	
  player[id].ship.speed -= player[id].ship.zrychleni;	
  if(player[id].ship.speed < 0)
		  player[id].ship.speed = 0;
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
int Rotate_R(int id){
//==============================================================================
	
  player[id].ship.angle -= player[id].ship.manevr;	

  if(player[id].ship.angle > 360)
	player[id].ship.angle -= 360;
  if(player[id].ship.angle < 0)
	player[id].ship.angle += 360;

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
int Rotate_L(int id){
//==============================================================================
	
  player[id].ship.angle += player[id].ship.manevr;	

  if(player[id].ship.angle > 360)
	player[id].ship.angle -= 360;
  if(player[id].ship.angle < 0)
	player[id].ship.angle += 360;
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
int Shift_R(int id){
//==============================================================================
	
  player[id].ship.uhyb = player[id].ship.MAX_uhyb;

  tp = t->data;
  *tp =  P_SHIFT_R;
  tp++;
  memcpy(tp, &player[id].ship.uhyb, sizeof(float));

//  UDP_SEND;

 return OK;
}
//==============================================================================
int Shift_L(int id){
//==============================================================================
	
  player[id].ship.uhyb = player[id].ship.MAX_uhyb;

  tp = t->data;
  *tp =  P_SHIFT_L;
  tp++;
  memcpy(tp, &player[id].ship.uhyb, sizeof(float));

//  UDP_SEND;

 return OK;
}

//==============================================================================
//==============================================================================
int Send_ship_state(int i){
//==============================================================================

printf(">>> sending ship state <<<\n");
fflush(stdout);
	unsigned char *tp = t->data;
	*tp = P_STATE;
	tp++;	
	*( (float *)tp) = player[i].ship.X;
	fprintf(TTY,"<< X: %4f\n", (double) *((float *)tp));
	tp += sizeof(float);
	*( (float *)tp) = player[i].ship.Y;
	tp += sizeof(float);
	*( (float *)tp) = player[i].ship.speed;
	tp += sizeof(float);
	*( (float *)tp) = player[i].ship.angle;

	UDP_SEND;
	
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
		player[i].ship = SHIP_RED_RX;
		player[i].ship.X = (MAX_X/2) + (i * 200);
		player[i].ship.Y = (MAX_Y/2) + (i * 200);
		player[i].ship.speed = 0.1;
		player[i].ship.angle = 0;
		player[i].ship.alive= 1;
	}


 return OK;
}

//==============================================================================
int Pohybuj_objekty(){
//==============================================================================
//
	//  === Pohyb lodi ===
  for(int i=0; i < players; i++){
	if(! player[i].ship.alive) continue;

	// ==== speed limit ====
	if(player[i].ship.speed > player[i].ship.MAX_speed) 
			player[i].ship.speed =  player[i].ship.MAX_speed;

	//player[i].ship.angle += player[i].ship.manevr;
	//player[i].ship.manevr = 0;

	//player[i].ship.speed += player[i].ship.zrychleni;	
	//player[i].ship.zrychleni = 0;
	
	// ==== position change ====
	player[i].ship.X += player[i].ship.speed * cos(((float)player[i].ship.angle/180)*M_PI)
	       	+ player[i].ship.uhyb * cos(((float)(player[i].ship.angle+90)/180)*M_PI);

	player[i].ship.Y -= player[i].ship.speed * sin(((float)player[i].ship.angle/180)*M_PI)
			+ player[i].ship.uhyb * sin(((float)(player[i].ship.angle+90)/180)*M_PI);	

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

	Send_ship_state(i);
  }
/*
	// === Pohyb projektilu(strel) ===
	//
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
*/		

 return OK;
}


//==============================================================================
int Detekuj_kolize(){
//==============================================================================

  for(int x=1; x <= pocet_lodi; x++){		
  	if(! lode[x].alive) continue;

	for(int i=0; i <= pocet_raket; i++){
		if(!rockets[i].alive) continue;
		if(Collision_detect(&lode[x], &rockets[i])){
			// DISABLE PROJECTIL
			rockets[i].alive = 0;
			rockets[i].X = 0;
			rockets[i].Y = 0;
			rockets[i].speed = 0;
			// MAKE DAMAGE
			lode[x].poskozeni += rockets[i].damage;
			if(lode[x].poskozeni > lode[x].MAX_poskozeni){
				printf("# SHIP n.%3d DESTROYED\n",x);
				lode[x].speed= 0;
				lode[x].X = 0;
				lode[x].Y = 0;
				lode[x].alive = 0;
			}

		}
	}

	for(int i=0; i <= pocet_laseru; i++){
		if(!lasers[i].alive) continue;
		if(Collision_detect(&lode[x], &lasers[i])){
			// DISABLE PROJECTIL
			lasers[i].alive = 0;
			lasers[i].X = 0;
			lasers[i].Y = 0;
			lasers[i].speed = 0;
			// MAKE DAMAGE
			lode[x].poskozeni += lasers[i].damage;
			if(lode[x].poskozeni > lode[x].MAX_poskozeni){
				printf("# SHIP n.%3d DESTROYED\n",x);
				lode[x].speed= 0;
				//lode[x].X = 0;
				//lode[x].Y = 0;
				//lode[x].alive = 0;
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

