#ifndef IMAGES_H
 #define IMAGES_H


#include "program.h"

#define FREE(IMG) if((IMG) !=NULL) SDL_FreeSurface((IMG));


int Load_space_images();
int Free_space_images();

int Load_menu_images();
int Free_menu_images();

int Nacti_obrazky_bmenu();
int Uklid_obrazky_bmenu();
int Nacti_obrazky_mapa();
int Uklid_obrazky_mapa();
int Nastav_rozliseni();
int Zmena_rozliseni(char X);

int Kresli_lod();
int Kresli_pristroje();
int Kresli_strely();
int Draw_menu();
int Draw_configure();

SDL_Surface *screen;            // okno


// ===== MENU =====
SDL_Surface *menu_bg;           // pozadi
SDL_Surface *settings_bg;       // pozadi
SDL_Surface *connect_bg;        // pozadi

SDL_Surface *menu_connect_button;
SDL_Surface *menu_settings_button;
SDL_Surface *menu_exit_button;	
SDL_Surface *menu_logo;



// ===== SHIPS =====
SDL_Surface *lod;			// hracohracova kosmicka lod
SDL_Surface *lod_a;			// hracohracova kosmicka lod assault
SDL_Surface *lod_b;			// hracohracova kosmicka lod battle
SDL_Surface *lod_c;			// hracohracova kosmicka lod carry
SDL_Surface *lod_d;			// hracohracova kosmicka lod digger

SDL_Surface *IMG_RED_RX;		// 
SDL_Surface *IMG_RED_RX_move;		// 
SDL_Surface *IMG_RED_RX_crap;		// 
SDL_Surface *IMG_RED_EX;		// 
SDL_Surface *IMG_RED_EX_move;		// 
SDL_Surface *IMG_RED_EX_crap;		// 


SDL_Surface *IMG_BLUE_RX;		// 
SDL_Surface *IMG_BLUE_RX_move;		// 
SDL_Surface *IMG_BLUE_RX_crap;		// 

SDL_Surface *IMG_GREEN_ZX;		// 
SDL_Surface *IMG_GREEN_ZX_move;		// 
SDL_Surface *IMG_GREEN_ZX_crap;		// 

// Explosions
SDL_Surface *r_explosion;
SDL_Surface *g_explosion;
SDL_Surface *b_explosion;


SDL_Surface *CENTER;


// Zbrane
SDL_Surface *laser;
SDL_Surface *raketa;
SDL_Surface *energy_laser;
SDL_Surface *energy_plasma;
SDL_Surface *micro_missile;
SDL_Surface *guided_missile;

// Pristroje
SDL_Surface *radar;
SDL_Surface *radar_point_r;
SDL_Surface *radar_point_g;


SDL_Surface *damage;
SDL_Surface *speed;
SDL_Surface *position_x;
SDL_Surface *position_y;
SDL_Surface *position_ptr_x;
SDL_Surface *position_ptr_y;

SDL_Surface *space;			// vesmirne pozadi

SDL_Surface *console;
SDL_Surface *console_line;
SDL_Surface *console_bg;
TTF_Font *console_font;


SDL_Color fg_color;
SDL_Color bg_color;

#endif
