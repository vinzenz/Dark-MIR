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
char *Scan_input(char *);


//==============================================================================
char *Scan_input(char *output){
//==============================================================================

  //sleep(1);

  SDL_Event event;
  Uint8* keys;	
  SDLKey key_pressed;

  Uint8 quit= 0;
  int index = 0;

  // ==== MENU LOOP ====
  while(!quit){

		// === Primy pristup ke klavesnici ===
		while(SDL_PollEvent(&event)){
           switch(event.type){

              case SDL_KEYDOWN:       

              switch(event.key.keysym.sym){
             
             	  case SDLK_ESCAPE:
               	case SDLK_RETURN:
                 	quit = 1;
                 	break;
				
               	case SDLK_BACKSPACE:
               	case SDLK_DELETE:
                  output[index] =  '\0';
                  index--;
                  if(index < 0) index = 0;
                  break;

				        case SDLK_LEFT:
                  index--;
                  if(index < 0) index = 0;
                  break;

				        case SDLK_RIGHT:
                  index++;
                  if(index >= NICKNAME_MAX - 2) index = NICKNAME_MAX - 2;
                  break;

				       default:
                  key_pressed  = event.key.keysym.sym;
                 
                  output[index] =  (char) key_pressed;
                  index++;
                  break;    

			      	}

				default:
				  break;
			}
		}


  	
	  SDL_PumpEvents();
	  keys = SDL_GetKeyState(NULL);
  }

  
  //output[index] = '\0';
  return output;
}
//==============================================================================
Uint32 Redraw_configure_loop(Uint32 interval, void *param){
//==============================================================================

//  printf("TIMER: Redraw_loop()\n");
  //draw_timer = SDL_AddTimer(20, Redraw_loop, NULL);   // MOVE

  Draw_configure();

 return interval;
}
//==============================================================================
Uint32 Redraw_player_menu_loop(Uint32 interval, void *param){
//==============================================================================

//  printf("TIMER: Redraw_loop()\n");

  Draw_player_menu();

 return interval;
}

