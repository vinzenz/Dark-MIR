
#include "program.h"
#include "images.h"
#include "zbrane.h"
#include "vesmir.h"
#include "lod.h"

// Ship models
#include "ships.h"

// Weapon models
//#include "weapons.h"


// Function prototypes
//==============================================================================
int Prekresli_vesmir();
int Pohybuj_objekty();
int Detekuj_kolize();
int Collision_detect(T_ship *ship, T_weapon *weapon );



//==============================================================================
int Vesmir(){
//==============================================================================
 
 int ukonci=0;
 SDL_Event event;
 Uint8* keys;	
 SDL_TimerID kb_timer = NULL;

	
	// Inicializace
	
	if(Nacti_obrazky_vesmir() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");
 
	SDL_EnableKeyRepeat( 50, 50);  // Dalsi signal stisknute klavesy odesle po 50ms
	SDL_ShowCursor(SDL_DISABLE);  // vypne zobrazovani systemoveho kurzoru

	// casovani reakci na klavesy
	
	kb_timer = SDL_AddTimer(50, Ovladani, NULL); 
	
	
	
	
	my_ship = &SHIP_RED_RX;	
	
	my_ship->angle = 0; // angle ve stupnich
	my_ship->angle2 = 1; // predchozi angle ve stupnich

	X = 3000;
	Y = 3000;

	my_ship->img = IMG_RED_RX;

	my_ship->strana = RED;
	
	// Specifika cizi lodi
	lode[1] = SHIP_BLUE_RX;
	lode[1].img = IMG_BLUE_RX;
	lode[1].strana= BLUE;
	
	lode[1].X = 3450;
	lode[1].Y = 3450;
	
	pocet_lodi   = 1;
	pocet_laseru = 0;
	pocet_raket  = 0;
	
	
	// --------------------- Hlavni smycka -------------------
	while(!ukonci){


		while(SDL_PollEvent(&event)){
			switch(event.type){
				
				// KLAVESY ZMACKNOUT				
				
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
				 	manevr =  + my_ship->manevr;
					break;

				 case SDLK_RIGHT:
				 	manevr =  - my_ship->manevr;
					break;
				
				 case SDLK_UP:
				 	zrychleni = + my_ship->zrychleni;
					break;
				 
				 case SDLK_DOWN:
				 	zrychleni = - my_ship->zrychleni;
					break;
				
				 case SDLK_a:
				 	my_ship->uhyb += 1;
					break;
				 
				 case SDLK_d:
				 	my_ship->uhyb -= 1;
					break;


				 
				 case SDLK_SPACE:
					strilej[LASER] = 1;		// HOLD and FIRE
				 	
					break;
				 
				 case SDLK_RCTRL:
				 case SDLK_LCTRL:
				 	Vystrel(ROCKET, my_ship);	// FIRE 1
					break;
				 
				 
				  default:break;
									
				}
		//my_ship->angle = 0; // angle ve stupnich

	
		/*case SDL_KEYUP: 	
				switch(event.key.keysym.sym){
					
				case SDLK_d:  
				case SDLK_a:
					
				  	
					break;
				default: break;

				}
		*/
				
		}
	}
	
	
	
	// === Primy pristup ke klavesnici ===
	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);
	
	if(keys[SDLK_a]  == SDL_RELEASED && keys[SDLK_d] == SDL_RELEASED){
		my_ship->uhyb = 0;
		//printf("A/D released\n");
	}		
	
	if(keys[SDLK_LEFT] == SDL_RELEASED && keys[SDLK_RIGHT] == SDL_RELEASED){
		manevr = 0;
		//printf("SIPKY LEVA/PRAVA released\n");
	}

	if(keys[SDLK_UP] == SDL_RELEASED && keys[SDLK_DOWN] == SDL_RELEASED){
		zrychleni = 0;
		//printf("SIPKY NAHORU/DOLU released\n");
	}

	if(keys[SDLK_SPACE] == SDL_RELEASED){
		strilej[LASER] = 0;
		//printf("SPACE released\n");
	}

	//printf("---------\n");
	
	
	
	
	// === Pocatek nekonecneho vesmiru ===
	//
	if(X < 0) X = 0;
	if(Y < 0) Y = 0;
	
	// === Konec nekonecneho vesmiru ===
	//
	if(X > MAX_X) X = MAX_X;
	if(Y > MAX_Y) Y = MAX_Y;	
	
	if(my_ship->angle >= 360) my_ship->angle -= 360;		// < 0 ; 360 ) degrees
	if(my_ship->uhyb >= my_ship->MAX_uhyb ) my_ship->uhyb = my_ship->MAX_uhyb ;	
	if(my_ship->uhyb <= -my_ship->MAX_uhyb ) my_ship->uhyb = -my_ship->MAX_uhyb ;		
	if(my_ship->rychlost <= 0) my_ship->rychlost = 0 ;
	if(my_ship->rychlost >= my_ship->MAX_rychlost) my_ship->rychlost = my_ship->MAX_rychlost ;

	
	Pohybuj_objekty();
	
		
		
 	Detekuj_kolize();
		
/*		
	printf("   %G\n",(float)angle/180);
	printf("   %d\n",angle);
	printf("   %G\n",cos((float)angle/180));
*/
	//printf("X  %G    Y  %G\n", X, Y);

//	 float T1 = SDL_GetTicks();
	
	Prekresli_vesmir();
	//SDL_Delay(10);	
	
/*	
	float T2 = SDL_GetTicks();

	float fps = 1000 / (T2 - T1);
	printf("%G  FPS: %3.2G	\n",T2 - T1, fps);	

	T1 = 0;
	T2 = 0;
*/

	}
	
  // === Uklizeni ===
  Uklid_obrazky_vesmir();
  
  SDL_RemoveTimer(kb_timer);
	
	
 return OK;	
}




