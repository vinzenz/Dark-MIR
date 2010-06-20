#ifndef IMAGES_H
 #define IMAGES_H


#include "program.h"

int Nacti_obrazky_vesmir();
int Uklid_obrazky_vesmir();
int Nacti_obrazky_menu();
int Uklid_obrazky_menu();
int Nacti_obrazky_bmenu();
int Uklid_obrazky_bmenu();
int Nacti_obrazky_mapa();
int Uklid_obrazky_mapa();
int Nastav_rozliseni();
int Zmena_rozliseni(char X);

int Kresli_lod();
int Kresli_pristroje();
int Kresli_strely();

SDL_Surface *screen;                  // okno
SDL_Surface *bg_img;                     // pozadi
SDL_Surface *bg_nastaveni;                     // pozadi
SDL_Surface *policko;			// v menu
SDL_Surface *policko1;			// v menu
SDL_Surface *tlacitko;			// v menu
SDL_Surface *b_menu;			// v bitevnim menu

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
