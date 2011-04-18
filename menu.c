/*
 * File name: menu.c
 * Date:      2010/09/19 13:06
 * Author:    
 */

//==============================================================================
#include "program.h"
#include "images.h"
#include "menu.h"
#include "client.h"
#include "faction.h"

//==============================================================================
int Menu(){
//==============================================================================

  SDL_Event event;
  Uint8* keys;	

  Uint8 quit= 0;

  if(Load_menu_images() == FAIL){
		ERROR("some images missing ... ignore");
  }


  // ==== MENU LOOP ====
  while(!quit){

  menu_button[0] = menu_logo;

  menu_button[1] = menu_connect_button;
  menu_button[2] = menu_settings_button;
  menu_button[3] = menu_help_button;
  menu_button[4] = menu_exit_button;

  Message(" > _ ");
		// === Primy pristup ke klavesnici ===
		while(SDL_PollEvent(&event)){
           switch(event.type){

              case SDL_KEYDOWN:       
              switch(event.key.keysym.sym){
             
             	case SDLK_ESCAPE:
                 	Exit_game(0);               
                 	break;
				
             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
                 	Connect();
                 	break;

             	case SDLK_2:
             	case SDLK_KP2:
                 	POINT(2);
                  Configure();
                 	break;

             	case SDLK_3:
             	case SDLK_KP3:
                 	POINT(3);
                  Help();
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
int Configure(){
//==============================================================================

  SDL_Event event;
  Uint8* keys;	

  Uint8 quit= 0;

  if(Load_menu_images() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");

  bzero(item, sizeof(menu_item)*MAX_ITEMS);

  item[0].img_p = settings_bg;
  item[0].alive = 1;
  item[0].active = 0;
  item[0].x = 0;
  item[0].y = 0;

  item[1].img_p = menu_logo_small;
  item[1].alive = 1;
  item[1].active = 0;
  item[1].x = 50;
  item[1].y = 20;

  item[2].img_p = switch_off_img;
  item[2].img_a = switch_on_img;
  item[2].alive = 1;
  item[2].active = 1;
  item[2].x = 170;
  item[2].y = 200;

  item[3].img_p = switch_off_img;
  item[3].img_a = switch_on_img;
  item[3].alive = 1;
  item[3].active = 0;
  item[3].x = 170;
  item[3].y = 230;

  item[4].img_p = switch_off_img;
  item[4].img_a = switch_on_img;
  item[4].alive = 1;
  item[4].active = 0;
  item[4].x = 170;
  item[4].y = 260;

  item[5].img_p = switch_off_img;
  item[5].img_a = switch_on_img;
  item[5].alive = 1;
  item[5].active = 0;
  item[5].x = 170;
  item[5].y = 290;

  item[6].img_p = switch_off_img;
  item[6].img_a = switch_on_img;
  item[6].alive = 1;
  item[6].active = 0;
  item[6].x = 170;
  item[6].y = 320;

  item[7].img_p = switch_off_img;
  item[7].img_a = switch_on_img;
  item[7].alive = 0;
  item[7].active = 0;
  item[7].x = 170;
  item[7].y = 350;


  //for(int i = 0; i < CONFIG_ITEMS_MAX; i++){
  strcpy(configure_list[0], " [ 0 ] resolution 800x600");
  strcpy(configure_list[1], " [ 1 ] resolution 1024x768");
  strcpy(configure_list[2], " [ 2 ] resolution 1280x1024");
  strcpy(configure_list[3], " [ 3 ] resolution 1280x800");
  strcpy(configure_list[4], " [ 4 ] resolution 1440x900");


  // ==== MENU LOOP ====
  while(!quit){

		// === Primy pristup ke klavesnici ===
		while(SDL_PollEvent(&event)){
           switch(event.type){

              case SDL_KEYDOWN:       
              switch(event.key.keysym.sym){
             
             	case SDLK_ESCAPE:
                 	quit = 1;
                 	break;
				
             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
                  Zmena_rozliseni(1);
                 	break;

             	case SDLK_2:
             	case SDLK_KP2:
                  Zmena_rozliseni(2);
                 	POINT(2);
                 	break;

             	case SDLK_3:
             	case SDLK_KP3:
                  Zmena_rozliseni(3);
                 	POINT(3);
                 	break;

             	case SDLK_4:
             	case SDLK_KP4:
                  Zmena_rozliseni(4);
                 	POINT(4);
                 	break;
				
				default:
					break;
				}
			}
		}


	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);


	//Draw_menu();
	Draw_configure();
	//printf("X");
 
  }
  
  return OK;
}
//==============================================================================
//==============================================================================
int Connect(){
//==============================================================================

  SDL_Event event;
  Uint8* keys;	

  int quit= 0;
  int rc = 0;  // return code

  if(Load_menu_images() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");


  menu_button[0] = menu_logo_small;

  menu_button[1] = NULL;
  menu_button[2] = NULL;
  menu_button[3] = NULL;
  menu_button[4] = menu_exit_button;


  Load_server_list();
  FACTION = RED;

  // ==== MENU LOOP ====
  while(!quit){

		// === Primy pristup ke klavesnici ===
		while(SDL_PollEvent(&event)){
           switch(event.type){

              case SDL_KEYDOWN:       
              switch(event.key.keysym.sym){
             
             	case SDLK_ESCAPE:
                  quit = 1;
                 	break;
				
             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
                  Message("Connecting to  ... [  1  ] ");
                  Draw_connect();
	                rc = Connect2server(server_list[1]);
                  if(rc == FAIL){
                    Message("SERVER NOT RESPONDING");
                  }else
                    Game_loop();
                 	break;

             	case SDLK_2:
             	case SDLK_KP2:
                 	POINT(2);
                  Message("Connecting to  ... [  2  ] ");
                  Draw_connect();
	                rc = Connect2server(server_list[2]);
                  if(rc == FAIL){
                    Message("SERVER NOT RESPONDING");
                  }else 
                    Game_loop();
                 	break;

             	case SDLK_3:
             	case SDLK_KP3:
                 	POINT(3);
                  Message("Connecting to  ... [  3  ] ");
                  Draw_connect();
	                rc = Connect2server(server_list[3]);
                  if(rc == FAIL){
                    Message("SERVER NOT RESPONDING");
                  }else
                    Game_loop();
                 	break;

             	case SDLK_4:
             	case SDLK_KP4:
                 	POINT(4);
                  Message("Connecting to  ... [  4  ] ");
                  Draw_connect();
	                rc = Connect2server(server_list[4]);
                  if(rc == FAIL){
                    Message("SERVER NOT RESPONDING");
                  }else
                    Game_loop();
                 	break;

             	case SDLK_r:
                 FACTION = RED;
                 Message("[ SOCIALISTS ]   s e l e c t e d");
                 break ;

             	case SDLK_b:
                 FACTION = BLUE;
                 Message("[ IMPERIALISTS ]   s e l e c t e d");
                 break;
				
				default:
					break;
				}
			}
		}


	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);


	Draw_connect();
	//printf("X");
 
  }
  
  return OK;
}
//==============================================================================
int Help(){
//==============================================================================

  // Shows keybord layout



  // Press the key, to view assigned action

  SDL_Event event;
  Uint8* keys;	

  Uint8 quit= 0;

  if(Load_menu_images() == FAIL){
		ERROR("some images missing ... ignore");
  }


  bzero(item, sizeof(menu_item)*MAX_ITEMS);

  item[0].img_p = help_bg;
  item[0].alive = 1;
  item[0].active = 0;
  item[0].x = 0;
  item[0].y = 0;

  item[1].img_p = menu_logo_small;
  item[1].alive = 1;
  item[1].active = 0;
  item[1].x = 50;
  item[1].y = 20;


  item[2].img_p = keyboard_img;
  item[2].alive = 1;
  item[2].active = 0;
  item[2].x = 200;
  item[2].y = 100;


  

  // ==== MENU LOOP ====
  while(!quit){

    Message(" > _ ");

		// === Primy pristup ke klavesnici ===
		while(SDL_PollEvent(&event)){
           switch(event.type){

              case SDL_KEYDOWN:       
              switch(event.key.keysym.sym){
             
             	case SDLK_ESCAPE:
                 	quit = 1;
                 	break;
				
             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
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


	Draw_help();
	//printf("X");
 
  }
  
  return OK;
}

//==============================================================================
int Message(const char *msg){

  strncpy(status_line, msg, 255);

  return OK;
}
//==============================================================================
//==============================================================================
/* end of menu.c */