//==============================================================================
int Menu(){
//==============================================================================

  SDL_Event event;
  Uint8* keys;	

  Uint8 quit= 0;

  if(Load_menu_images() == FAIL){
		MIR_LOG_ERROR("some images missing ... ignore");
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
				
             	case SDLK_9:
             	case SDLK_KP9:
                 	POINT(9);
                  Player_menu();
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

  SDL_TimerID draw_timer = NULL;
  SDL_Event event;
  Uint8* keys;	

	draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL); 				// DRAW


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

 // ------------------------------------------------------------
  item[2].img_p = switch_off_img;
  item[2].img_a = switch_on_img;
  item[2].alive = 1;
  item[2].active = 0;
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
  item[7].alive = 1;
  item[7].active = 0;
  item[7].x = 170;
  item[7].y = 350;

  // ------------------------------------------------------------
  item[2+nastavene_rozliseni].active = 1;
  // ------------------------------------------------------------

  item[20].img_p = switch_off_img;
  item[20].img_a = switch_on_img;
  item[20].alive = 1;
  item[20].active = 0;
  item[20].x = 170;
  item[20].y = 410;

  // ------------------------------------------------------------

  item[9].img_p = switch_off_img;
  item[9].img_a = switch_on_img;
  item[9].alive = 1;
  item[9].active = 0;
  item[9].x = 170;
  item[9].y = 470;

  item[9].active = F;
  // ------------------------------------------------------------
  //for(int i = 0; i < CONFIG_ITEMS_MAX; i++){
  strcpy(configure_list[0], " [ 0 ] resolution 800x600");
  strcpy(configure_list[1], " [ 1 ] resolution 1024x768");
  strcpy(configure_list[2], " [ 2 ] resolution 1280x1024");
  strcpy(configure_list[3], " [ 3 ] resolution 1280x800");
  strcpy(configure_list[4], " [ 4 ] resolution 1440x900");
  strcpy(configure_list[5], " [ 5 ] resolution 1366x768");


  strcpy(configure_list[7], " [ N ] nickname > ");


  strcpy(configure_list[9], " [ F12 ] Full Screen");






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
				
             	case SDLK_0:
             	case SDLK_KP0:
                 	POINT(0);
                  Zmena_rozliseni(0);
                  item[1+1].active = 1;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
                  Zmena_rozliseni(1);
                  item[1+1].active = 0;
                  item[1+2].active = 1;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_2:
             	case SDLK_KP2:
                 	POINT(2);
                  Zmena_rozliseni(2);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 1;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_3:
             	case SDLK_KP3:
                 	POINT(3);
                  Zmena_rozliseni(3);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 1;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_4:
             	case SDLK_KP4:
                 	POINT(4);
                  Zmena_rozliseni(4);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 1;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;


             	case SDLK_5:
             	case SDLK_KP5:
                 	POINT(5);
                  Zmena_rozliseni(5);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 1;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

              
             	case SDLK_n:
                 	POINT(20);
                  item[20].active = 1;
                  Scan_input(nick);
                  item[20].active = 0;
                  break;
            
             	case SDLK_F12:
                  F = ! F;
                  item[9].active = F;
                  Zmena_rozliseni(nastavene_rozliseni);
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
				          break;
				default:
					break;
				}
			}
		}


	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);


	//Draw_configure();
	//printf("X");
 
  }
  
  SDL_RemoveTimer(draw_timer);
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
		MIR_LOG_ERROR("some images missing ... ignore");
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
int Player_menu(){
//==============================================================================

  SDL_TimerID draw_timer = NULL;
  SDL_Event event;
  Uint8* keys;	

	draw_timer = SDL_AddTimer(20, Redraw_player_menu_loop, NULL); 				// DRAW


  Uint8 quit= 0;

  if(Load_menu_images() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro menu\n");

  if(Load_space_images() == FAIL) 
		fprintf(stderr, "ERROR: nepodarilo se nacist obrazky pro vesmir\n");


  bzero(item, sizeof(menu_item)*MAX_ITEMS);

  item[0].img_p = player_menu_bg;
  item[0].alive = 1;
  item[0].active = 0;
  item[0].x = 0;
  item[0].y = 0;

  item[1].img_p = menu_logo_small;
  item[1].alive = 1;
  item[1].active = 0;
  item[1].x = 100;
  item[1].y = 20;

 // --- flags --------------------------------------------------
  item[31].img_p = blue_flag;
  item[31].alive = 1;
  item[31].active = 0;
  item[31].x = 150;
  item[31].y = 150;

  item[30].img_p = red_flag;
  item[30].alive = 1;
  item[30].active = 0;
  item[30].x = 600;
  item[30].y = 150;

  item[33].img_p = switch_off_img;
  item[33].img_a = switch_on_img;
  item[33].alive = 1;
  item[33].active = 0;
  item[33].x = 270;
  item[33].y = 350;

  item[34].img_p = switch_off_img;
  item[34].img_a = switch_on_img;
  item[34].alive = 1;
  item[34].active = 0;
  item[34].x = 720;
  item[34].y = 350;
 // ------------------------------------------------------------
 // -- ships ---------------------------------------------------

  item[40].img_p = IMG_RED_RX;
  item[40].img_a = IMG_RED_RX_move;
  item[40].alive = 1;
  item[40].active = 0;
  item[40].x = 670;
  item[40].y = 400;

  item[41].img_p = IMG_RED_EX;
  item[41].img_a = IMG_RED_EX_move;
  item[41].alive = 1;
  item[41].active = 0;
  item[41].x = 670;
  item[41].y = 500;

  item[42].img_p = IMG_RED_RX;
  item[42].img_a = IMG_RED_RX_move;
  item[42].alive = 0;
  item[42].active = 0;
  item[42].x = 670;
  item[42].y = 600;


  // BLUE CORP
  item[50].img_p = IMG_BLUE_RX;
  item[50].img_a = IMG_BLUE_RX_move;
  item[50].alive = 1;
  item[50].active = 0;
  item[50].x = 200;
  item[50].y = 400;

  item[51].img_p = IMG_BLUE_RX;
  item[51].img_a = IMG_BLUE_RX_move;
  item[51].alive = 1;
  item[51].active = 0;
  item[51].x = 200;
  item[51].y = 500;

  item[52].img_p = IMG_RED_RX;
  item[52].img_a = IMG_RED_RX_move;
  item[52].alive = 0;
  item[52].active = 0;
  item[52].x = 200;
  item[52].y = 600;

  // ------------------------------------------------------------
  //for(int i = 0; i < CONFIG_ITEMS_MAX; i++){
  strcpy(configure_list[0], "");
  strcpy(configure_list[1], " [ 1 ]  RECON");
  strcpy(configure_list[2], "");
  strcpy(configure_list[3], "");
  strcpy(configure_list[4], "");
  strcpy(configure_list[5], " [ 2 ] BATTLE");
  strcpy(configure_list[6], "");
  strcpy(configure_list[7], "");
  strcpy(configure_list[8], "");
  strcpy(configure_list[9], " [ 3 ] SUPPORT");





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
				
             	case SDLK_0:
             	case SDLK_KP0:
                 	POINT(0);
                  Zmena_rozliseni(0);
                  item[1+1].active = 1;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_1:
             	case SDLK_KP1:
                 	POINT(1);
                  Zmena_rozliseni(1);
                  item[1+1].active = 0;
                  item[1+2].active = 1;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_2:
             	case SDLK_KP2:
                 	POINT(2);
                  Zmena_rozliseni(2);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 1;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_3:
             	case SDLK_KP3:
                 	POINT(3);
                  Zmena_rozliseni(3);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 1;
                  item[1+5].active = 0;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

             	case SDLK_4:
             	case SDLK_KP4:
                 	POINT(4);
                  Zmena_rozliseni(4);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 1;
                  item[1+6].active = 0;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;


             	case SDLK_5:
             	case SDLK_KP5:
                 	POINT(5);
                  Zmena_rozliseni(5);
                  item[1+1].active = 0;
                  item[1+2].active = 0;
                  item[1+3].active = 0;
                  item[1+4].active = 0;
                  item[1+5].active = 0;
                  item[1+6].active = 1;
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
                 	break;

              
             	case SDLK_n:
                 	POINT(20);
                  item[20].active = 1;
                  Scan_input(nick);
                  item[20].active = 0;
                  break;
            
             	case SDLK_F12:
                  F = ! F;
                  item[9].active = F;
                  Zmena_rozliseni(nastavene_rozliseni);
	                draw_timer = SDL_AddTimer(20, Redraw_configure_loop, NULL);
				          break;
				default:
					break;
				}
			}
		}


	
	SDL_PumpEvents();
	keys = SDL_GetKeyState(NULL);


	//Draw_configure();
	//printf("X");
 
  }
  
  SDL_RemoveTimer(draw_timer);
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
