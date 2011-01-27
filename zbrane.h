#ifndef __ZBRANE_H_
 #define __ZBRANE_H_

#include "objects.h"

#define LASER 1
#define ROCKET 2
#define ENERGY_LASER 3
#define MICRO_MISSILE 4
#define GUIDED_MISSILE 5
#define MISSILE 2 // 6
#define MULTI_MISSILE 8 // 6

#define EXPLOSION 20
// ==========================================
#define MAX_WEAPONS 1000
#define MAX_LASER 300
#define MAX_ROCKET 30

#define EXPLOSION_TTL 10

int pocet_weapons;

 typedef struct str_weapon {
	SDL_Surface *img;
	Uint8 type;
	Uint8 strana;

	float speed;
	float MAX_speed;
	float acceleration;
	int delta_angle;
	float angle;
	float angle2;
	int damage;
	float X; 
	float Y;
	//int x;   
	//int y;

	Uint8 alive;
	Uint16 ttl;		// Time To Live

} T_weapon;

/*
struct zbrane lasery[MAX_LASERU];
struct zbrane rakety[MAX_LASERU];
*/

//T_weapon lasers[MAX_LASER];
//T_weapon rockets[MAX_ROCKET];

//T_weapon weapon[MAX_WEAPONS];
T_object Explosion;

//char strilej[16];	// oznacuje ze kterych zbrani se prave strili


#endif
