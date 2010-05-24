#ifndef SHIPS_H
 #define SHIPS_H

#include "lod.h"



/*
typedef struct str_lod {
	SDL_Surface *lod;
	char strana;
	
	float rychlost;
	int MAX_rychlost;
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
   .MAX_rychlost = 5,
   .zrychleni = 0.1,
   .manevr = 5,
};


#endif
