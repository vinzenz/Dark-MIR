#ifndef LOD_H
 #define LOD_H

#include "program.h"

#define MAX_LODI 40


#define LOD_RX_speed 4;
#define LOD_RX_angle 10;



//struct st


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
  T_ship *my_ship;



// 	lode[0]  je lod lokalniho hrace






// Function Prototypes  
// =============================================================================

  int Vystrel(int zbran, T_ship *ship);
  Uint32 Ovladani(Uint32 interval, void *param);

// =============================================================================
  SDL_Surface *roto_lod;
  SDL_Surface *rlod;
  int uhel;
  int uhel2;

  float rychlost;
  int MAX_rychlost;
  float zrychleni;

  int manevr;
  float uhyb;
  int MAX_uhyb;

  int poskozeni;
  int MAX_poskozeni;

#endif
