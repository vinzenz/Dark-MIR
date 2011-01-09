#include "program.h"
#include "vesmir.h"
#include "images.h"
#include "lod.h"
#include "zbrane.h"
#include "client.h"
#include "menu.h"

#include <SDL/SDL_rotozoom.h>

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
SDL_Surface *GP = NULL;
SDL_Surface *RP = NULL;

	// Radar
	
	rect.x = 20;
	rect.y = HEIGHT - 20 - radar->h;

	int R_X = rect.x + radar->w/2;
	int R_Y = rect.y + radar->h/2;
 	
	SDL_BlitSurface(radar, NULL, screen, &rect);

	for(int i= 0; i < pocet_lodi; i++){
		if(! ship[i].alive) continue;
		if(ship[i].X == 0) continue;
		if(ship[i].Y == 0) continue;


		if(ship[i].strana == GREEN && ship[i].speed == 0) continue;

		rect.x = R_X + (radar->w/2 * (ship[i].X - ship[ID].X)) / MAX_X;
		rect.y = R_Y + (radar->h/2 * (ship[i].Y - ship[ID].Y )) / MAX_Y;

		//printf("SHIP: %d R:X: %3d R:Y: %3d\n",i, rect.x, rect.y);

		if(ship[i].strana == ship[ID].strana){	// FRIEND
			rect.x -= radar_point_g->w/2;	
			rect.y -= radar_point_g->h/2;	
			GP = rotozoomSurface(radar_point_g, 0, 1, 0);
			SDL_BlitSurface(GP, NULL, screen, &rect);
			SDL_FreeSurface(GP);
		}
		else{									// ENEMY
			rect.x -= radar_point_r->w/2;	
			rect.y -= radar_point_r->h/2;	
			RP = rotozoomSurface(radar_point_r, 0, 1, 0);
			SDL_BlitSurface(RP, NULL, screen, &rect);
			SDL_FreeSurface(RP);
		}
	}

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


	// Console
	// -------------------------------------------------------------------
	rect.x = 20;				
	rect.y = 0;

	SDL_BlitSurface(console_bg, NULL, console, NULL);	

	for(int i=0; i < MAX_PLAYERS; i++){
		console_line = TTF_RenderText_Solid(console_font, player_list[i] ,fg_color);

		SDL_BlitSurface(console_line, NULL, console, &rect);	
		SDL_FreeSurface(console_line);
		rect.y += 20;
	}
	rect.y = 20;
	SDL_BlitSurface(console, NULL, screen, &rect);	



return OK;
}



