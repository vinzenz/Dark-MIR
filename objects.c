// OBJECTS functions

#include "program.h"
#include "server.h"
#include "objects.h"
#include "faction.h"
#include "images.h"
#include "vesmir.h"
#include "lod.h"

#include "ships.h"
#include "asteroids.h"
#include "zbrane.h"
#include "weapons.h"

//==============================================================================
// PROTOTYPES
//==============================================================================
extern T_object Asteroid_X1;
extern T_object Asteroid_X2;

//==============================================================================
//==============================================================================
int Initialize_objects(int ARG){
//==============================================================================
int CLIENT = ARG;  // (1)
int SERVER = !ARG; // (0)

	// Specifika lodi	
	// ====================
	SHIP_RED_RX.faction = RED;
	SHIP_RED_EX.faction = RED;
	SHIP_BLUE_RX.faction = BLUE;
	SHIP_GREEN_ZX.faction = GREEN;

if(CLIENT){
	SHIP_RED_RX.img = IMG_RED_RX;
	SHIP_RED_RX.img_m = IMG_RED_RX_move;
	SHIP_RED_RX.img_c = IMG_RED_RX_crap;

	SHIP_RED_EX.img = IMG_RED_EX;
	SHIP_RED_EX.img_m = IMG_RED_EX_move;
	SHIP_RED_EX.img_c = IMG_RED_EX_crap;

	SHIP_BLUE_RX.img = IMG_BLUE_RX;
	SHIP_BLUE_RX.img_m = IMG_BLUE_RX_move;
	SHIP_BLUE_RX.img_c = IMG_BLUE_RX_crap;

	SHIP_GREEN_ZX.img = IMG_GREEN_ZX;
	SHIP_GREEN_ZX.img_m = IMG_GREEN_ZX_move;
	SHIP_GREEN_ZX.img_c = IMG_GREEN_ZX_crap;

  Asteroid_X1.img =  asteroid1;
  Asteroid_X2.img =  asteroid2;

	//ship[0] = SHIP_RED_RX;
	//ship[0] = SHIP_BLUE_RX;

	object[0] = SHIP_RED_RX;
	object[0].alive = 1;

  printf("MY ID %3d\n", ID);
	my_ship = &object[ID];	

  if(FACTION == RED)
    *my_ship = SHIP_RED_RX;
  else 
    if (FACTION == BLUE)
      *my_ship = SHIP_BLUE_RX;
    else
      *my_ship = SHIP_GREEN_ZX;
}

// ----------------------------------------------------------------------------
if(SERVER){

  srand(SEED);

  for(int i=0; i < MAX_PLAYERS; i++){
    player[i].ship = SHIP_RED_RX;

    player[i].ship.X = (MAX_X/2) + (i * 200);
    player[i].ship.Y = (MAX_Y/2) + (i * 200);
    player[i].ship.health = player[i].ship.MAX_health;
    player[i].ship.speed  = 0.0;
    player[i].ship.angle  = 0;
    player[i].ship.manevr = 0;
    player[i].ship.shift  = 0;
    player[i].ship.wp_1   = player[i].ship.MAX_wp_1;
    //printf("WP1: %d\n", player[i].ship.wp_1);
    player[i].ship.wp_2   = player[i].ship.MAX_wp_2;
    player[i].ship.wp_3   = player[i].ship.MAX_wp_3;
    player[i].ship.acceleration = 0;
    player[i].ship.alive  = 1;
  }

  players = 0;


  // --- Objects --------------------------------------------------------------

  int pos_x;
  int pos_y;

  // Asteroids randomly 
  for(int i = 0; i < 20; i++){
    pos_x = rand() % MAX_X;
    pos_y = rand() % MAX_Y;
    Create_object(NATURE, ASTEROID, 2, pos_x, pos_y  );
  }

  // Asteroid field
  for(int i = 0; i < 60; i++){
    pos_x = (rand() % 2000) + 2000;
    pos_y = (rand() % 2000) + 2000;
    Create_object(NATURE, ASTEROID, 1, pos_x, pos_y  );
  }

}
// ----------------------------------------------------------------------------



  return OK;
}



//==============================================================================
//==============================================================================
int Create_object( int descriptor, int type, int model, int X, int Y){
//==============================================================================
  
 int i= -1;

  

  // === Select type ===
  // ------------------------------------------------------------
  if(descriptor == WEAPON){
    //object[i].faction = RED;
      // Find_slot();
    for(i = WP; i < NT; i++){
      if(! object[i].alive) break;
    }
    if(i >= MAX_OBJECTS - 1) return FAIL;

    switch(type){

      case LASER:
        object[i] = RX_laser;
        break;
      case ROCKET:
        object[i] = RX_R1;
        break;
      case MICRO_MISSILE:
        object[i] = RX_M1;
        break;
      case GUIDED_MISSILE:
        object[i] = RX_M2;
        break;
      default:
       DEBUG("OBJECT IS NOT IMPLEMENTED");
    }
  }
  // ------------------------------------------------------------
  if(descriptor == NATURE){
    // Find_slot();
    for(i = NT; i < MAX_OBJECTS; i++){
      if(! object[i].alive) break;
    }
    if(i >= MAX_OBJECTS - 1) return FAIL;

    object[i].faction = NEUTRAL;

    if(type == ASTEROID){

      switch(model){
    
        case 0:
        case 1:
            object[i] = Asteroid_X1;
            break;
        case 2:
            object[i] = Asteroid_X2;
            break;

        default: 
            object[i] = Asteroid_X2;
      }


    }
  } // END NATURE

  object[i].X = X;
  object[i].Y = Y;

  object[i].alive =     1;
  object[i].destroyed = 0;

  fprintf(D_OUT, "AST x: %4d y: %4d\n", X, Y);
  return i;
  // returning ID of created object
  // negative value is returned in case of failure
}
//==============================================================================
// EOF
