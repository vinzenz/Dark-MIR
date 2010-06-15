
#include "program.h"
#include "images.h"
#include "zbrane.h"
#include "vesmir.h"
#include "lod.h"

// Net stuff
#include "protokol.h"
#include "client.h"

// Ship models
#include "ships.h"

// Weapon models
//#include "weapons.h"

// Global variables
//=============================================================================
 SDL_TimerID kb_timer = NULL;
 SDL_TimerID mv_timer = NULL;
 SDL_TimerID draw_timer = NULL;

// Function prototypes
//==============================================================================
int Inicializuj_objekty();
int Pohybuj_objekty();
int Detekuj_kolize();
 int Collision_detect(T_ship *ship, T_weapon *weapon );
int Prekresli_vesmir();

Uint32 Timed_loop(Uint32 interval, void *param);
Uint32 Redraw_loop(Uint32 interval, void *param);

//==============================================================================
int Vesmir(){
//==============================================================================
 
 int ukonci=0;
 SDL_Event event;
 Uint8* keys;	

	// Inicializace

	if(New_client() == OK)		// TELL "hello server"
		printf("---==:: CONNECTED ::==---\n");
	else{			
		fprintf(stderr, "SERVER ERROR");
		// react somehow
	}

	
	if(Nacti_obrazky_vesmir() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");
 
	//SDL_EnableKeyRepeat( 50, 50);  // Dalsi signal stisknute klavesy odesle po 50ms
	SDL_ShowCursor(SDL_DISABLE);  // vypne zobrazovani systemoveho kurzoru

	// casovani reakci na klavesy
	
//	kb_timer = SDL_AddTimer(50, Ovladani, NULL); 					// KEYBORD
//	mv_timer = SDL_AddTimer(1, Timed_loop, NULL); 					// MOVE
	draw_timer = SDL_AddTimer(30, Redraw_loop, NULL); 				// DRAW
	

	Inicializuj_objekty();
	
	// ============================== GAME LOOP ==============================
	while(!ukonci){

		// Recieving position X,Y, angle, speed ... of ship	
		//Get_ship_state();		// NON blocking function
		Timed_loop(1, NULL);

		while(SDL_PollEvent(&event)){
			switch(event.type){
				
			// 	KEYs PRESSED
			case SDL_KEYDOWN: 	
				switch(event.key.keysym.sym){
					
				  case SDLK_ESCAPE:
					pauza = 1;
				  	ukonci = 1;		
					break;
				
				  case SDLK_PAUSE:
				  case SDLK_p:
					if(pauza==0) pauza = 1;
					else pauza = 0;
					fprintf(stderr, "pauza = %i\n", pauza);	
					break;
					
				 case SDLK_LEFT:
					Rotate_L(START);
				 	//manevr =  + my_ship->manevr;
					break;

				 case SDLK_RIGHT:
					Rotate_R(START);
				 	//manevr =  - my_ship->manevr;
					break;
				
				 case SDLK_UP:
					Speed_up(START);
				 	//acceleration = + my_ship->acceleration;
					break;
				 
				 case SDLK_DOWN:
					Slow_down(START);
				 	//acceleration = - my_ship->acceleration;
					break;
				
				 case SDLK_a:
					Shift_L(START);
				 	//my_ship->shift += 1;
					break;
				 
				 case SDLK_d:
					Shift_R(START);
				 	//my_ship->shift -= 1;
					break;


				 case SDLK_LSHIFT:			// TURBO
				 case SDLK_RSHIFT:			
					Turbo(START);
				 	break;

				 case SDLK_LALT:			// MODIFIKATOR = FIRE 1
				 case SDLK_SPACE:
					if(ship[ID].strana == GREEN)
						Fire(ENERGY_LASER);
					else
						Fire(LASER);
				 	
					break;
				 
				 case SDLK_RCTRL:
				 case SDLK_LCTRL:
					if(ship[ID].strana == GREEN);
						//Fire(ROCKET);
					else
						Fire(ROCKET);
					break;
				 
				 
				  default:break;
									
				}
				break;

			// ==== KEY RELEASED ===	
			case SDL_KEYUP: 		
				switch(event.key.keysym.sym){
				
					
				 case SDLK_LEFT:
					Rotate_L(STOP);
					break;

				 case SDLK_RIGHT:
					Rotate_R(STOP);
					break;
				
				 case SDLK_UP:
					Speed_up(STOP);
					break;
				 
				 case SDLK_DOWN:
					Slow_down(STOP);
					break;
				
				 case SDLK_a:
					Shift_L(STOP);
					break;
				 
				 case SDLK_d:
					Shift_R(STOP);
					break;

				 case SDLK_LSHIFT:			// TURBO
				 case SDLK_RSHIFT:			
					Turbo(STOP);
				 	break;
						
				 default: break;
				}
				break;
	
			case SDL_QUIT:
				ukonci = 1;
				break;

				
		}
	}
	
	
	
	// === Primy pristup ke klavesnici ===
	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);
/*	
	if(keys[SDLK_a]  == SDL_RELEASED && keys[SDLK_d] == SDL_RELEASED){
		my_ship->shift = 0;
		//printf("A/D released\n");
	}		
	
	if(keys[SDLK_LEFT] == SDL_RELEASED && keys[SDLK_RIGHT] == SDL_RELEASED){
		manevr = 0;
		//printf("SIPKY LEVA/PRAVA released\n");
	}

	if(keys[SDLK_UP] == SDL_RELEASED && keys[SDLK_DOWN] == SDL_RELEASED){
		acceleration = 0;
		//printf("SIPKY NAHORU/DOLU released\n");
	}
*/
/*
	if(keys[SDLK_SPACE] == SDL_RELEASED){
		strilej[LASER] = 0;
		//printf("SPACE released\n");
	}
*/
	//printf("---------\n");
	
	
	
	
	// === Pocatek nekonecneho vesmiru ===
	//
//	if(X < 0) X = 0;
//	if(Y < 0) Y = 0;
	
	// === Konec nekonecneho vesmiru ===
	//
	//if(X > MAX_X) X = MAX_X;
//	if(Y > MAX_Y) Y = MAX_Y;	

// NYNI RESI SERVER	
/*
	// === prubezne opravy parametru ===	
	if(my_ship->angle >= 360) my_ship->angle -= 360;		// < 0 ; 360 ) degrees
	if(my_ship->shift >= my_ship->MAX_shift ) my_ship->shift = my_ship->MAX_shift ;	
	if(my_ship->shift <= -my_ship->MAX_shift ) my_ship->shift = -my_ship->MAX_shift ;		
	if(my_ship->speed <= 0) my_ship->speed = 0 ;
	if(my_ship->speed >= my_ship->MAX_speed) my_ship->speed = my_ship->MAX_speed ;

*/	
//	Pohybuj_objekty();
	
		
		
//	Detekuj_kolize();
		

//	float T1 = SDL_GetTicks();
	
	//Prekresli_vesmir();
	//SDL_Delay(10);	
	
	
	//float T2 = SDL_GetTicks();

	//float fps = 1000 / (T2 - T1);
//	printf("%G  FPS: %3.2G	\n",T2 - T1, fps);	

//	T1 = 0;
//	T2 = 0;


	} 
// ==== END GAME LOOP ====

  Logout();		// TELL "goodbye server"
  printf("---==:: DISCONNECTED ::==---\n");
	
  // === Uklizeni ===
  Uklid_obrazky_vesmir();
  
  SDL_RemoveTimer(draw_timer);
  SDL_RemoveTimer(mv_timer);
  SDL_RemoveTimer(kb_timer);
	
	
 return OK;	
}


