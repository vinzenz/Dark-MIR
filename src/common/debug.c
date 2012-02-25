


//==============================================================================
//==============================================================================

#include "program.h"
#include "objects.h"

//==============================================================================
void Examine_object(T_object *obj){
//==============================================================================
  DEBUG("------------------------------------------------------------");

  int i;

  for(i = 0; i < MAX_OBJECTS; i++){
    if(obj == &object[i]) break; 

  }
    
    fprintf(D_OUT,  " ID[ %4d ] D: %02X T: %02X  M: %02X F: %d alive: %d\n",
       i, object[i].descriptor, object[i].type, object[i].model, object[i].faction,
       object[i].alive);
    fprintf(D_OUT,  "           X: %6d Y: %6d        H: %4d\n", 
                object[i].X, object[i].Y, object[i].health);
    fprintf(D_OUT,  "           img: %8x img_m: %8x  img_c: %8x \n",
                object[i].img, object[i].img_m, object[i].img_c);


  DEBUG("------------------------------------------------------------");
  return;
}
//==============================================================================
void Examine_objects(){
//==============================================================================
  DEBUG("------------------------------------------------------------");

  int i;
  //for(i = 0; i < MAX_OBJECTS; i++){
  for(i = 0; i < 10; i++){

    if(! object[i].alive) continue;
    
    fprintf(D_OUT,  " [ %4d ] D: %02X T: %02X  M: %02X \n",
       i, object[i].descriptor, object[i].type, object[i].model);

  }

  DEBUG("------------------------------------------------------------");
  return;
}
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
