#include "program.h"
#include "protokol.h"
#include "client.h"
#include "lod.h"


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
		*tp = P_SHIFT_R;
	else
		*tp = P_STOP_SHIFT_R;

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
//==============================================================================
int Get_ship_states(){
//==============================================================================	
	UDP_RECV;
	else return OK;

	Uint8 *tp = r->data;
	Uint8 id = 0;



printf("!!--");			

if(*tp == P_SHIP_STATES){					// OP_code
  tp++;	

printf(":||:");			

  for(int i = 0; i < 3; i++){

	//if(*tp == ID){							// ID
		printf("__==");			
/*
		tp++;	
		my_ship->type = *(tp);				// TYPE
		tp++;	
		my_ship->X = *( (float *)tp);		// X
		printf("X: %f\n", (double)my_ship->X);
		tp += sizeof(float);
		my_ship->Y = *( (float *)tp);		// Y
		tp += sizeof(float);
		my_ship->speed = *( (float *)tp);	// SPEED
		tp += sizeof(float);
		my_ship->angle = *( (float *)tp);	// ANGLE
		tp += sizeof(float);
*/		
	//}else{

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

		POINT(*tp);
		POINT(ID);

	//}
  }
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