//==============================================================================
Uint32 Redraw_loop(Uint32 interval, void *param){
//==============================================================================

//	printf("TIMER: Redraw_loop()\n");
	//draw_timer = SDL_AddTimer(20, Redraw_loop, NULL); 	// MOVE

	Prekresli_vesmir();

 return interval;
}
//==============================================================================
Uint32 Timed_loop(Uint32 interval, void *param){
//==============================================================================
// 50 ms
	//printf("TIMER: UDP_RECV()\n");
	//mv_timer = SDL_AddTimer(10, Timed_loop, NULL); 	// MOVE

// SERVER periodical message P_STATE
	
	UDP_RECV;
	else return interval;

	switch(r->data[0]){

		case P_SHIP_STATES:
			Get_ship_states(); 
			break;
		case P_WEAPON_STATES:
			Get_weapon_states(); 
			break;
		case P_PLAYER_LIST:
			Get_player_list(); 
			break;

	}

return interval;
}


//==============================================================================
int Prekresli_vesmir(){
//==============================================================================
 
  static float T1;
  static int FPS;

  if(SDL_GetTicks() - T1 >= 1000){
//		  printf("FPS: %d\n",FPS);
		  FPS = 0;
		  T1 = SDL_GetTicks();
  }
  FPS++;

  SDL_Rect rect;
  int x,y;
  
	X = my_ship->X;
	Y = my_ship->Y;
  
	// === Pozadi === 
	
	for(y = -(int)round(Y)%space->h; y<HEIGHT; y+=space->h){
	    for(x = -(int)round(X)%space->w; x<WIDTH; x+=space->w){
		rect.x=x; rect.y=y;
		SDL_BlitSurface(space, NULL, screen, &rect);
	    }
	}
/*	
	rect.x = (WIDTH/2) - (CENTER->w/2) + MAX_X/2 - X;
	rect.y = (HEIGHT/2) - (CENTER->h/2) + MAX_Y/2 - Y;
	SDL_BlitSurface(CENTER, NULL, screen, &rect);
*/

	// === Strely === 
	
	Kresli_strely();
	
	// === Lod === 
	//		if(my_ship->alive) Kresli_lod(my_ship); 		// my ship 

	for(int id = 0; id < pocet_lodi; id++){	
		if(ship[id].alive) Kresli_lod(&ship[id]); 		// another ship
	}	
	// === Pristroje ===
	
	Kresli_pristroje(my_ship);
/*	
	printf(">> sX: %d sY: %d X: %d Y: %d x: %d y: %d \n",
		my_ship->sX, my_ship->sY, (int)(my_ship->X), 
		(int) (my_ship->Y), my_ship->x, my_ship->y);	
*/	

	//printf(">> X: %d Y: %d \n", (int)(my_ship->X), (int)(my_ship->Y));

	SDL_Flip(screen);
	
return OK;	
}


