/******************************************************************************
"utils.h"

MATRIX CMD CALCULATOR
by Roman Meyerson ,December 2020
-------------------------------------------------------------------------------
Definitions of Utilities Functions\Helpers
*******************************************************************************/

typedef enum {false, true} bool;

//Checks if string is actual number
bool check_ifnumber(char* str);

//Special version of library function strtok
char* strTok(char** newString, char* delimiter);

//clears stdin by consuming what left in there
void clear_stdin ();

//removing all spaces in the string
void remove_spaces(char *str);
