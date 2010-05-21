#ifndef ZBRANE_H
 #define ZBRANE_H



#define LASER 1
#define RAKETA 2

#define MAX_LASERU 300
#define MAX_RAKET 30

#define LASER_rychlost 30
#define R1_rychlost 8

int pocet_laseru;
int pocet_raket;

struct zbrane{
	SDL_Surface *zbran;
	float X; //  pozice
	float Y;
	int sX;	 // pocatecni pozice
	int sY;
	int x;   // rect vykreslovaci pozice
	int y;
	int uhel;
	
		
}; 

struct zbrane lasery[MAX_LASERU];
struct zbrane rakety[MAX_LASERU];


char strilej[16];	// oznacuje ze kterych zbrani se prave strili


#endif
