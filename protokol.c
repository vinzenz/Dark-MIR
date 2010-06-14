#include "program.h"
#include "protokol.h"
#include "client.h"
#include "lod.h"
#include "zbrane.h"


//unsigned char tbuff[BUFF_SIZE];
//unsigned char rbuff[BUFF_SIZE];

// =============================================================================
// Client side protokol module
// =============================================================================

// =============================================================================
//==============================================================================
int New_client(){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	*tp = P_NEW_PLAYER;
	tp++;
	strncpy((char *) tp, (char *) nick, NICKNAME_MAX);

	printf("t->data[0]: 0x%X\n",t->data[0]);
	printf("t->data+1: %s\n", tp);

	UDP_SEND;


  for(int i=0; i < 100; i++){

	usleep(2000);	  
		  
	UDP_RECV;
	else continue;

	if(r->data[0] == P_NEW_PLAYER){
		ID = r->data[1];
		printf("ID: %2d\n", ID);
  		return OK;
	}
  }
		printf("SERVER IS FULL\n");		
  		exit(EXIT_FAILURE);
}

//==============================================================================
int Logout(){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	*tp = P_LOGOUT;
	tp++;
	strcpy((char *) tp, "... leaving ...\n");

	printf("t->data[0]: 0x%X\n",t->data[0]);
	printf("t->data+1: %s\n", tp);

	UDP_SEND;

  return OK;
}

//==============================================================================
int Speed_up(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_SPEED_UP;
	else			
		*tp = P_SPEED_UP;

	tp++;

	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}

//==============================================================================
int Slow_down(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_SLOW_DOWN;
	else
		*tp = P_SLOW_DOWN;

	tp++;
	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}

//==============================================================================
int Rotate_L(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_ROTATE_L;
	else
		*tp = P_ROTATE_L;

	tp++;
	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}

//==============================================================================
int Rotate_R(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_ROTATE_R;
	else
		*tp = P_ROTATE_R;

	tp++;
	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}

//==============================================================================
//==============================================================================
int Shift_L(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_SHIFT_L;
	else
		*tp = P_SHIFT_L;

	tp++;
	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}
//==============================================================================
int Shift_R(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_SHIFT_R;
	else
		*tp = P_SHIFT_R;

	tp++;
	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;

}

//==============================================================================
int Fire(int wp){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	*tp = P_FIRE_0 + wp;	
	tp++;

	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}




/*
//==============================================================================
int Get_ship_state(){
//==============================================================================
	UDP_RECV;

	unsigned char *tp = r->data;
	//if(*tp == P_STATE){
		tp++;	
		my_ship->X = *( (float *)tp);
		tp += sizeof(float);
		my_ship->Y = *( (float *)tp);
		tp += sizeof(float);
		my_ship->speed = *( (float *)tp);
		tp += sizeof(float);
		my_ship->angle = *( (float *)tp);
	printf("STATE RECIVED\n");			
	//}
	return OK;
}
*/
//==============================================================================
int Get_ship_states(){
//==============================================================================	

	Uint8 *tp = r->data;
	Uint8 id = 0;

printf("!!--");			

  if(*tp != P_SHIP_STATES)					// OP_code
    return FAIL;

  tp++;	
 										
  if(fabs(*(tp) - PACKET_NUMBER) > 10)				// PACKET_NUMBER
	PACKET_NUMBER = *(tp);	// overflow correction
  if(*(tp) < PACKET_NUMBER)
	return FAIL;	  		// not right deliver order

  tp++;	


  while(tp - r->data < BUFF_SIZE - 6 * sizeof(float)){

		printf("__==");			

		id = *(tp);							// ID
		if(id == 0xFF) break;

		tp++;	
		ship[id].type = *(tp);				// TYPE
		tp++;	
		ship[id].X = *( (float *)tp);		// X
		printf("X: %f\n", ship[id].X);
		tp += sizeof(float);
		ship[id].Y = *( (float *)tp);		// Y
		printf("Y: %f\n", ship[id].Y);
		tp += sizeof(float);
		ship[id].speed = *( (float *)tp);	// SPEED
		printf("speed: %f\n", ship[id].speed);
		tp += sizeof(float);
		ship[id].angle = *( (float *)tp);	// ANGLE
		printf("angle: %f\n", ship[id].angle);
		tp += sizeof(float);
		ship[id].health = *( (int *)tp);	// DAMAGE
		printf("health: %d\n", ship[id].health);
		tp += sizeof(int);

  }
 
	return OK;
}
//==============================================================================
int Get_weapon_states(){
//==============================================================================	

	Uint8 *tp = r->data;
	Uint8 id = 0;


  if(*tp != P_WEAPON_STATES)					// OP_code
    return FAIL;

printf("WEPON STATES:\n");			
  tp++;	


  while(tp - r->data < BUFF_SIZE - 4 * sizeof(float)){
		id = *(tp);							// ID
		if(id == 0xFF) break;

		tp++;	
		weapon[id].type = *(tp);			// TYPE
		tp++;	
		weapon[id].strana = *(tp);			// SUBTYPE (strana)
		tp++;	
		weapon[id].X = *( (float *)tp);		// X
		printf("X: %f\n", weapon[id].X);
		tp += sizeof(float);
		weapon[id].Y = *( (float *)tp);		// Y
		printf("Y: %f\n", weapon[id].Y);
		tp += sizeof(float);
		weapon[id].angle = *( (float *)tp);	// ANGLE
		printf("angle: %f\n", weapon[id].angle);
		tp += sizeof(float);
		
		weapon[id].alive = 1;

		if(id >= pocet_weapons)
			pocet_weapons++;
  }
 
	return OK;
}
// =============================================================================
// =============================================================================
int  print_ip(){
// =============================================================================
	// human readable IP address
	printf("%d.%d.%d.%d", 
		(SDLNet_Read32(&remoteIP->host) & 0xFF000000) >> 24,
		(SDLNet_Read32(&remoteIP->host) & 0x00FF0000) >> 16,
		(SDLNet_Read32(&remoteIP->host) & 0x0000FF00) >> 8,
		(SDLNet_Read32(&remoteIP->host) & 0x000000FF) >> 0 
	);
	return OK;
}

// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
// =============================================================================
