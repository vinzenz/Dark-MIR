#ifndef PROTOKOL_H
  #define PROTOKOL_H


#include "program.h"
#include "server.h"


/* Communication Protokol Description v0.01
 * 
 * Clients request
 *
 * 1. Byte = request code
 * 2. - ... data
 *
 *
 *  0x01 = new player
 *  0x02 = 
 *  0x03 =
 *
 *  0x11 = rotate right
 *  0x12 = rotate left
 *  0x13 = accelerate speed up
 *  0x14 = slow down
 *  0x15 = shift right
 *  0x16 = shift left
 *
 *  0x41 = fire 1. weapon
 *  0x42 = fire 2. weapon
 *  0x43 = fire 2. weapon
 *
 *  0xFF = logout
 */


/* Server answer
 * 
 * 1. Byte = answer code
 * 2. Byte ...N X position
 * N. Byte ...M Y position
 * N. Byte ...M angle
 * N. Byte ...M speed
 *
 *
 *
 */

/*	// PLAYER STRUCT example
typedef struct str_player{
	IPaddress  ip;	
	char nick[32];
	
	int score;
	T_ship ship;
	
} T_player;
*/


#define NICKNAME_MAX 	32	
#define HOSTNAME_MAX 	256


#define SERVER_TIME_INTERVAL 10

#define P_NEW_PLAYER 	0x01
#define P_LOGOUT 		0xFF
// ----------------------------
#define P_ROTATE_R 		0x11
#define P_ROTATE_L 		0x12

#define P_SPEED_UP 		0x13
#define P_SLOW_DOWN		0x14

#define P_SHIFT_R		0x15
#define P_SHIFT_L		0x16



// ----------------------------
//  0x21, X, Y, speed, [ angle ]
#define P_POSITION		0x21
#define P_STATE			0x22


// ----------------------------
#define P_FIRE_1		0x41
#define P_FIRE_2		0x42
#define P_FIRE_3		0x43



// MACROS
// =============================================================================
#define  RECV \
		printf("Recieving data:\n");\
		bzero(rbuff, BUFF_SIZE);\
		if (SDLNet_TCP_Recv(sd, (void *)rbuff, BUFF_SIZE) > 0){\
			printf("recived: 0x%X:%s\n", rbuff[0], rbuff+1);\
			printf("recived: 0x%X:%f\n", rbuff[0], (double) *((float *) rbuff+1));\
		}else   \
			printf("INVALID PACKET");\


#define SEND \
		printf("Sending data:\n");\
		if (SDLNet_TCP_Send(sd, (void *)tbuff, BUFF_SIZE) < BUFF_SIZE){\
			fprintf(stderr, "SDLNet_TCP_Send: %s\n", SDLNet_GetError());\
			exit(EXIT_FAILURE);\
		}\
		bzero(tbuff, BUFF_SIZE);
// UDP
// =============================================================================
#define  UDP_RECV \
		if (SDLNet_UDP_Recv(usd, r))


#define UDP_SEND \
		printf("Sending data: 0x%2X\n", t->data[0]);\
		SDLNet_UDP_Send(usd, -1, t);\
		bzero(t->data, BUFF_SIZE);







// FUNCTIONS
// =============================================================================
int New_client();
int Logout();

int Speed_up();
int Slow_down();
int Rotate_R();
int Rotate_L();
int Shift_R();
int Shift_L();

int Get_ship_state();

int print_ip();
// =============================================================================
#endif
