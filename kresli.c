#include "program.h"
#include "images.h"
#include "zbrane.h"
#include "lod.h"

SDL_Rect rect2;

int Kresli_lod(int i){

	if(i == 0){
		rect.x = (WIDTH/2) - (lode[i].lod->w/2);
		rect.y = (HEIGHT/2) - (lode[i].lod->h/2);
 	}
	else{
		//rect.x = lode[i].X - (lode[i].lod->w/2);
		//rect.y = lode[i].Y - (lode[i].lod->w/2);
	
		rect.x = (WIDTH/2)  - (lode[i].lod->w/2) + lode[i].X  - X;
		rect.y = (HEIGHT/2) - (lode[i].lod->h/2) + lode[i].Y  - Y;	
		
	}
	
	
	if(uhel2 == lode[i].uhel){
		
		if(rlod != NULL) SDL_BlitSurface(rlod, NULL, screen, &rect);
		
	}
	else{
	
		roto_lod = rotozoomSurface(lode[i].lod, lode[i].uhel, 1, 0);
	
		rlod = roto_lod;

		SDL_BlitSurface(roto_lod, NULL, screen, &rect);
		//SDL_FreeSurface(roto_lod); 
	
		uhel2 = lode[i].uhel;
	
	}
return OK;
}


// -----------------------------------------------
int Kresli_pristroje(){

	// Radar
	
	rect.x = 20;
	rect.y = HEIGHT - 20 - radar->h;
 	
	SDL_BlitSurface(radar, NULL, screen, &rect);

	// Ukazatel poskozeni
	
	rect.x = WIDTH  - 30 - damage->w;
	rect.y = HEIGHT - 30 - damage->h;
	
	rect2.w = (lode[0].MAX_poskozeni / lode[0].poskozeni) * 100;
	rect2.h = damage->h;	
 	
	SDL_BlitSurface(damage, &rect2, screen, &rect);	
	
	
	// Ukazatel rychlosti
	
	rect.x = WIDTH  - 30 - speed->w;
	rect.y = 30 + speed->h;
	
	rect2.w = ((float)lode[0].rychlost / (float)lode[0].MAX_rychlost) * 100;
	rect2.h = speed->h;
	
	SDL_BlitSurface(speed, &rect2, screen, &rect);	
	
	
return OK;
}




// -----------------------------------------------
int Kresli_strely(){
  int i;
	
	// Lasery(plasma)
	
 	for(i = 0; i <= pocet_laseru; i++){
	
		lasery[i].zbran = rotozoomSurface(laser, lasery[i].uhel, 1, 0);
		
		rect.x = (WIDTH/2) - (laser->w/2) + lasery[i].X /*- lasery[i].sX */ - X;
		rect.y = (HEIGHT/2) - (laser->h/2) + lasery[i].Y /*- lasery[i].sY*/ - Y;
		SDL_BlitSurface(lasery[i].zbran, NULL, screen, &rect);
		SDL_FreeSurface(lasery[i].zbran);
	}

	// Rakety
	
	for(i = 0; i <= pocet_raket; i++){
	
		rakety[i].zbran = rotozoomSurface(raketa, rakety[i].uhel, 1, 0);
		
		rect.x = (WIDTH/2) - (raketa->w/2) + rakety[i].X  - X;
		rect.y = (HEIGHT/2) - (raketa->h/2) + rakety[i].Y  - Y;
		SDL_BlitSurface(rakety[i].zbran, NULL, screen, &rect);
		SDL_FreeSurface(rakety[i].zbran);
	}

return OK;
}







int FPS(){		// Frames Per Secund
	
	int fps = 0;	
	
	
	
	
 return fps;
}
