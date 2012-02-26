// GARBAGE COLLECTING

#include "program.h"
#include "client.h"


// === DESTRUCTOR === 
//==============================================================================
int Exit_game(int RC){
//==============================================================================
// RC = return code

  MIR_LOG_DEBUG("Garbage collector starting");

  TTF_Quit();
  SDL_Quit();

  MIR_LOG_DEBUG("Exiting program");
  exit(RC);
}
//==============================================================================
// EOF
