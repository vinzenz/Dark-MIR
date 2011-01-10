#ifndef MENU_H
  #define MENU_H

#define CONFIG_ITEMS_MAX 6
//==============================================================================
// Global variables
//==============================================================================
  char status_line[256];
  char configure_list[CONFIG_ITEMS_MAX][256];

//==============================================================================
// Global functions
//==============================================================================

  int Menu();
  int Configure();
  int Connect();

  int Message(const char *msg);


#define MAX_BUTTONS 10
SDL_Surface *menu_button[MAX_BUTTONS];


//==============================================================================
#endif

/* end of menu.h */
