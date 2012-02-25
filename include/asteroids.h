

#ifndef __ASTEROIDS_H_
  #define __ASTEROIDS_H_

#include "objects.h"

//==============================================================================
// OBJECTS definitions
//==============================================================================


T_object Asteroid_X1 = {
  .descriptor = NATURE,
  .type = ASTEROID,
  .model = 1,
  .speed = 0,
  .damage = 30,
  .health=  59,
  .alive = 1,
  .destroyed = 0,
  .ttl = 0,

};


T_object Asteroid_X2 = {
  .descriptor = NATURE,
  .type = ASTEROID,
  .model = 2,
  .speed = 0,
  .damage = 130,
  .health= 129,
  .alive = 1,
  .destroyed = 0,
  .ttl = 0,

};




//==============================================================================
#endif 
