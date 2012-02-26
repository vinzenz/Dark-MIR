// READING CONFIGURATION FILE

#include "program.h"
#include "client.h"



#define RLBUFF_SIZE 1024 
//==============================================================================
// PROTOTYPES
//==============================================================================
int Parser(char *line);
int ReadLine(FILE *file, char **dst);


  static char buffer[RLBUFF_SIZE];

//==============================================================================
int Read_configuration(){
//==============================================================================
// RC = return code
  
  FILE *config_file;
  char *line;
  int line_counter = 1;
  MIR_LOG_DEBUG("Configuration starting");
  
  config_file = fopen(CONFIGURATION_FILE, "r");
  if(config_file == NULL){
    MIR_LOG_ERROR("FAILED TO OPEN CONFIGURATION FILE");
    return FAIL;
  }

  
  while(ReadLine(config_file, &line) > 0){

    if(Parser(line) != OK){
      MIR_LOG_ERROR(" parsing configuration file")
      fprintf(stderr, "  line: %d\n", line_counter); 
    }
    line_counter++;

  }


  fprintf(stderr, "  lines parsed: %d\n", line_counter); 
  fclose(config_file);

  MIR_LOG_DEBUG("Configuration loaded ... [ OK ]");
  return OK;
}

//==============================================================================
int Parser(char *line){
//==============================================================================
  int RC = -1;
  int i = 0;
 
  if(line == NULL){ 
    MIR_LOG_ERROR("NULL pointer used");
    return FAIL;  
  }


  // Skip white space from begining of line
  while(isspace(line[0])) { 
    line++;
  }  

  // Skip comments
  if(line[0] == '#') return OK;

  // Skip Void line
  if(line[0] == '\n') return OK;
  if(line[0] == '\0') return OK;

  // Chomp EOL
  line[strlen(line) - 1] = '\0';

  //printf("$ %s\n",line);

  if (strstr(line, "resolution") != NULL){ 
      nastavene_rozliseni = atoi(strstr(line, "=") + 1) % 5;
      RC = OK;
      MIR_LOG_DEBUG(" -- RESOLUTION CONFIGURED");
  
  }
  if (strstr(line, "nickname") != NULL){ 
      strcpy(nick, strstr(line, "=") + 1);
      nick[strlen(nick)] = '\0';
      RC = OK;
      MIR_LOG_DEBUG(" -- NICKNAME CONFIGURED");
  }

  return RC;
}
//==============================================================================

//==============================================================================
int ReadLine(FILE *file, char **dst){
//==============================================================================

  int counter  = -1;
  buffer[0] = 0;

  if(fgets(buffer, RLBUFF_SIZE - 2, file) != NULL){
    *dst = buffer; 
    //MIR_LOG_DEBUG("readed")
    return 1;
  }

  return counter;
}
//==============================================================================
// EOF
