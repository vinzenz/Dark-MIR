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



// LOD_RED_RX

T_ship SHIP_RED_RX = {
   .MAX_poskozeni = 100,	
   .MAX_speed = 3,
   .MAX_uhyb = 1.5,
   .zrychleni = 0.5,
   .manevr = 5,
   .alive = 1,
};
// =============================================================================
//
T_ship SHIP_BLUE_RX = {
   .MAX_poskozeni = 70,	
   .MAX_speed = 4,
   .MAX_uhyb = 2,
   .zrychleni = 0.2,
   .manevr = 5,
   .alive = 1,
};


#endif
