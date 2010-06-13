#ifndef WEAPONS_H
 #define WEAPONS_H

#include "zbrane.h"

/*
 typedef struct str_weapon {
	SDL_Surface *img;
	char strana;

	float speed;
	float MAX_speed;
	float acceleration;
	int delta_angle;
	int angle;
	int damage;
	float X; //  pozice
	float Y;
	int x;   // rect vykreslovaci pozice
	int y;

} T_weapon;
*/


// NEW speeds
T_weapon RX_laser = {
	.type = LASER,
	.speed = 30,
	.damage = 10,
	.alive = 1,

};

T_weapon RX_R1 = {
	.type = ROCKET,
	.speed = 15,
	.damage = 30,
	.alive = 1,

};


/*
// OLD speeds
T_weapon RX_laser = {
	.type = LASER,
	.speed = 9,
	.damage = 10,
	.alive = 1,

};

T_weapon RX_R1 = {
	.type = ROCKET,
	.speed = 7,
	.damage = 30,
	.alive = 1,

};
*/


#endif
