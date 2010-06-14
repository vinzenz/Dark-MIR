#ifndef ZBRANE_H
 #define ZBRANE_H


#define LASER 1
#define ROCKET 2

#define ENERGY_LASER 3

// ==========================================
#define MAX_WEAPONS 1000
#define MAX_LASER 300
#define MAX_ROCKET 30


int pocet_weapons;
int pocet_laseru;
int pocet_raket;

 typedef struct str_weapon {
	SDL_Surface *img;
	char type;
	char strana;

	float speed;
	float MAX_speed;
	float acceleration;
	int delta_angle;
	float angle;
	float angle2;
	int damage;
	float X; //  pozice
	float Y;
	int x;   // rect vykreslovaci pozice
	int y;
	char alive;
} T_weapon;

/*
struct zbrane lasery[MAX_LASERU];
struct zbrane rakety[MAX_LASERU];
*/

T_weapon lasers[MAX_LASER];
T_weapon rockets[MAX_ROCKET];

T_weapon weapon[MAX_WEAPONS];

//char strilej[16];	// oznacuje ze kterych zbrani se prave strili


#endif
