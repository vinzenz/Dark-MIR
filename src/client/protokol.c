#include "program.h"
#include "protokol.h"
#include "client.h"
#include "lod.h"
#include "zbrane.h"

#include "images.h"
#include "faction.h"

//unsigned char tbuff[BUFF_SIZE];
//unsigned char rbuff[BUFF_SIZE];

// =============================================================================
// Client side protokol module
// =============================================================================

// =============================================================================
//==============================================================================
int New_client(){
//==============================================================================

	Uint8 *tp=NULL;
	tp=t->data;

	*tp = P_NEW_PLAYER;
	tp++;
  *((Uint8*) tp) = FACTION;
	tp++;
	strncpy((char *) tp, (char *) nick, NICKNAME_MAX);

//	printf("t->data[0]: 0x%X\n",t->data[0]);
//	printf("t->data+1: %s\n", tp);

	UDP_SEND;

  for(int i=0; i < 3; i++){

    SDL_Delay(500);	  
		  
    UDP_RECV;
    else continue;

    if(r->data[0] == P_NEW_PLAYER){
      ID = r->data[1];
      FACTION = r->data[2];
      //printf("ID: %2d\n", ID);
      return OK;
    }
    if(r->data[0] == P_LOGOUT){
      DEBUG("SERVER IS FULL");		
      exit(EXIT_FAILURE);
    }
  }
  //printf("SERVER IS NOT RUNNING\n");		
  return FAIL;
}

//==============================================================================
int Logout(){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	*tp = P_LOGOUT;
	tp++;
	strcpy((char *) tp, "... leaving ...\n");

//	printf("t->data[0]: 0x%X\n",t->data[0]);
//	printf("t->data+1: %s\n", tp);

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

//	printf("t->data[0]: 0x%X\n",t->data[0]);

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
//	printf("t->data[0]: 0x%X\n",t->data[0]);

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
//	printf("t->data[0]: 0x%X\n",t->data[0]);

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
//	printf("t->data[0]: 0x%X\n",t->data[0]);

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
//	printf("t->data[0]: 0x%X\n",t->data[0]);

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
//	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;

}
//==============================================================================
int Turbo(int X){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	if(X == STOP)
		*tp = P_STOP_TURBO;
	else
		*tp = P_TURBO;

	tp++;

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

//	printf("t->data[0]: 0x%X\n",t->data[0]);

	UDP_SEND;
	return OK;
}




//==============================================================================
int Get_ship_states(){
//==============================================================================	

	Uint8 *tp = r->data;
	Uint8 id = 0;

//printf("!!--");			

  if(*tp != P_SHIP_STATES)					// OP_code
    return FAIL;

  tp++;	
 										
  if(fabs(*(tp) - PACKET_NUMBER) > 100)				// PACKET_NUMBER
    PACKET_NUMBER = *(tp);	// overflow correction

//  if(*(tp) < PACKET_NUMBER)
//    return FAIL;	  		    // not right deliver order

  tp++;	


  while(tp - r->data < BUFF_SIZE - 7 * sizeof(float)){

//		printf("__==");			

		id = *(tp);							// ID
    fprintf(stderr, "SHIP ID: %u\n",id);

		if(id == 0xFF){
      DEBUG("WARNNING: unexepected ID of ship")
       break;
    }

		tp++;	
		object[id].descriptor = SHIP;
		object[id].type = *(tp);				// TYPE
		tp++;	
		object[id].X = *( (Sint32 *)tp);		// X
    fprintf(stderr, "SHIP X: %u\n",object[id].X);

		//printf("ID: %3d id: %3d X: %5d\n",ID, id, object[id].X);
		//printf("ID: %3d ship: %3d X: %5d\n",ID, id, my_ship->X);
		tp += sizeof(Sint32);
		object[id].Y = *( (Sint32 *)tp);		// Y
    fprintf(stderr, "SHIP Y: %u\n",object[id].Y);
//		printf("Y: %f\n", ship[id].Y);
		tp += sizeof(Sint32);
		object[id].speed = *( (float *)tp);	// SPEED
//		printf("speed: %f\n", ship[id].speed);
		tp += sizeof(float);
		object[id].angle = *( (float *)tp);	// ANGLE
//		printf("angle: %f\n", ship[id].angle);
		tp += sizeof(float);
		object[id].health = *( (int *)tp);	// DAMAGE
//		printf("health: %4d\n", object[id].health);
		tp += sizeof(int);
		object[id].faction = *( (int *)tp);	// FACTION
//		printf("health: %4d\n", object[id].health);
		tp += sizeof(int);

    if((object[id].X == 0) && (object[id].Y == 0)){
      fprintf(stderr, "DEAD ID: %u\n", id);
		  object[id].alive = 0;
    }else
		  object[id].alive = 1;


  }
 
	return OK;
}

