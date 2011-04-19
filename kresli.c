#include "program.h"
#include "vesmir.h"
#include "images.h"
#include "lod.h"
#include "zbrane.h"
#include "client.h"
#include "menu.h"
#include "faction.h"

#include <SDL/SDL_rotozoom.h>

//==============================================================================
int Draw_object(T_object *object){
//==============================================================================
//static int T;
//static int clk;


  if(object->descriptor == SHIP){
    Draw_ship(object);
    return OK;
  }

  if(object->descriptor == WEAPON){
    Draw_weapon(object);
    return OK;
  }

  if(object->descriptor == NATURE){
    Draw_nature(object);
    //DEBUG("Draw_object(): ASTEROID");
    //fprintf(D_OUT, "object X: %3d\n", object->X);
    //fprintf(D_OUT, "object Y: %3d\n", object->Y);
    return OK;
  }

  DEBUG("Draw_object(): Unknown object");
  fprintf(D_OUT, "object type: %3d\n", object->type);
  return OK;
}


//==============================================================================
int Draw_nature(T_object *object){
//==============================================================================
//static int T;
//static int clk;


    SDL_Rect rect = {.x = 0, .y = 0};
    SDL_Rect rect2 = {.x = 0, .y = 0};

      if(object->type == ASTEROID){
        switch(object->model){
          case 0:
          case 1:
            object->img = asteroid1;
            break;
          case 2:
            object->img = asteroid2;
            POINT(2);
            break;
          default:
            POINT(2);
            object->img = asteroid2;
        }
      }


		rect.x = (WIDTH/2)  - (object->img->w/2) + object->X  - X;
		rect.y = (HEIGHT/2) - (object->img->h/2) + object->Y  - Y;	
	
		rect2.w = object->img->w;	
		rect2.h = object->img->h;	


		SDL_BlitSurface(object->img, NULL, screen, &rect);

  return OK;
}

//==============================================================================
int Draw_ship(T_object *object){
//==============================================================================
static int T;
static int clk;


  // OBJECT SHIP 
  // Set new img
  if(object->img == NULL){

    if(object->faction == RED){    
  		object->img = IMG_RED_RX;
    }
    if(object->faction == BLUE){    
  		object->img = IMG_BLUE_RX;
    }
  }


    SDL_Rect rect = {.x = 0, .y = 0};
    SDL_Rect rect2 = {.x = 0, .y = 0};

		rect.x = (WIDTH/2)  - (object->img->w/2) + object->X  - X;
		rect.y = (HEIGHT/2) - (object->img->h/2) + object->Y  - Y;	
	
		rect2.w = object->img->w;	
		rect2.h = object->img->h;	

  	if(object->speed > 0){
	  	SDL_FreeSurface(object->rot_img);		// free old img
  		object->rot_img = rotozoomSurface(object->img_m, object->angle, 1, 0);
  	}
  	else{
	  	SDL_FreeSurface(object->rot_img);		// free old img
  		object->rot_img = rotozoomSurface(object->img, object->angle, 1, 0);
  	}
	  if(object->health <= 0){					// crap
		  //SDL_FreeSurface(object->rot_img);		// free old img
		  //object->rot_img = rotozoomSurface(object->img_c, object->angle, 1, 0);


		  if(clk++ > 10)
			  T++;
			
		  rect2.x = object->img->w * (T % 3);	
		  rect2.y = object->img->h * (T / 3);	
		  SDL_BlitSurface(r_explosion, &rect2, screen, &rect);
		  return OK;
	  }

		SDL_BlitSurface(object->rot_img, NULL, screen, &rect);

  return OK;
}