//==============================================================================
int Prekresli_vesmir(){
//==============================================================================
  
  int x,y;
  
	my_ship->X = X;
	my_ship->Y = Y;
  
	// === Pozadi === 
	
	for(y = -(int)round(Y)%space->h; y<HEIGHT; y+=space->h){
	    for(x = -(int)round(X)%space->w; x<WIDTH; x+=space->w){
		rect.x=x; rect.y=y;
		SDL_BlitSurface(space, NULL, screen, &rect);
	    }
	}
	
	
	// === Strely === 
	
	Kresli_strely();
	
	// === Lod === 
	
	if(lode[1].alive) Kresli_lod(&lode[1]); 		// another ship
	if(my_ship->alive) Kresli_lod(my_ship); 		// my ship 
	
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
int Pohybuj_objekty(){
//==============================================================================
	//  === Pohyb lodi ===
	
	X += my_ship->rychlost * cos(((float)my_ship->angle/180)*M_PI)
	       	+ my_ship->uhyb * cos(((float)(my_ship->angle+90)/180)*M_PI);

	Y -= my_ship->rychlost * sin(((float)my_ship->angle/180)*M_PI)
	       	+ my_ship->uhyb * sin(((float)(my_ship->angle+90)/180)*M_PI);	

	// === Pohyb projektilu(strel) ===
	
	for (int i=0; i<=pocet_laseru; i++){

	lasers[i].X += lasers[i].speed * cos(((float)lasers[i].angle/180)*M_PI);
	lasers[i].Y -= lasers[i].speed  * sin(((float)lasers[i].angle/180)*M_PI); 	
	}
	
	for (int i=0; i<=pocet_raket; i++){

	rockets[i].X += rockets[i].speed * cos(((float)rockets[i].angle/180)*M_PI);
	rockets[i].Y -= rockets[i].speed * sin(((float)rockets[i].angle/180)*M_PI); 
	}
		

 return OK;
}
//==============================================================================
int Detekuj_kolize(){
//==============================================================================

	// === Collision detect ===

		//
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
				lode[x].X = 0;
				lode[x].Y = 0;
				lode[x].alive = 0;
			}
		}
	}
  } 

return OK;
}
//==============================================================================
int Collision_detect(T_ship *ship, T_weapon *weapon ){
//==============================================================================
int c = 0;

  c = 	(fabs(ship->X - weapon->X) < (ship->img->w  >> 1)) &&
  	(fabs(ship->Y - weapon->Y) < (ship->img->h >> 1));

  //if(c)	printf("COLLISION: X: %d Y: %d\n",(int)(ship->X), (int)(ship->Y));

  return c;
}