//==============================================================================
int Inicializuj_objekty(){
//==============================================================================
	// Specifika vlastni lodi	
	// ====================
	SHIP_RED_RX.img = IMG_RED_RX;
	SHIP_RED_RX.img_m = IMG_RED_RX_move;
	SHIP_RED_RX.img_c = IMG_RED_RX_crap;
	SHIP_RED_RX.strana = RED;

	SHIP_RED_EX.img = IMG_RED_EX;
	SHIP_RED_EX.img_m = IMG_RED_EX_move;
	SHIP_RED_EX.img_c = IMG_RED_EX_crap;
	SHIP_RED_EX.strana = RED;

	SHIP_BLUE_RX.img = IMG_BLUE_RX;
	SHIP_BLUE_RX.img_m = IMG_BLUE_RX_move;
	SHIP_BLUE_RX.img_c = IMG_BLUE_RX_crap;
	SHIP_BLUE_RX.strana = BLUE;

	SHIP_GREEN_ZX.img = IMG_GREEN_ZX;
	SHIP_GREEN_ZX.img_m = IMG_GREEN_ZX_move;
	SHIP_GREEN_ZX.img_c = IMG_GREEN_ZX_crap;
	SHIP_GREEN_ZX.strana = GREEN;

	//ship[0] = SHIP_RED_RX;
	//ship[0] = SHIP_BLUE_RX;
	
	my_ship = &ship[ID];	
	
	ship[0] = SHIP_GREEN_ZX;
	ship[1] = SHIP_BLUE_RX;
	ship[2] = SHIP_RED_EX;
	ship[3] = SHIP_GREEN_ZX;
	ship[4] = SHIP_BLUE_RX;
	
	pocet_lodi   = 5;
	pocet_laseru = 0;
	pocet_raket  = 0;

 return OK;
}

/*
//==============================================================================
int Pohybuj_objekty(){
//==============================================================================
//
	//  === Pohyb lodi ===
	my_ship->angle += manevr;
	my_ship->speed += acceleration;	
	
	X += my_ship->speed * cos(((float)my_ship->angle/180)*M_PI)
	       	+ my_ship->shift * cos(((float)(my_ship->angle+90)/180)*M_PI);

	Y -= my_ship->speed * sin(((float)my_ship->angle/180)*M_PI)
	       	+ my_ship->shift * sin(((float)(my_ship->angle+90)/180)*M_PI);	


	for (int i=1; i<=pocet_lodi; i++){
	  if(! ship[i].alive) continue;
	  ship[i].X += ship[i].speed * cos(((float)ship[i].angle/180)*M_PI);
	  ship[i].Y -= ship[i].speed  * sin(((float)ship[i].angle/180)*M_PI); 	
	}

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
		

 return OK;
}
*/
/*
//==============================================================================
int Detekuj_kolize(){
//==============================================================================

  for(int x=1; x <= pocet_lodi; x++){		
  	if(! ship[x].alive) continue;

	for(int i=0; i <= pocet_raket; i++){
		if(!rockets[i].alive) continue;
		if(Collision_detect(&ship[x], &rockets[i])){
			// DISABLE PROJECTIL
			rockets[i].alive = 0;
			rockets[i].X = 0;
			rockets[i].Y = 0;
			rockets[i].speed = 0;
			// MAKE DAMAGE
			ship[x].health -= rockets[i].damage;
			if(ship[x].health <= 0 ){
				printf("# SHIP n.%3d DESTROYED\n",x);
				ship[x].speed= 0;
				ship[x].X = 0;
				ship[x].Y = 0;
				ship[x].alive = 0;
			}

		}
	}

	for(int i=0; i <= pocet_laseru; i++){
		if(!lasers[i].alive) continue;
		if(Collision_detect(&ship[x], &lasers[i])){
			// DISABLE PROJECTIL
			lasers[i].alive = 0;
			lasers[i].X = 0;
			lasers[i].Y = 0;
			lasers[i].speed = 0;
			// MAKE DAMAGE
			ship[x].health -= lasers[i].damage;
			if(ship[x].health <= 0){
				printf("# SHIP n.%3d DESTROYED\n",x);
				ship[x].speed= 0;
				//ship[x].X = 0;
				//ship[x].Y = 0;
				//ship[x].alive = 0;
			}
		}
	}
  } 

return OK;
}
*/
//==============================================================================
int Collision_detect(T_ship *ship, T_weapon *weapon ){
//==============================================================================

  int c = (fabs(ship->X - weapon->X) < (ship->img->w  >> 1)) &&
  	  (fabs(ship->Y - weapon->Y) < (ship->img->h >> 1));

  //if(c)	printf("COLLISION: X: %d Y: %d\n",(int)(ship->X), (int)(ship->Y));

  return c;
}
