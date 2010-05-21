#ifndef LOD_H
 #define LOD_H

#include "program.h"

#define MAX_LODI 40




struct str_lod{
	SDL_Surface *lod;
	char strana;
	
	float rychlost;
	int MAX_rychlost;
	float zrychleni;

	int manevr;
	float uhyb;
	int MAX_uhyb;

	int poskozeni;
	int MAX_poskozeni;
	
	float X; //  pozice
	float Y;
	int sX;	 // pocatecni pozice
	int sY;
	int x;   // rect vykreslovaci pozice
	int y;
	int uhel;
	
		
} lode[MAX_LODI];

/*
	lode[0]  je lod lokalniho hrace

*/





// -----  Funkce  -----

int Vystrel(int zbran, int lod);
Uint32 Ovladani(Uint32 interval, void *param);

SDL_Surface *roto_lod;
SDL_Surface *rlod;
int uhel;
int uhel2;

float rychlost;
int MAX_rychlost;
float zrychleni;

int manevr;
float uhyb;
int MAX_uhyb;

int poskozeni;
int MAX_poskozeni;

#endif
