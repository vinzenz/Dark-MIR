#include "program.h"
#include "images.h"
#include "zbrane.h"
#include "lod.h"


//#include "weapons.h"

//==============================================================================
Uint32 Ovladani(Uint32 interval, void *param){
//==============================================================================

	my_ship->angle += manevr;
	my_ship->speed += acceleration;	
	
//	if(strilej[LASER] != 0) Vystrel(LASER, my_ship);
//	if(strilej[ROCKET] != 0) Vystrel(ROCKET, my_ship);
	
return interval;	
}









/*
//==============================================================================
int Vystrel(int zbran, T_ship *ship){
//==============================================================================

	switch(zbran){
		
		case LASER:
			if(pocet_laseru < MAX_LASER-1){
				pocet_laseru++;
				lasers[pocet_laseru] = RX_laser;
				lasers[pocet_laseru].angle = ship->angle;
				lasers[pocet_laseru].X = X;
				lasers[pocet_laseru].Y = Y;
				
				
				
			}
			else{
			#ifdef DEBUG
				
				fprintf(stderr,"MAX: VYSTRELU(laseru) \n");
				//fprintf(stderr,"poskozeni: %d \n",ship->poskozeni);
				//fprintf(stderr,"speed: %G \n",ship->speed);
				
			#endif				
				
			}	
			
			
			break;
		case ROCKET:
			
			if(pocet_raket < MAX_ROCKET-1){
				pocet_raket++;
				rockets[pocet_raket] = RX_R1;
				rockets[pocet_raket].angle = ship->angle;
				rockets[pocet_raket].X = X;
				rockets[pocet_raket].Y = Y;
				
			}
			else{
			#ifdef DEBUG
				
				fprintf(stderr,"MAX: VYSTRELU(raket) \n");
				
				
			#endif				
				
			}	
		
			break;
		
		default: 
			break;
	}
	
	
	
	
return OK;	
}

*/