/* ZASTARALE
//==============================================================================
int Get_weapon_states(){
//==============================================================================	

	Uint8 *tp = r->data;
	Uint8 id = 0;


  if(*tp != P_WEAPON_STATES)					// OP_code
    return FAIL;

  DEBUG("GET WEAPONS STATES"); 
  tp++;	


  while(tp - r->data < BUFF_SIZE - 4 * sizeof(float)){
		id = *(tp);							// ID
		if(id == 0xFF) break;

    printf("wp id:%3d\n");

		tp++;	
		object[id].descriptor = WEAPON;
		object[id].type = *(tp);			// TYPE
		tp++;	
		object[id].faction = *(tp);			// SUBTYPE (strana)
		tp++;	
		object[id].X = *( (float *)tp);		// X
//		printf("X: %f\n", weapon[id].X);
		tp += sizeof(float);
		object[id].Y = *( (float *)tp);		// Y
//		printf("Y: %f\n", weapon[id].Y);
		tp += sizeof(float);
		object[id].angle = *( (float *)tp);	// ANGLE
//		printf("angle: %f\n", weapon[id].angle);
		tp += sizeof(float);
	
    if((object[id].X == 0) && (object[id].Y == 0))	
		  object[id].alive = 0;
    else
		  object[id].alive = 1;

//		if(weapon[id].type == EXPLOSION) 
//				printf("TEST: explosion at: %g %g", 
//					weapon[id].X, weapon[id].Y);


		if(id >= pocet_weapons)
			pocet_weapons++;
  }
 
	return OK;
}
*/
//==============================================================================
int Get_object_states(){
//==============================================================================	

	Uint8 *tp = r->data;
	Uint32 id = 0;


  if((*tp != P_OBJECT_STATES) &&	
     (*tp != P_WEAPON_STATES))					// OP_code
      return FAIL;

  DEBUG("OBJECT STATES");
  tp++;	


  // POTREBA PREPOCITAT VELIKOST
  while(tp - r->data < BUFF_SIZE - 4 * sizeof(float)){
		id = *((Uint32 *)tp);							// ID
		if(id >= MAX_OBJECTS - 1){
      ERROR("too high identification number, packet corruption possible");
      fprintf(stderr, "object ID: %u\n", id);
      break;
    }

		tp += sizeof(Uint32);
		object[id].descriptor = *(tp);  // DESCRIPTOR
		tp++;	
		object[id].type = *(tp);        // TYPE
		tp++;	
		object[id].model = *(tp);       // TYPE model
		tp++;	
		object[id].faction = *(tp);			// FACTION
		tp++;	
		object[id].X = *( (Uint32 *)tp);		// X
//		printf("X: %f\n", weapon[id].X);
		tp += sizeof(Uint32);
		object[id].Y = *( (Uint32 *)tp);		// Y
//		printf("Y: %f\n", weapon[id].Y);
		tp += sizeof(Uint32);
		object[id].angle = *( (float *)tp);	// ANGLE
//		printf("angle: %f\n", weapon[id].angle);
		tp += sizeof(float);
	
    if((object[id].X == 0) && (object[id].Y == 0)){
      fprintf(stderr, "DEAD ID: %u\n", id);
		  object[id].alive = 0;
      object[id].img = NULL;
    }else
		  object[id].alive = 1;
/*
		if(weapon[id].type == EXPLOSION) 
				printf("TEST: explosion at: %g %g", 
					weapon[id].X, weapon[id].Y);
*/

  }
 
	return OK;
}


//==============================================================================
int Get_player_list(){
//==============================================================================	
  Sint16 score = 0;
  char nick[NICKNAME_MAX];

	Uint8 *tp = r->data;
	Uint8 id = 0;

//printf("!!--");			

  if(*tp != P_PLAYER_LIST)					// OP_code
    return FAIL;

  tp++;	

  //while(tp - r->data < BUFF_SIZE - NICKNAME_MAX - 4 ){
  {

		id = *(tp);							// ID
		//if(id == 0xFF) break;

		tp++;	
		object[id].type = *(tp);				// TYPE
		tp++;	
		score = *((Sint16 *)tp);			// SCORE 
		tp++;
		tp++;
		strncpy(nick, (char *) tp, NICKNAME_MAX-1);	// NICK
		tp += NICKNAME_MAX;

		printf("PLAYER: %d  SCORE: %d\n",id, score);
		sprintf(player_list[id], "| %2d | %32s | %3d |", id, nick, score);		
		

  }
 
	return OK;
}
//==============================================================================
int Request_player_list(){
//==============================================================================
	unsigned char *tp=NULL;
	tp=t->data;

	*tp = P_PLAYER_LIST;

	tp++;

	UDP_SEND;
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