// -----------------------------------------------
//==============================================================================
int Kresli_pristroje(T_object *my_ship){
//==============================================================================
SDL_Rect rect = {.x = 0, .y = 0};
SDL_Rect rect2 = {.x = 0, .y = 0};
SDL_Surface *GP = NULL;
SDL_Surface *RP = NULL;
SDL_Surface *img = NULL;

	//  === Radar ===
	
	rect.x = 20;
	rect.y = HEIGHT - 20 - radar->h;

	int R_X = rect.x + radar->w/2;
	int R_Y = rect.y + radar->h/2;
 	
	SDL_BlitSurface(radar, NULL, screen, &rect);

	for(int i= 0; i < MAX_OBJECTS; i++){
		if(! object[i].alive) continue;

		//if(object[i].X == 0) continue;
		//if(object[i].Y == 0) continue;


		if(object[i].faction == GREEN && object[i].speed == 0) continue;

		rect.x = R_X + (radar->w/2 * (object[i].X - object[ID].X )) / MAX_X;
		rect.y = R_Y + (radar->h/2 * (object[i].Y - object[ID].Y )) / MAX_Y;

		//printf("SHIP: %d R:X: %3d R:Y: %3d\n",i, rect.x, rect.y);

    
    // ASTEROID
	  if(object[i].descriptor == NATURE){	
			rect.x -= radar_point_g->w/2;	
			rect.y -= radar_point_g->h/2;	
			RP = rotozoomSurface(radar_point_garbage, 0, 1, 0);
			SDL_BlitSurface(RP, NULL, screen, &rect);
			SDL_FreeSurface(RP);
		}
    else
    // MISSILE
	  if(object[i].descriptor == WEAPON){

	  switch(object[i].type){
	    case MISSILE:        img = radar_point_missile; break;
	    case GUIDED_MISSILE: img = radar_point_missile; break;
      default: img = NULL;
    
    }
      if(img != NULL){
			rect.x -= radar_point_g->w/2;	
			rect.y -= radar_point_g->h/2;	
			RP = rotozoomSurface(img, 0, 1, 0);
			SDL_BlitSurface(RP, NULL, screen, &rect);
			SDL_FreeSurface(RP);
      }
		}
    else

    // FRIEND
		if(object[i].faction == object[ID].faction){	
			rect.x -= radar_point_g->w/2;	
			rect.y -= radar_point_g->h/2;	
			GP = rotozoomSurface(radar_point_g, 0, 1, 0);
			SDL_BlitSurface(GP, NULL, screen, &rect);
			SDL_FreeSurface(GP);
		}
    // ENEMY
		else{									
			rect.x -= radar_point_r->w/2;	
			rect.y -= radar_point_r->h/2;	
			RP = rotozoomSurface(radar_point_r, 0, 1, 0);
			SDL_BlitSurface(RP, NULL, screen, &rect);
			SDL_FreeSurface(RP);
		}
	}
  

	//  === Ukazatel zdravi ===
	
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
int Draw_weapon(T_object *weapon){
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
		if(weapon->img == NULL){
		 if(weapon->faction == RED) 
		    weapon->img = RED_laser;
		 if(weapon->faction == BLUE) 
		    weapon->img = BLUE_laser;

      FREE(weapon->rot_img);
		  weapon->rot_img = rotozoomSurface(weapon->img, weapon->angle, 1, 0);
    }

		rect.x = (WIDTH/2) - (weapon->img->w/2) + weapon->X /*- lasers[i].sX */ - X;
		rect.y = (HEIGHT/2) - (weapon->img->h/2) + weapon->Y /*- lasers[i].sY*/ - Y;
		SDL_BlitSurface(weapon->rot_img, NULL, screen, &rect);
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
      FREE(weapon->img);  // potencial problem
			weapon->img = NULL;
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
		
		if(weapon->faction == RED)
			SDL_BlitSurface(r_explosion, &rect2, screen, &rect);
		if(weapon->faction == BLUE)
			SDL_BlitSurface(b_explosion, &rect2, screen, &rect);
		if(weapon->faction == GREEN)
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
	
 	for(i = 0; i < MAX_OBJECTS; i++){
		if(object[i].alive) Draw_object(&object[i]);
		else object[i].img = NULL;
	}


return OK;
}




//==============================================================================
int Draw_menu(){
//==============================================================================
//SDL_Rect src;
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
//SDL_Rect src;
SDL_Rect dst;

	// === Draw Menu ===

	for(int i=0; i < MAX_ITEMS; i++){
    if(! item[i].alive) continue;
 
  	 dst.x = item[i].x;
	   dst.y = item[i].y;

    if(item[i].active) 
		  SDL_BlitSurface(item[i].img_a, NULL, screen, &dst);
    else
		  SDL_BlitSurface(item[i].img_p, NULL, screen, &dst);
	}


  // Text labels and options 

	 dst.x = 200;
	 dst.y = 200;

	for(int i=0; i < CONFIG_ITEMS_MAX; i++){

		console_line = TTF_RenderText_Solid(text_font, configure_list[i] ,fg_color);

		SDL_BlitSurface(console_line, NULL, screen, &dst);	
		SDL_FreeSurface(console_line);
		dst.y += 30;
	}

  dst.x = 400;
  dst.y = 410;
  console_line = TTF_RenderText_Solid(text_font, nick ,fg_color);
  SDL_BlitSurface(console_line, NULL, screen, &dst);	
  SDL_FreeSurface(console_line);

/*
	 dst.x = 300; dst.y = HEIGHT - 400;
	 SDL_BlitSurface(red_flag_small, NULL, screen, &dst);
	 dst.x = WIDTH -600; dst.y = HEIGHT - 400;
	 SDL_BlitSurface(blue_flag_small, NULL, screen, &dst);
*/
	 SDL_Flip(screen);


  return OK;
}

//==============================================================================
int Draw_connect(){
//==============================================================================
//SDL_Rect src;
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

	 dst.x = 600; dst.y = 580;
	 SDL_BlitSurface(red_flag_small, NULL, screen, &dst);
	 dst.x = 750; dst.y = 580;
	 SDL_BlitSurface(blue_flag_small, NULL, screen, &dst);

  SDL_Flip(screen);


  return OK;
}

//==============================================================================
int Draw_help(){
//==============================================================================
//SDL_Rect src;
SDL_Rect dst;

	// === Draw Menu ===

	for(int i=0; i < MAX_ITEMS; i++){
    if(! item[i].alive) continue;
 
  	 dst.x = item[i].x;
	   dst.y = item[i].y;

    if(item[i].active) 
		  SDL_BlitSurface(item[i].img_a, NULL, screen, &dst);
    else
		  SDL_BlitSurface(item[i].img_p, NULL, screen, &dst);
	}

    dst.x = 300;
    dst.y = 500;

		console_line = 
      TTF_RenderText_Solid(text_font, "PRESS THE BUTTON TO SHOW ACTION" ,fg_color);

		SDL_BlitSurface(console_line, NULL, screen, &dst);	
		SDL_FreeSurface(console_line);
		dst.y += 30;

	 SDL_Flip(screen);


  return OK;
}


//==============================================================================
int FPS(){		// Frames Per Secund
//==============================================================================
	
	int fps = 0;	
	
 return fps;
}
