/******************************************************************************
"utils.c"

MATRIX CMD CALCULATOR
by Roman Meyerson ,December 2020
-------------------------------------------------------------------------------
Implementations of Utilities Functions\Helpers
*******************************************************************************/

typedef enum {false, true} bool;

//Checks if string is actual number



int check_ifnumber(char *s) {
    const char *ptr = s;
    float x = strtod(ptr, &s);

    //check if converted to long int
    if (*s == 0) {
        return true;
    }
    else {
        return false;
    }
    return false;
}


//Special version of library function strtok
char* strTok(char** newString, char* delimiter)
{
    char* string = *newString;
    char* delimiterFound = (char*) 0;
    int tokLenght = 0;
    char* tok = (char*) 0;

    if(!string) return (char*) 0;

    delimiterFound = strstr(string, delimiter);

    if(delimiterFound){
        tokLenght = delimiterFound-string;
    }else{
        tokLenght = strlen(string);
    }

    tok = malloc(tokLenght + 1);
    memcpy(tok, string, tokLenght);
    tok[tokLenght] = '\0';

    *newString = delimiterFound ? delimiterFound + strlen(delimiter) : (char*)0;

    return tok;
}

//clears stdin by consuming what left in there
void clear_stdin ()
{ //consume stdin
  while ( getchar() != '\n' );
}


//removing all spaces in the string
void remove_spaces(char *str) {
    // To keep track of non-space character count
    int count = 0;

    // Traverse the given string. If current character
    // is not space, then place it at index 'count++'
    for (int i = 0; str[i]; i++)
        if (str[i] != ' ')
            str[count++] = str[i]; // here count is
                               // incremented
    str[count] = '\0';
}
