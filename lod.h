#ifndef LOD_H
 #define LOD_H

#include "program.h"

#define MAX_LODI 40


#define LOD_RX_speed 4;
#define LOD_RX_angle 10;



//struct st


  typedef struct str_ship {
	SDL_Surface *img;		// img of ship
	SDL_Surface *img_m;		// img of ship on move
	SDL_Surface *img_c;		// img of ship crap
	SDL_Surface *rot_img;		// img ->angle rotated 
	char strana;
	
	float speed;
	float MAX_speed;
	float zrychleni;

	float manevr;
	float angle;
	float angle2;

	float uhyb;
	float MAX_uhyb;

	int poskozeni;
	int MAX_poskozeni;

	float X; 			//  position
	float Y;

	int alive;	
		
  } T_ship;
/*
  typedef struct str_weapon {
	SDL_Surface *lod;
	char strana;
	
	float speed;
	float MAX_speed;
	float acceleration;

	int delta_angle;
	int angle;

	int poskozeni;
	int MAX_damage;
	
	float X; //  pozice
	float Y;
	int x;   // rect vykreslovaci pozice
	int y;
	
		
  } T_weapon;
*/

  T_ship lode[MAX_LODI];
  T_ship *my_ship;



// 	lode[0]  je lod lokalniho hrace



  int pocet_lodi;


// Function Prototypes  
// =============================================================================

  int Vystrel(int zbran, T_ship *ship);
  Uint32 Ovladani(Uint32 interval, void *param);

// =============================================================================
  SDL_Surface *roto_lod;
  SDL_Surface *rlod;
  int uhel;
  int uhel2;

  //float speed;
  int MAX_speed;
  float zrychleni;

  float manevr;
  float uhyb;
  int MAX_uhyb;

  int poskozeni;
  int MAX_poskozeni;

#endif
