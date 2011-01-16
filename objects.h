// OBJECTS functions


#ifndef __OBJECTS_H_
  #define __OBJECTS_H_

#include "program.h"

//==============================================================================
// PROTOTYPES
//==============================================================================
int Create_object(int faction, int type, int model);

//==============================================================================
// DATA TYPES
//==============================================================================

// Generic structure for ALL types of objects(weapons, ships, asteroids ..)
typedef struct str_object {
  Uint8 faction;

  Uint8 type;
  Uint8 model;

  Sint32 X; 
  Sint32 Y;

  Uint8 alive;
  Uint16 ttl;            // Time To Live


  SDL_Surface *img;      // img of ship
  SDL_Surface *img_m;		 // img of ship on move
  SDL_Surface *img_c;		 // img of ship crap
  SDL_Surface *rot_img;	 // img ->angle rotated 


  Uint8 turbo;

  float speed;
  float MAX_speed;

  float acceleration;
	float MAX_acceleration;
  
  float manevr;
  float MAX_manevr;

  float angle;
  float angle2;
  
  float shift;
  float MAX_shift;

  int health;
  int MAX_health;

	// weapons
  int wp_1;
  int wp_2;
  int wp_3;

  int MAX_wp_1;
  int MAX_wp_2;
  int MAX_wp_3;

  int damage;

} T_object;



//==============================================================================
// GLOBAL variables
//==============================================================================
#define MAX_OBJECTS 1024
  
  static T_object object[MAX_OBJECTS];

  T_object *my_ship;


#endif 
