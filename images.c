#include "program.h"
#include "images.h"
#include "lod.h"




/*
 * Funkce se pokusi nahrat obrazek ze souboru a zkonvertovat ho
 * na stejny pixel format, jako ma okno (framebuffer)
 */

SDL_Surface *LoadImage(const char *filename, int alpha)
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
	space  	= LoadImage(ROOT"images/space.png", 1); 
	
	lode[0].lod	= LoadImage(ROOT"images/l3.png", 1); // Moje lod
	lode[1].lod	= LoadImage(ROOT"images/l2.png", 1); // Cizi lod
	
	laser = LoadImage(ROOT"images/RED/laser.png", 1); 
	raketa = LoadImage(ROOT"images/r1.png", 1); 
	
	radar = LoadImage(ROOT"images/system/mapa.png", 1); 
	damage = LoadImage(ROOT"images/system/poskozeni.png", 1); 
	speed = LoadImage(ROOT"images/system/rychlost.png", 1); 
	position_x = LoadImage(ROOT"images/system/poloha_x.png", 1); 
	position_y = LoadImage(ROOT"images/system/poloha_y.png", 1); 
	position_ptr_x = LoadImage(ROOT"images/system/ptr.png", 1); 
	position_ptr_y = LoadImage(ROOT"images/system/ptr_y.png", 1); 
	
	if (space 		!= NULL && 
		lode[0].lod	!= NULL &&
		lode[1].lod	!= NULL &&
		laser 		!= NULL	&&
		radar 		!= NULL	&&
		damage 		!= NULL	&&
		position_x 	!= NULL	&&
		position_y 	!= NULL	&&
		position_ptr_x 	!= NULL	&&
		position_ptr_y 	!= NULL	&&
		speed 		!= NULL	
		)
		return OK;
	
	 return FAIL;
}






//==============================================================================
int Nacti_obrazky_menu()
//==============================================================================
{
	bg_img   	= LoadImage(ROOT"images/bg.png", 1); 
	bg_nastaveni	= LoadImage(ROOT"images/bg_nastaveni.jpg", 1); 
	//tlacitko 	= LoadImage(ROOT"images/tlacitko.png", 1); 
	//policko  	= LoadImage(ROOT"images/policko.png", 1); 
	//policko1  	= LoadImage(ROOT"images/policko-1.png", 1); 
	
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
