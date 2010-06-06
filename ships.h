#ifndef SHIPS_H
 #define SHIPS_H

#include "lod.h"
#include "images.h"


/*
typedef struct str_lod {
	SDL_Surface *lod;
	char strana;
	
	float speed;
	int MAX_speed;
	float zrychleni;

	int manevr;
	float uhyb;
	int MAX_uhyb;

	int poskozeni;
	int MAX_poskozeni;
	
	float X; //  pozice
	float Y;
	int sX;	 // pocatecni pozice
	int sY;
	int x;   // rect vykreslovaci pozice
	int y;
	int uhel;
	
		
} T_ship;

T_ship lode[MAX_LODI];

*/
T_ship SHIP_RED_RX = {
   .MAX_poskozeni = 100,	
   .MAX_speed 	= 1.50,
   .MAX_uhyb 	= 50.00,
   .zrychleni 	= 0.1,
   .manevr 	= 2.00,
   .alive = 1,
};
// =============================================================================
/*
// LOD_RED_RX

T_ship SHIP_RED_RX = {
   .MAX_poskozeni = 100,	
   .MAX_speed 	= 0.50,
   .MAX_uhyb 	= 0.25,
   .zrychleni 	= 0.001,
   .manevr 	= 0.10,
   .alive = 1,
};

// =============================================================================
*/
T_ship SHIP_BLUE_RX = {
   .MAX_poskozeni = 70,	
   .MAX_speed 	= 0.70,
   .MAX_uhyb 	= 0.30,
   .zrychleni 	= 0.02,
   .manevr 	= 3.0,
   .alive = 1,
};


#endif
