#include "program.h"
#include "images.h"
#include "zbrane.h"
#include "lod.h"



//==============================================================================
Uint32 Ovladani(Uint32 interval, void *param){
//==============================================================================

	my_ship->uhel += manevr;
	my_ship->rychlost += zrychleni;	
	
	if(strilej[LASER] != 0) Vystrel(LASER, my_ship);
	if(strilej[RAKETA] != 0) Vystrel(RAKETA, my_ship);
	
return interval;	
}










//==============================================================================
int Vystrel(int zbran, T_ship *ship){
//==============================================================================

	switch(zbran){
		
		case LASER:
			if(pocet_laseru < MAX_LASERU-1){
				pocet_laseru++;
				lasery[pocet_laseru].uhel = ship->uhel;
				lasery[pocet_laseru].uhel = ship->uhel;
				lasery[pocet_laseru].sX = X;
				lasery[pocet_laseru].sY = Y;
				lasery[pocet_laseru].X = X;
				lasery[pocet_laseru].Y = Y;
				//lasery[pocet_laseru].x = /*(WIDTH/2) - (laser->w/2) + */(lasery[pocet_laseru].X - lasery[pocet_laseru].sX);
				//lasery[pocet_laseru].y = /*(HEIGHT/2) - (laser->h/2) + */(lasery[pocet_laseru].Y - lasery[pocet_laseru].sY);
				
				
				
			}
			else{
			#ifdef DEBUG
				
				fprintf(stderr,"MAX: VYSTRELU(laseru) \n");
				//fprintf(stderr,"poskozeni: %d \n",ship->poskozeni);
				//fprintf(stderr,"rychlost: %G \n",ship->rychlost);
				
			#endif				
				
			}	
			
			
			break;
		case RAKETA:
			
			if(pocet_raket < MAX_RAKET-1){
				pocet_raket++;
				rakety[pocet_raket].uhel = ship->uhel;
				rakety[pocet_raket].sX = X;
				rakety[pocet_raket].sY = Y;
				rakety[pocet_raket].X = X;
				rakety[pocet_raket].Y = Y;
				
				//rakety[pocet_laseru].x = /*(WIDTH/2) - (laser->w/2) + */(rakety[pocet_laseru].X - lasery[pocet_laseru].sX);
				//lasery[pocet_laseru].y = /*(HEIGHT/2) - (laser->h/2) + */(lasery[pocet_laseru].Y - lasery[pocet_laseru].sY);
				
				
				
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
