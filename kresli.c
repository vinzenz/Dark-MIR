#include "program.h"
#include "vesmir.h"
#include "images.h"
#include "lod.h"
#include "zbrane.h"


//==============================================================================
int Kresli_lod(T_ship *ship){
//==============================================================================
static int T;
static int clk;

SDL_Rect rect = {.x = 0, .y = 0};
SDL_Rect rect2 = {.x = 0, .y = 0};

		rect.x = (WIDTH/2)  - (ship->img->w/2) + ship->X  - X;
		rect.y = (HEIGHT/2) - (ship->img->h/2) + ship->Y  - Y;	
	
		rect2.w = ship->img->w;	
		rect2.h = ship->img->h;	

	if(ship->speed > 0){
		SDL_FreeSurface(ship->rot_img);		// free old img
		ship->rot_img = rotozoomSurface(ship->img_m, ship->angle, 1, 0);
	}
	else{
		SDL_FreeSurface(ship->rot_img);		// free old img
		ship->rot_img = rotozoomSurface(ship->img, ship->angle, 1, 0);
	}
	if(ship->health <= 0){					// crap
		//SDL_FreeSurface(ship->rot_img);		// free old img
		//ship->rot_img = rotozoomSurface(ship->img_c, ship->angle, 1, 0);


		if(clk++ > 10)
			T++;
			
		rect2.x = ship->img->w * (T % 3);	
		rect2.y = ship->img->h * (T / 3);	
		SDL_BlitSurface(r_explosion, &rect2, screen, &rect);
		return OK;
	}

		SDL_BlitSurface(ship->rot_img, NULL, screen, &rect);


return OK;
}


// -----------------------------------------------
//==============================================================================
int Kresli_pristroje(T_ship *my_ship){
//==============================================================================
SDL_Rect rect = {.x = 0, .y = 0};
SDL_Rect rect2 = {.x = 0, .y = 0};

	

	// Radar
	
	rect.x = 20;
	rect.y = HEIGHT - 20 - radar->h;
 	
	SDL_BlitSurface(radar, NULL, screen, &rect);

	// Ukazatel zdravi
	
	rect.x = WIDTH  - 30 - damage->w;
	rect.y = HEIGHT - 30 - damage->h;
	
	rect2.w = damage->w * ((float)my_ship->health / (float)(my_ship->MAX_health)) ;
	rect2.h = damage->h;	
 	
	SDL_BlitSurface(damage, &rect2, screen, &rect);	
	
	
	// Ukazatel speed
	
	rect.x = WIDTH  - 30 - speed->w;
	rect.y = 30 + speed->h;
	
	rect2.w = speed->w * ((float)my_ship->speed / (float)my_ship->MAX_speed);
	rect2.h = speed->h;
	
	SDL_BlitSurface(speed, &rect2, screen, &rect);	
	

	// Ukazatel polohy X
	// -------------------------------------------------------------------
		
	rect.x = WIDTH/2 - position_x->w/2; 
	rect.y = 20;
	
	//rect2.w = ((float)X / (float)MAX_X) * 100;
	rect2.w = position_x->w;
	rect2.h = position_x->h;
	
	SDL_BlitSurface(position_x, &rect2, screen, &rect);	

	rect.x = WIDTH/2 - position_x->w/2 + (((float)X / (float)MAX_X) * (position_x->w )); 
	rect.y = 20;
	
	SDL_BlitSurface(position_ptr_x, &rect2, screen, &rect);	

	// Ukazatel polohy Y
	// -------------------------------------------------------------------
		
	rect.y = HEIGHT/2 - position_y->h/2; 
	rect.x = WIDTH - position_y->w - 20;
	
	rect2.w = position_y->w;
	rect2.h = position_y->h;
	
	SDL_BlitSurface(position_y, &rect2, screen, &rect);	

	rect.y = HEIGHT/2 - position_y->h/2 + (((float)Y / (float)MAX_Y) * (position_y->h ));  
	rect.x = WIDTH - position_y->w - 20;
	
	SDL_BlitSurface(position_ptr_y, &rect2, screen, &rect);	

	// raficka polohy

return OK;
}



// -----------------------------------------------
//==============================================================================
int Draw_weapon(T_weapon *weapon){
//==============================================================================
SDL_Rect rect;

  switch(weapon->type){
	case LASER:
		if(weapon->img == NULL)
			weapon->img = rotozoomSurface(laser, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X /*- lasers[i].sX */ - X;
		rect.y = (HEIGHT/2) - (weapon->img->h/2) + weapon->Y /*- lasers[i].sY*/ - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		//SDL_FreeSurface(weapon->img);
		break;

	case ROCKET:
		if(weapon->img == NULL)
			weapon->img = rotozoomSurface(raketa, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X  - X;
		rect.y = (HEIGHT/2) - (weapon->img->w/2) + weapon->Y  - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		//SDL_FreeSurface(rockets[i].img);
	break;
  }
 return OK;
}
// -----------------------------------------------
//==============================================================================
int Kresli_strely(){
//==============================================================================
  int i;
	
	// Lasery(plasma)
 	for(i = 0; i <= pocet_laseru; i++){
		if(lasers[i].alive) Draw_weapon(&lasers[i]);
	}

	// Rakety
	for(i = 0; i <= pocet_raket; i++){
		if(rockets[i].alive) Draw_weapon(&rockets[i]);
	}

return OK;
}







//==============================================================================
int FPS(){		// Frames Per Secund
//==============================================================================
	
	int fps = 0;	
	
 return fps;
}
