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
	float acceleration;

	int manevr;
	float shift;
	int MAX_shift;

	int health;
	int MAX_health;
	
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
// SERVER TIME INTERVAL = 20 ms

T_ship SHIP_RED_RX = {
   .MAX_health 			= 120,	
   .MAX_speed 			= 8.00,
   .MAX_shift 			= 5.00,
   .MAX_acceleration 	= 0.2,
   .MAX_manevr= 1.0,
   .alive = 1,
};

T_ship SHIP_BLUE_RX = {
   .MAX_health = 70,	
   .MAX_speed 	= 10.00,
   .MAX_shift 	= 5.00,
   .MAX_acceleration = 0.3,
   .MAX_manevr 	= 2.0,
   .alive = 1,
};

// =============================================================================

/*
T_ship SHIP_RED_RX = {
   .MAX_health 			= 100,	
   .MAX_speed 			= 5.50,
   .MAX_shift 			= 5.00,
   .MAX_acceleration 	= 0.1,
   .MAX_manevr= 0.1,
   .alive = 1,
};
// =============================================================================
// LOD_RED_RX

T_ship SHIP_RED_RX = {
   .MAX_health = 100,	
   .MAX_speed 	= 0.50,
   .MAX_shift 	= 0.25,
   .acceleration 	= 0.001,
   .manevr 	= 0.10,
   .alive = 1,
};

// =============================================================================
T_ship SHIP_BLUE_RX = {
   .MAX_health = 70,	
   .MAX_speed 	= 2.70,
   .MAX_shift 	= 5.00,
   .MAX_acceleration = 0.02,
   .MAX_manevr 	= 0.1,
   .alive = 1,
};
*/


#endif
