/*************************************************************************** 
 *  Dark Mir                                                               *
 *	version 0.01                                                           *
 *   Copyright (C) 2007 by Alexej alexej.x@mail.ru                         *
 *                                                                         * 
 *   This program is free software; you can redistribute it and/or modify  * 
 *   it under the terms of the GNU General Public License as published by  * 
 *   the Free Software Foundation; either version 3 of the License, or     * 
 *   (at your option) any later version.                                   * 
 *                                                                         * 
 *   This program is distributed in the hope that it will be useful,       * 
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        * 
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         * 
 *   GNU General Public License for more details.                          * 
 *                                                                         * 
 *   You should have received a copy of the GNU General Public License     * 
 *   along with this program; if not, write to the                         * 
 *   Free Software Foundation, Inc.,                                       * 
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             * 
 ***************************************************************************/



#include "program.h"
#include "images.h"
#include "client.h"

#include <getopt.h>



int	Init(int w, int h, int bits, int full);
int NET_Init();	
int	Get_Opts(int argc, char **argv);


// -------------------------------------------------------------------------------------------

//==============================================================================
int main(int argc,char *argv[]){
//==============================================================================


  strcpy(nick, "PLAYER_Alexej");

	Get_Opts(argc, argv);  
	
//	Nacti_konfiguraci();
	
//	Nacti_jazyk(p_lang);

	NET_Init();

	Nastav_rozliseni();   
	Zmena_rozliseni(nastavene_rozliseni);

//	Init(WIDTH, HEIGHT, COLOR, 0);
    
   
	Vesmir(); // Hlavni funkce
	 

	SDL_Quit();

	return OK;
}





// -------------------------------------------------------------------------------------------
//==============================================================================
int	Get_Opts(int argc, char **argv){
//==============================================================================
  char *p_lang;

	// argumenty 
    while (1) {
	 int c = getopt(argc, argv, "hfer:l:");
	 if (c == -1) {
	      break;
	    } else
     switch (c) {
	  case 'h':
		printf("%s\n", HELP_MSG);
	/*	  
	    printf("GROZA RTS v %s \n", VERSION);
	    printf("GNU GPL-3 \n");
	    printf("2008 copyright by\n");
	    printf("(c) Alexej alexej.x@mail.ru  \n");
	    //printf("(c) NiO jurajg@gmail.com \n\n");
	    printf("	-h		show this help    \n");
	    printf("	-f		fullscreen    \n");
	    printf("	-r NUM	resolution(default 1) 0 = 800x600; 1 = 1024x768; 2 = 1280x1024;\n"); 
	    printf("	-l LANG	language (LANG: cs,sk,ru,en ) \n");  	  
	    printf("	-e		map editor    \n");
	  	printf("\n");
		*/
	    return OK;
        break;
	  
	  case 'f':
        F = 1;
	    break;
     
	  case 'r':
        
	  	nastavene_rozliseni = atoi(optarg);
	    
	    break;
	  
	  
	  case 'l':
        
	  	p_lang = optarg;
	    
	    break; 
	  
	  
	  
	  }
   }

	// The last parameter is hostname of server //
	if(argv[argc-1] != NULL)
			strncpy(hostname, argv[argc-1], HOSTNAME_MAX);

	return OK;
}
// -------------------------------------------------------------------------------------------






//==============================================================================
int	Init(int w, int h, int bits, int full){
//==============================================================================

	if (SDL_Init(SDL_SUBSYSTEMS)==-1){
		
	
	fprintf(stderr, "ERROR: Inicializacia VIDEO podpory SDL sa nepodarila: %s\n",
				SDL_GetError());
		return FAIL;
	}
	
	fprintf(stderr, "Inicializacia VIDEO podpory SDL [OK] \n");
	

	screen = SDL_SetVideoMode(w, h, bits, WIN_FLAGS );

	SDL_WM_SetCaption(WIN_TITLE, 0);

	if (screen==NULL){
		printf("Inicializacia videobufferu %ix%ix%i: %s\n", w, h, bits, SDL_GetError());
		return FAIL;
	}
	
	if(TTF_Init() == -1){
    	printf("Nepodarilo se inicializovat SDL_ttf: %s\n", TTF_GetError());
    	return FAIL;
    }

	if(F==1)SDL_WM_ToggleFullScreen(screen);	

    return OK;	
}

//==============================================================================
int	NET_Init(){
//==============================================================================
	// ==== SDL_NET_Init ====
	if (SDLNet_Init() == FAIL){
	    fprintf(stderr, "SDLNet_Init: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}
 
	/* Resolving the host */
  	if (SDLNet_ResolveHost(&ip, hostname, PORT) == FAIL){
		fprintf(stderr, "SDLNet_ResolveHost: %s\n", SDLNet_GetError());
	    exit(EXIT_FAILURE);
    }
 
	/* Open a connection with the IP provided ) */
  	if (!(sd = SDLNet_TCP_Open(&ip))){
		fprintf(stderr, "SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		exit(EXIT_FAILURE);
	}

    return OK;	
}
