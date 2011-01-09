/*
 * File name: menu.c
 * Date:      2010/09/19 13:06
 * Author:    
 */

//==============================================================================
#include "program.h"
#include "images.h"
#include "menu.h"
#include <stdlib.h>

//==============================================================================
int Menu(){

  SDL_Event event;
  Uint8* keys;	

  Uint8 quit= 0;

  if(Load_menu_images() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");


  menu_button[0] = menu_logo;

  menu_button[1] = menu_connect_button;
  menu_button[2] = menu_settings_button;
  menu_button[3] = menu_exit_button;

  // ==== MENU LOOP ====
  while(!quit){

		// === Primy pristup ke klavesnici ===
		while(SDL_PollEvent(&event)){
           switch(event.type){

              case SDL_KEYDOWN:       
              switch(event.key.keysym.sym){
             
             	case SDLK_ESCAPE:
                 	exit(0);               
                 	break;
				
             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
                 	quit = 1;
                 	break;

             	case SDLK_2:
             	case SDLK_KP2:
                 	POINT(2);
                 	break;
				
				default:
					break;
				}
			}
		}


	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);


	Draw_menu();
	//printf("X");
 
  }
  
  return OK;
}
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================
//==============================================================================

/* end of menu.c */
