#include "program.h"
#include "images.h"
#include "lod.h"




/*
 * Funkce se pokusi nahrat obrazek ze souboru a zkonvertovat ho
 * na stejny pixel format, jako ma okno (framebuffer)
 */

SDL_Surface *MIR_LoadImage(const char *filename, int alpha)
{
	SDL_Surface *tmp;// Pomocny
	SDL_Surface *ret;// Bude vracen

	if((tmp = IMG_Load(filename)) == NULL)// Prilinkovat SDL_image
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		return NULL;
	}

	if((ret = (alpha) ? SDL_DisplayFormatAlpha(tmp)
			: SDL_DisplayFormat(tmp)) == NULL)
	{
		fprintf(stderr, "%s\n", SDL_GetError());
		SDL_FreeSurface(tmp);
		return NULL;
	}

	SDL_FreeSurface(tmp);// Uz neni potreba

	return ret;
}




//==============================================================================
int Nacti_obrazky_vesmir()
//==============================================================================
{
	fg_color.r=255; 
	fg_color.g=255; 
	fg_color.b=255;

	space  	= MIR_LoadImage(ROOT"images/space.png", 1); 
	
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


	damage = MIR_LoadImage(ROOT"images/system/poskozeni.png", 1); 
	speed = MIR_LoadImage(ROOT"images/system/rychlost.png", 1); 
	position_x = MIR_LoadImage(ROOT"images/system/poloha_x.png", 1); 
	position_y = MIR_LoadImage(ROOT"images/system/poloha_y.png", 1); 
	position_ptr_x = MIR_LoadImage(ROOT"images/system/ptr.png", 1); 
	position_ptr_y = MIR_LoadImage(ROOT"images/system/ptr_y.png", 1); 

	CENTER = MIR_LoadImage(ROOT"images/center_2.png", 1); 


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
	
	 return FAIL;
}






//==============================================================================
int Nacti_obrazky_menu()
//==============================================================================
{
	bg_img   	= MIR_LoadImage(ROOT"images/bg.png", 1); 
	bg_nastaveni	= MIR_LoadImage(ROOT"images/bg_nastaveni.jpg", 1); 
	//tlacitko 	= MIR_LoadImage(ROOT"images/tlacitko.png", 1); 
	//policko  	= MIR_LoadImage(ROOT"images/policko.png", 1); 
	//policko1  	= MIR_LoadImage(ROOT"images/policko-1.png", 1); 
	
	if (bg_img != NULL && 
		bg_nastaveni != NULL)
		return OK;
	
	 return FAIL;
}



//==============================================================================
int Uklid_obrazky_menu()
//==============================================================================
{
	if(bg_img!=NULL) SDL_FreeSurface(bg_img);
	if(bg_nastaveni!=NULL) SDL_FreeSurface(bg_nastaveni);
	//if(tlacitko!=NULL) SDL_FreeSurface(tlacitko);
	//if(policko!=NULL) SDL_FreeSurface(policko);
	//if(policko1!=NULL) SDL_FreeSurface(policko1);
		
	return OK;
}


//==============================================================================
int Uklid_obrazky_vesmir()
//==============================================================================
{
	if(lod!=NULL) SDL_FreeSurface(lod);
	if(space!=NULL) SDL_FreeSurface(space);
	if(laser!=NULL) SDL_FreeSurface(laser);
	if(radar!=NULL) SDL_FreeSurface(radar);	
	if(position_x!=NULL) SDL_FreeSurface(position_x);	
	if(position_y!=NULL) SDL_FreeSurface(position_y);	
	if(position_ptr_x!=NULL) SDL_FreeSurface(position_ptr_x);	
	if(position_ptr_y!=NULL) SDL_FreeSurface(position_ptr_y);	
	
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