// -----------------------------------------------
//==============================================================================
int Draw_weapon(T_weapon *weapon){
//==============================================================================
SDL_Rect rect;
SDL_Rect rect2;
int T;
//static int clk;
  if(! weapon->alive) return FAIL;

  if(weapon->X < 0){
		  Draw_weapon(&Explosion);
		  return OK;
  }

  // Space borders
  if(weapon->X < (0 + 50))
		  return OK;
  if(weapon->Y < (0 + 50))
		  return OK;
  if(weapon->X > (MAX_X - 50))
		  return OK;
  if(weapon->Y > (MAX_Y - 50))
		  return OK;

  switch(weapon->type){
	case LASER:
		if(weapon->img != NULL)
			SDL_FreeSurface(weapon->img);		

		weapon->img = rotozoomSurface(laser, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X /*- lasers[i].sX */ - X;
		rect.y = (HEIGHT/2) - (weapon->img->h/2) + weapon->Y /*- lasers[i].sY*/ - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		break;

	case ROCKET:
		if(weapon->img != NULL)
			SDL_FreeSurface(weapon->img);		

		weapon->img = rotozoomSurface(raketa, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X  - X;
		rect.y = (HEIGHT/2) - (weapon->img->w/2) + weapon->Y  - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		break;

	case MICRO_MISSILE:
		if(weapon->img != NULL)
			SDL_FreeSurface(weapon->img);		

		weapon->img = rotozoomSurface(micro_missile, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X  - X;
		rect.y = (HEIGHT/2) - (weapon->img->w/2) + weapon->Y  - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		break;

	case ENERGY_LASER:
		if(weapon->img != NULL)
			SDL_FreeSurface(weapon->img);		

		weapon->img = rotozoomSurface(energy_laser, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X /*- lasers[i].sX */ - X;
		rect.y = (HEIGHT/2) - (weapon->img->h/2) + weapon->Y /*- lasers[i].sY*/ - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		break;

	case GUIDED_MISSILE:
		if(weapon->img != NULL)
			SDL_FreeSurface(weapon->img);		

		weapon->img = rotozoomSurface(guided_missile, weapon->angle, 1, 0);
		
		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X  - X;
		rect.y = (HEIGHT/2) - (weapon->img->w/2) + weapon->Y  - Y;
		SDL_BlitSurface(weapon->img, NULL, screen, &rect);
		break;

	case EXPLOSION:

		if(weapon->ttl > 20){
			weapon->alive = 0;
			weapon->ttl = 0;
			break;
		}

		T = weapon->ttl;
		weapon->ttl += 1;

		rect.x = (WIDTH/2) - (50/2) + weapon->X  - X;
		rect.y = (HEIGHT/2) - (50/2) + weapon->Y  - Y;
			
		rect2.x = 50 * (T % 3);	
		rect2.y = 50 * (T / 3);	
		rect2.w = 50;
		rect2.h = 50;
		
		if(weapon->strana == RED)
			SDL_BlitSurface(r_explosion, &rect2, screen, &rect);
		if(weapon->strana == BLUE)
			SDL_BlitSurface(b_explosion, &rect2, screen, &rect);
		if(weapon->strana == GREEN)
			SDL_BlitSurface(g_explosion, &rect2, screen, &rect);
		break;
  }	

 weapon->angle2 = weapon->angle;
 return OK;
}
// -----------------------------------------------
//==============================================================================
int Kresli_strely(){
//==============================================================================
  int i;
	
 	for(i = 0; i <= pocet_weapons; i++){
		if(weapon[i].alive) Draw_weapon(&weapon[i]);
		else weapon[i].img = NULL;
	}


return OK;
}




//==============================================================================
int Draw_menu(){
//==============================================================================
SDL_Rect src;
SDL_Rect dst;

	// === Draw Menu ===
	 SDL_BlitSurface(menu_bg, NULL, screen, NULL);

	 dst.x = 200;
	 dst.y = 350;
	// LOGO
	SDL_BlitSurface(menu_button[0], NULL, screen, &dst);

	 dst.x = 100;
	 dst.y = 50;

	for(int i=1; i < MAX_BUTTONS; i++){
		SDL_BlitSurface(menu_button[i], NULL, screen, &dst);
		dst.y += 70;
	}
	 SDL_Flip(screen);


  return OK;
}
//==============================================================================
int Draw_configure(){
//==============================================================================
SDL_Rect src;
SDL_Rect dst;

	// === Draw Menu ===
	 SDL_BlitSurface(settings_bg, NULL, screen, NULL);

	 dst.x = 50;
	 dst.y = 50;
	// LOGO
	SDL_BlitSurface(menu_button[0], NULL, screen, &dst);

	 dst.x = 200;
	 dst.y = 350;

	for(int i=1; i < MAX_BUTTONS; i++){
		SDL_BlitSurface(menu_button[i], NULL, screen, &dst);
		dst.y += 70;
	}
	 SDL_Flip(screen);


  return OK;
}

//==============================================================================
int Draw_connect(){
//==============================================================================
SDL_Rect src;
SDL_Rect dst;

	// === Draw Menu ===
	 SDL_BlitSurface(connect_bg, NULL, screen, NULL);

	 dst.x = 50;
	 dst.y = 10;
	// LOGO
	SDL_BlitSurface(menu_button[0], NULL, screen, &dst);

	 dst.x = 200;
	 dst.y = 350;

	for(int i=1; i < MAX_BUTTONS; i++){
		SDL_BlitSurface(menu_button[i], NULL, screen, &dst);
		dst.y += 70;
	}

	 dst.x = 75;
	 dst.y = 65;

  char tmp[SERVER_ADDRESS_MAX + 10];

	for(int i=1; i < MAX_SERVERS; i++){

    sprintf(tmp, " [ %2X ]   ", i);
    strcat(tmp, server_list[i]);
		console_line = TTF_RenderText_Solid(text_font, tmp ,fg_color);

		SDL_BlitSurface(console_line, NULL, screen, &dst);	
		SDL_FreeSurface(console_line);
		dst.y += 30;
	}

  console_line = TTF_RenderText_Solid(text_font, status_line ,fg_color);
  SDL_BlitSurface(console_line, NULL, screen, &dst);	
  SDL_FreeSurface(console_line);

  SDL_Flip(screen);


  return OK;
}

//==============================================================================
int FPS(){		// Frames Per Secund
//==============================================================================
	
	int fps = 0;	
	
 return fps;
}
