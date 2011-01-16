

#ifndef __ASTEROIDS_H_
  #define __ASTEROIDS_H_

#include "objects.h"

//==============================================================================
// OBJECTS definitions
//==============================================================================


T_object Asteroid_X1 = {
  .descriptor = NATURE,
  .type = ASTEROID,
  .speed = 0.2,
  .damage = 30,
  .health=  30,
  .alive = 1,
  .destroyed = 0,
  .ttl = 0,

};


T_object Asteroid_X2 = {
  .descriptor = NATURE,
  .type = ASTEROID,
  .speed = 0.1,
  .damage = 130,
  .health= 130,
  .alive = 1,
  .destroyed = 0,
  .ttl = 0,

};




//==============================================================================
#endif 
