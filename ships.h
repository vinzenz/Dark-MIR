#ifndef __SHIPS_H_
  #define __SHIPS_H_

#include "lod.h"
#include "objects.h"
#include "images.h"



#define RED_RX_TYPE  1
#define RED_EX_TYPE  2

#define BLUE_RX_TYPE  32

// SERVER TIME INTERVAL = 20 ms


// LIGHT BATTLE FIGHTER / SCOUT
T_object SHIP_RED_RX = {
   .MAX_health 			= 120,	
   .MAX_speed 			= 5.00,
   .MAX_shift 			= 10.00,
   .MAX_acceleration 	= 0.3,
   .MAX_manevr= 2.0,

   .MAX_wp_1	= 150,
   //.MAX_wp_2	= 8,
   .MAX_wp_2	= 80,
   .MAX_wp_3	= 2,
   .alive 	= 1,
};

// HEAVY BATTLE FIGHTER 
T_object SHIP_RED_EX = {
   .MAX_health 			= 240,	
   .MAX_speed 			= 14.00,
   .MAX_shift 			= 5.00,
   .MAX_acceleration 	= 0.2,
   .MAX_manevr= 2.0,

   .MAX_wp_1= 300,
   .MAX_wp_2= 30,
   .MAX_wp_2= 10,
   .alive = 1,
};

// LIGHT BATTLE FIGHTER / SCOUT
T_object SHIP_BLUE_RX = {
   .MAX_health = 90,	
   .MAX_speed 	= 7.00,
   .MAX_shift 	= 10.00,
   .MAX_acceleration = 0.3,
   .MAX_manevr 	= 2.5,

   .MAX_wp_1= 100,
   .MAX_wp_2= 20,
   .MAX_wp_3= 2,
   .alive = 1,
};

T_object SHIP_GREEN_ZX = {
   .MAX_health = 40,	
   .MAX_speed 	= 20.00,
   .MAX_shift 	= 15.00,
   .MAX_acceleration = 0.5,
   .MAX_manevr 	= 3.0,

   .MAX_wp_1= 100,
   .MAX_wp_2= 0,
   .alive = 1,
};


// =============================================================================

/*
T_object SHIP_RED_RX = {
   .MAX_health 			= 100,	
   .MAX_speed 			= 5.50,
   .MAX_shift 			= 5.00,
   .MAX_acceleration 	= 0.1,
   .MAX_manevr= 0.1,
   .alive = 1,
};
// =============================================================================
// LOD_RED_RX

T_object SHIP_RED_RX = {
   .MAX_health = 100,	
   .MAX_speed 	= 0.50,
   .MAX_shift 	= 0.25,
   .acceleration 	= 0.001,
   .manevr 	= 0.10,
   .alive = 1,
};

// =============================================================================
T_object SHIP_BLUE_RX = {
   .MAX_health = 70,	
   .MAX_speed 	= 2.70,
   .MAX_shift 	= 5.00,
   .MAX_acceleration = 0.02,
   .MAX_manevr 	= 0.1,
   .alive = 1,
};
*/


#endif
