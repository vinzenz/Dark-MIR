#include "program.h"
#include "images.h"
#include "lod.h"




/*
 * Funkce se pokusi nahrat obrazek ze souboru a zkonvertovat ho
 * na stejny pixel format, jako ma okno (framebuffer)
 */

//==============================================================================
SDL_Surface *MIR_LoadImage(const char *filename, int alpha){
//==============================================================================

	SDL_Surface *tmp;// Pomocny
	SDL_Surface *ret;// Bude vracen

	if((tmp = IMG_Load(filename)) == NULL)// Prilinkovat SDL_image
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return NULL;
	}

	if((ret = (alpha) ? SDL_DisplayFormatAlpha(tmp)
                    : SDL_DisplayFormat(tmp)) 
  == NULL)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		SDL_FreeSurface(tmp);
		return NULL;
	}

	SDL_FreeSurface(tmp);// Uz neni potreba

	return ret;
}




//==============================================================================
int Load_space_images(){
//==============================================================================

  DEBUG("Loading space images ...");

	fg_color.r=255; 
	fg_color.g=255; 
	fg_color.b=255;

  DEBUG(" colors set ");
	space  	= MIR_LoadImage(ROOT"images/space.png", 1); 
  DEBUG(" background loaded ");
	
	IMG_RED_RX	= MIR_LoadImage(ROOT"images/R_RX.png", 1); 		
	IMG_RED_RX_move	= MIR_LoadImage(ROOT"images/R_RX_move.png", 1); 	
	IMG_RED_RX_crap = MIR_LoadImage(ROOT"images/R_RX_crap.png", 1); 	
	IMG_RED_EX	= MIR_LoadImage(ROOT"images/R_EX.png", 1); 	
	IMG_RED_EX_move	= MIR_LoadImage(ROOT"images/R_EX_move.png", 1);
	IMG_RED_EX_crap = MIR_LoadImage(ROOT"images/R_EX_crap.png", 1); 

	IMG_BLUE_RX	= MIR_LoadImage(ROOT"images/B_RX.png", 1); 
	IMG_BLUE_RX_move= MIR_LoadImage(ROOT"images/B_RX_move.png", 1); 
	IMG_BLUE_RX_crap= MIR_LoadImage(ROOT"images/B_RX_crap.png", 1); 

	IMG_GREEN_ZX = MIR_LoadImage(ROOT"images/G_ZX.png", 1); 
	IMG_GREEN_ZX_move= MIR_LoadImage(ROOT"images/G_ZX_move.png", 1); 
	IMG_GREEN_ZX_crap= MIR_LoadImage(ROOT"images/G_ZX.png", 1); 
	
	laser = MIR_LoadImage(ROOT"images/RED/laser.png", 1); 
	raketa = MIR_LoadImage(ROOT"images/r1.png", 1); 
	micro_missile= MIR_LoadImage(ROOT"images/micro_missile.png", 1); 
	guided_missile= MIR_LoadImage(ROOT"images/guided_missile.png", 1); 
	//raketa = MIR_LoadImage(ROOT"images/G_Q1.png", 1); 

	energy_laser =  MIR_LoadImage(ROOT"images/G_Q1.png", 1); 
	energy_plasma =  MIR_LoadImage(ROOT"images/G_Q2.png", 1); 

	r_explosion = MIR_LoadImage(ROOT"images/r_explosion.png", 1); 
	g_explosion = MIR_LoadImage(ROOT"images/g_explosion.png", 1); 
	b_explosion = MIR_LoadImage(ROOT"images/b_explosion.png", 1); 

	
	radar = MIR_LoadImage(ROOT"images/system/mapa.png", 1); 
	radar_point_r = MIR_LoadImage(ROOT"images/system/radar_point_r.png", 1); 
	radar_point_g = MIR_LoadImage(ROOT"images/system/radar_point_g.png", 1); 
	radar_point_missile = MIR_LoadImage(ROOT"images/system/radar_point_missile.png", 1); 


	damage = MIR_LoadImage(ROOT"images/system/poskozeni.png", 1); 
	speed = MIR_LoadImage(ROOT"images/system/rychlost.png", 1); 
	position_x = MIR_LoadImage(ROOT"images/system/poloha_x.png", 1); 
	position_y = MIR_LoadImage(ROOT"images/system/poloha_y.png", 1); 
	position_ptr_x = MIR_LoadImage(ROOT"images/system/ptr.png", 1); 
	position_ptr_y = MIR_LoadImage(ROOT"images/system/ptr_y.png", 1); 

	CENTER = MIR_LoadImage(ROOT"images/center_2.png", 1); 
	red_space_station = MIR_LoadImage(ROOT"images/objects/red_space_station.png", 1); 

	asteroid1 = MIR_LoadImage(ROOT"images/objects/asteroid_1.png", 1); 
	asteroid2 = MIR_LoadImage(ROOT"images/objects/asteroid_2.png", 1); 

  DEBUG("Space images are loaded");

	console = MIR_LoadImage(ROOT"images/system/console.png", 1); 
	console_bg = MIR_LoadImage(ROOT"images/system/console.png", 1); 
	
	if (space 		!= NULL && 
		IMG_RED_RX	!= NULL &&
		IMG_RED_RX_move	!= NULL &&
		IMG_RED_RX_crap	!= NULL &&
		IMG_BLUE_RX	!= NULL &&
		IMG_BLUE_RX_move	!= NULL &&
		IMG_BLUE_RX_crap	!= NULL &&
		r_explosion != NULL &&
		g_explosion != NULL &&
		b_explosion != NULL &&
		laser 		!= NULL	&&
		radar 		!= NULL	&&
		damage 		!= NULL	&&
		position_x 	!= NULL	&&
		position_y 	!= NULL	&&
		position_ptr_x 	!= NULL	&&
		position_ptr_y 	!= NULL	&&
		speed 		!= NULL	&&
		console_bg	!= NULL	
		)
		return OK;

  else	
	 return FAIL;
}






