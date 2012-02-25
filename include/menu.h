#ifndef MENU_H
  #define MENU_H

#define CONFIG_ITEMS_MAX 32




//==============================================================================
// Global types
//==============================================================================
struct menu_item_struct{
  int alive;

  // Activated image
  SDL_Surface* img_a;    

  // Passive image
  SDL_Surface* img_p;    

  // Coordinates
  int x;
  int y;

  int active;
};
typedef struct menu_item_struct menu_item;


//==============================================================================
// Global variables
//==============================================================================
  char status_line[256];
  char configure_list[CONFIG_ITEMS_MAX][81];

//==============================================================================
// Global functions
//==============================================================================

  int Menu();
  int Configure();
  int Connect();
  int Help();

  int Message(const char *msg);


#define MAX_BUTTONS 10
#define MAX_ITEMS 64
SDL_Surface *menu_button[MAX_BUTTONS];
menu_item item[MAX_ITEMS];


//==============================================================================
#endif

/* end of menu.h */
