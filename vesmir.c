
#include "program.h"
#include "images.h"
#include "zbrane.h"
#include "vesmir.h"
#include "lod.h"

int Prekresli_vesmir();



int Vesmir(){
 
 int i;
 int ukonci=0;
 SDL_Event event;
 Uint8* keys;	
 SDL_TimerID kb_timer = NULL;

	
	// Inicializace
	
	X = MAX_X / 2;
  	Y = MAX_Y / 2;
		
	if(Nacti_obrazky_vesmir() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");
 
	SDL_EnableKeyRepeat( 50, 50);  // Dalsi signal stisknute klavesy odesle po 50ms
	SDL_ShowCursor(SDL_DISABLE);  // vypne zobrazovani systemoveho kurzoru

	// casovani reakci na klavesy
	
	kb_timer = SDL_AddTimer(50, Ovladani, NULL); 
	
	
	
	
	
	uhel = 0; // uhel ve stupnich
	uhel2 = 1; // predchozi uhel ve stupnich

	
	// Specifika hracovi lodi
	lode[0].strana = RED;
	
	lode[0].X = 16000;
	lode[0].Y = 16000;
	
	lode[0].MAX_poskozeni = 70;
	lode[0].poskozeni = 1;
	
	lode[0].MAX_rychlost = 13;
	lode[0].rychlost = 0;
	lode[0].MAX_uhyb = 5;
	lode[0].uhyb = 0;
	lode[0].zrychleni = 0.3;
	lode[0].manevr = 5;
	lode[0].uhel = 0;
	
	
	
	// Specifika cizi lodi
	lode[1].strana = GREEN;
	
	lode[1].X = 15000;
	lode[1].Y = 15000;
	
	lode[1].MAX_poskozeni = 100;
	lode[1].poskozeni = 1;
	
	lode[1].MAX_rychlost = 10;
	lode[1].rychlost = 0;
	lode[1].MAX_uhyb = 5;
	lode[1].uhyb = 0;
	lode[1].zrychleni = 0.3;
	lode[1].manevr = 5;
	lode[1].uhel = 0;
	
	
	
	
	
	pocet_laseru=0;
	pocet_raket=0;
	
	
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
				 	manevr =  + lode[0].manevr;
					break;

				 case SDLK_RIGHT:
				 	manevr =  - lode[0].manevr;
					break;
				
				 case SDLK_UP:
				 	zrychleni = + lode[0].zrychleni;
					break;
				 
				 case SDLK_DOWN:
				 	zrychleni = - lode[0].zrychleni;
					break;
				
				 case SDLK_a:
				 	lode[0].uhyb += 1;
					break;
				 
				 case SDLK_d:
				 	lode[0].uhyb -= 1;
					break;


				 
				 case SDLK_SPACE:
					strilej[LASER] = 1;
				 	
					break;
				 
				 case SDLK_RCTRL:
				 case SDLK_LCTRL:
				 	Vystrel(RAKETA,0);
					break;
				 
				 
				  default:break;
									
				}
		uhel = 0; // uhel ve stupnich

	
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
	
	
	
	// Primy pristup ke klavesnici
	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);
	
	if(keys[SDLK_a]  == SDL_RELEASED && keys[SDLK_d] == SDL_RELEASED){
		lode[0].uhyb = 0;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	// Pocatek nekonecneho vesmiru
	if(X < 0) X = 0;
	if(Y < 0) Y = 0;
	
	// Konec nekonecneho vesmiru
	if(X > MAX_X) X = MAX_X;
	if(Y > MAX_Y) Y = MAX_Y;	
	
	if(lode[0].uhel >= 360) lode[0].uhel -= 360;
	if(lode[0].uhyb >= lode[0].MAX_uhyb ) lode[0].uhyb = lode[0].MAX_uhyb ;	
	if(lode[0].uhyb <= -lode[0].MAX_uhyb ) lode[0].uhyb = -lode[0].MAX_uhyb ;		
	if(lode[0].rychlost <= 0) lode[0].rychlost = 0 ;
	if(lode[0].rychlost >= lode[0].MAX_rychlost) lode[0].rychlost = lode[0].MAX_rychlost ;

	
	// Pohyb lodi
		
	
	X += lode[0].rychlost * cos(((float)lode[0].uhel/180)*M_PI) + lode[0].uhyb * cos(((float)(lode[0].uhel+90)/180)*M_PI);
	Y -= lode[0].rychlost * sin(((float)lode[0].uhel/180)*M_PI) + lode[0].uhyb * sin(((float)(lode[0].uhel+90)/180)*M_PI);	

	// Pohyb projektilu(strel)
	
	
	for (i=0; i<=pocet_laseru; i++){

	lasery[i].X += LASER_rychlost * cos(((float)lasery[i].uhel/180)*M_PI);
	lasery[i].Y -= LASER_rychlost * sin(((float)lasery[i].uhel/180)*M_PI); 	
	}
	
	for (i=0; i<=pocet_raket; i++){

	rakety[i].X += R1_rychlost * cos(((float)rakety[i].uhel/180)*M_PI);
	rakety[i].Y -= R1_rychlost * sin(((float)rakety[i].uhel/180)*M_PI); 
	}
		
	//printf("X %G Y %G *** ", lasery[i].X, lasery[i].Y );	
		
		
		
/*		
	printf("   %G\n",(float)uhel/180);
	printf("   %d\n",uhel);
	printf("   %G\n",cos((float)uhel/180));
*/
	//printf("X  %G    Y  %G\n", X, Y);

	 float T1 = SDL_GetTicks();
	
	Prekresli_vesmir();
	//SDL_Delay(10);	
	
	
	float T2 = SDL_GetTicks();

	float fps = 1000 / (T2 - T1);
	printf("%G  FPS: %3.2G	\n",T2 - T1, fps);	

	T1 = 0;
	T2 = 0;


	}
	
	// Uklizeni
		
  Uklid_obrazky_vesmir();
  
  SDL_RemoveTimer(kb_timer);
	
	
 return OK;	
}





int Prekresli_vesmir(){
  
  int x,y;
  
  
	// Pozadi 
	
	for(y = -(int)round(Y)%space->h; y<HEIGHT; y+=space->h){
	    for(x = -(int)round(X)%space->w; x<WIDTH; x+=space->w){
		rect.x=x; rect.y=y;
		SDL_BlitSurface(space, NULL, screen, &rect);
	    }
	}
	
	
	// Strely
	
	Kresli_strely();
	
	// Lod
	
	//Kresli_lod(1); // Cizi lod
	Kresli_lod(0); // Moje lod
	
	// Pristroje
	
	Kresli_pristroje();
	
	
	
	SDL_Flip(screen);
	
return OK;	
}