//==============================================================================
int Load_menu_images(){
//==============================================================================

	fg_color.r=255; 
	fg_color.g=255; 
	fg_color.b=255;


	menu_bg   	= MIR_LoadImage(ROOT"images/menu/menu_bg.png", 1); 

	//settings_bg	= MIR_LoadImage(ROOT"images/menu/settins_bg.png", 1); 
	settings_bg	= MIR_LoadImage(ROOT"images/menu/configure_bg.png", 1); 

	connect_bg	= MIR_LoadImage(ROOT"images/menu/connect_bg.png", 1); 

	//menu_logo = MIR_LoadImage(ROOT"images/menu/logo.png", 1); 
	menu_logo = MIR_LoadImage(ROOT"images/menu/logo_alpha.png", 1); 
	menu_logo_small = MIR_LoadImage(ROOT"images/menu/logo_small_alpha.png", 1); 

	menu_connect_button = MIR_LoadImage(ROOT"images/menu/connect_button.png", 1); 
	menu_settings_button = MIR_LoadImage(ROOT"images/menu/settings_button.png", 1); 
	menu_exit_button = MIR_LoadImage(ROOT"images/menu/exit_button.png", 1); 
	//policko  	= MIR_LoadImage(ROOT"images/policko.png", 1); 
	//policko1  	= MIR_LoadImage(ROOT"images/policko-1.png", 1); 

	
  selection_table = MIR_LoadImage(ROOT"images/menu/selection_table.png", 1); 

  red_flag = MIR_LoadImage(ROOT"images/red_flag.png", 1); 
  blue_flag = MIR_LoadImage(ROOT"images/blue_flag.png", 1); 

  red_flag_small = MIR_LoadImage(ROOT"images/red_flag_small.png", 1); 
  blue_flag_small= MIR_LoadImage(ROOT"images/blue_flag_small.png", 1); 
	
	if (menu_bg != NULL && 
		settings_bg != NULL)
		return OK;
	
	 return FAIL;
}



//==============================================================================
int Free_menu_images(){
//==============================================================================

	FREE(menu_bg);
	FREE(settings_bg);

	FREE(menu_connect_button);
	FREE(menu_settings_button);
	FREE(menu_exit_button);
		
	return OK;
}


//==============================================================================
int Free_space_images(){
//==============================================================================

	FREE(lod);
	FREE(space);
	FREE(laser);
	FREE(radar);	
	FREE(position_x);	
	FREE(position_y);	
	FREE(position_ptr_x);	
	FREE(position_ptr_y);	
	
	return OK;
}






//==============================================================================
int Nastav_rozliseni(){
//==============================================================================
	
	rozliseni[VYCHOZI_ROZLISENI].X = 1;
	
	//nastavene_rozliseni = VYCHOZI_ROZLISENI ;
	
	rozliseni[0].W = WIDTH0;
	rozliseni[0].H = HEIGHT0;
	
	rozliseni[1].W = WIDTH1;
	rozliseni[1].H = HEIGHT1;

	rozliseni[2].W = WIDTH2;
	rozliseni[2].H = HEIGHT2;


	rozliseni[3].W = WIDTH3;
	rozliseni[3].H = HEIGHT3;

	rozliseni[4].W = WIDTH4;
	rozliseni[4].H = HEIGHT4;
return OK;	
}



//==============================================================================
int Zmena_rozliseni(char X){
//==============================================================================

	nastavene_rozliseni = X;	
	
	SDL_Quit();		// restart graphic layer
	
	Init(rozliseni[nastavene_rozliseni].W, rozliseni[nastavene_rozliseni].H, COLOR, 0);
	
return OK;	
}
