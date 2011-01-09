/*************************************************************************** 
 *  Dark Mir                                                               *
 *	version 0.01                                                           *
 *   Copyright (C) 2007-2010 by Filip 'Alexej' Kesner alexej.x@mail.ru     *
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
#include "menu.h"

#include <getopt.h>



int	Init(int w, int h, int bits, int full);
int NET_Init(const char *hostname);	
int	Get_Opts(int argc, char **argv);



//==============================================================================
int main(int argc,char *argv[]){
//==============================================================================

	
  strcpy(nick, "PLAYER_Alexej");
  nastavene_rozliseni = VYCHOZI_ROZLISENI;
  strcpy(hostname, CENTRAL_GAME_SERVER);

	Get_Opts(argc, argv);  
	
//	Nacti_konfiguraci();
	
//	Nacti_jazyk(p_lang);


	Nastav_rozliseni();   
	Zmena_rozliseni(nastavene_rozliseni);

	Menu();

	POINT(111);
	POINT(211);


//	Init(WIDTH, HEIGHT, COLOR, 0);
    
  // === GAME LOOP === 
	Vesmir();	 
	 
  // === DESTRUCTOR === 
	TTF_Quit();
	SDL_Quit();

	return OK;
}




//==============================================================================
int	Get_Opts(int argc, char **argv){
//==============================================================================
  char *p_lang;
	

	// argumenty 
  while (1) {

	 int c = getopt(argc, argv, "hfer:l:n:");
	 if (c == -1) {
	      return OK;
	    } else

   switch (c) {
	  case 'h':
		    printf("%s\n", HELP_MSG);
	      exit(EXIT_SUCCESS);
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

	  case 'n':
		strncpy(nick, optarg, NICKNAME_MAX);
	  
	  
	  
	  }
   }

	// The last parameter is hostname of server //
	if(argv[argc-1] != NULL)
			strncpy(hostname, argv[argc-1], HOSTNAME_MAX);

	return OK;
}






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

	console_font = TTF_OpenFont(ROOT"data/console.ttf", FONT_SIZE);
	if(!console_font){
			  printf("Unable to open font: %s\n", TTF_GetError());
			  return FAIL;
	}
	TTF_SetFontStyle(console_font, TTF_STYLE_NORMAL);


    SDL_ShowCursor(SDL_DISABLE); 
	if(F==1)SDL_WM_ToggleFullScreen(screen);	

  return OK;	
}

//==============================================================================
