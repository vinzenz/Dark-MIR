
#ifndef PROGRAM_H
 #define PROGRAM_H

#define  VERSION "0.02"

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_thread.h>
#include <SDL/SDL_opengl.h>
#include <SDL/SDL_net.h>

#include <math.h>

#define OK 0 
#define FAIL -1 

#define ROOT "./" 

#define WIN_FLAGS SDL_HWSURFACE|SDL_ANYFORMAT|SDL_DOUBLEBUF|SDL_HWPALETTE|SDL_HWACCEL//|SDL_NOFRAME

#define SDL_SUBSYSTEMS SDL_INIT_VIDEO|SDL_INIT_TIMER  

#define SDL_SERVER_SUBSYSTEMS SDL_INIT_TIMER  

#define WIN_TITLE "Dark MIR"  

#define VYCHOZI_JAZYK	"en"// vychozi nastaveni se uplatni pokud systemovy jazyk nebude definovan 
			//nebo nebudo odpovidat jedne z moznosti 

#define VYCHOZI_ROZLISENI   1 


#define MAX_RES	6

#define WIDTH	 rozliseni[nastavene_rozliseni].W // vychozi rozliseni
#define HEIGHT   rozliseni[nastavene_rozliseni].H

#define WIDTH0	 800 
#define HEIGHT0  600

#define WIDTH1	1024 
#define HEIGHT1  768

#define WIDTH2	1280
#define HEIGHT2 1024

#define WIDTH3	1280
#define HEIGHT3 768

#define WIDTH4	1440
#define HEIGHT4  900

#define WIDTH5	1366
#define HEIGHT5  768

#define COLOR   24 	// bits



#define FONT_SIZE 12


//==============================================================================
// Macros
//==============================================================================
#define D_OUT stderr

#define ERROR(arg) fprintf(stderr, " ERROR: %s\n", (arg));
#define DEBUG(arg) fprintf(D_OUT, " DEBUG: %s\n", (arg));

//==============================================================================
// Global vriables
//==============================================================================

short nastavene_rozliseni;
#define COLOR   24 	// bits



#define FONT_SIZE 12


//==============================================================================
// Macros
//==============================================================================
#define D_OUT stderr

#define ERROR(arg) fprintf(stderr, " ERROR: %s\n", (arg));
#define DEBUG(arg) fprintf(D_OUT, " DEBUG: %s\n", (arg));

//==============================================================================
// Global vriables
//==============================================================================

short nastavene_rozliseni;
char F; 		// detekce jeli fullscreen

char *jazyk;	  	// kod jazyka
char *j;

char m_text[16][32]; 		// texty tlacitek v menu
char konfigurace[80][32]; 	// nacteny konfiguracni soubor

struct R {
	int W;	
	int H;
	short X;	
};

struct R rozliseni[MAX_RES]; 

char pauza;

double X,Y;
Uint8 ID;

//==============================================================================
// Function prototypes
//==============================================================================

int Read_configuration();
int Init();
int Exit_game(int RC);



#define HELP_MSG "\
DARK MIR version 0.02\n\
2007-2011 copyright by (c) Alexej alexej.x@mail.ru GNU GPL-2 \n\
 ./mir [-r N] [-f] [-n NICK] < IP_address of server / domain name >\n\
      -h		show this help    	\n\
      -n NICK	sets your nickname	\n\
      -f		fullscreen    		\n\
      -r NUM		resolution(default 1) 	\n\
      0 = 800x600;\n\
      1 = 1024x768;\n\
      2 = 1280x1024;\n\
      3 = 1280x800;\n\
      4 = 1440x900;\n\
"


// DEBUG PURPOSE MESSAGES
#define POINT(N) printf("POINT: %3d\n",(N)); fflush(stdout);




#define CENTRAL_GAME_SERVER "undergroundlab.cz"
#define CONFIGURATION_FILE "CONFIG"

#endif
