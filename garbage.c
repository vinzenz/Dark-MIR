// GARBAGE COLLECTING

#include "program.h"
#include "client.h"


// === DESTRUCTOR === 
//==============================================================================
int Exit_game(int RC){
//==============================================================================
// RC = return code

  DEBUG("Garbage collector starting");

  TTF_Quit();
  SDL_Quit();

  DEBUG("Exiting program");
  exit(RC);
}
//==============================================================================
// EOF
