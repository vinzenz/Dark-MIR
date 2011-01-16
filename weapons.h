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

T_object Explosion = {
	.type = EXPLOSION,
	.speed = 0,
	.damage = 0,
	.alive = 1,

};


// NEW speeds
T_object RX_laser = {
	.type = LASER,
	.speed = 50,
	.damage = 10,
	.alive = 1,
	.ttl = 300,	// 300 * 20 ms = 6s

};

T_object RX_R1 = {
	.type = ROCKET,
	.speed = 20,
	.damage = 30,
	.alive = 1,
	.ttl = 600,	//  = 12s

};


T_object RX_M1 = {
	.type = MICRO_MISSILE,
	.speed = 25,
	.damage = 20,
	.alive = 1,
	.ttl = 400,	//  = 8s

};

T_object RX_M2 = {
	.type = GUIDED_MISSILE,
	.speed = 15,
	.damage = 40,
	.alive = 1,
	.ttl = 500, // 10s

};


T_object ZX_Q1 = {
	.type = ENERGY_LASER,
	.speed = 50,
	.damage = 20,
	.alive = 1,
	.ttl = 400, // 8s

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
