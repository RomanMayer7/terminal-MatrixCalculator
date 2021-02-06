/******************************************************************************
"mymat.c"

MATRIX CMD CALCULATOR
by Roman Meyerson ,December 2020
-------------------------------------------------------------------------------
Main Program Logic
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "mat.h"
#include "utils.h"

#define SIZE 4
#define NUM_ELEMENTS SIZE*SIZE



bool stop_program=false;

enum func_types{read_matrix, print_matrix ,add_matrix ,sub_matrix ,mul_matrix ,mult_scalar ,trans_matrix, stop_it,help_command};

enum func_types get_enum_value(char * val) {
    static char const * e_test_str[] = {"read_mat", "print_mat" ,"add_mat" ,"sub_mat" ,"mul_mat" ,"mul_scalar" ,"trans_mat", "stop","help"};
    for (int i = 0; i < 9; ++i)
        if (!strcmp(e_test_str[i], val))
            return i;
    return 9;
 }



typedef struct  params {
matrix *first_mat_parm;
matrix *second_mat_parm;
float scalar_parm;
float elements[16];
matrix *result_mat_param;
}params_container;



void print_help();
matrix* get_matrix(char* matrix_name);
int check_command(char* command);
bool validate_params(char* command,char* input,params_container* cmd_parms);
bool validate_input(char* _parameters);
void reset_elements_arr(params_container* cmd_parms);
void stop(params_container* cmd_parms);
void help(params_container* cmd_parms);
void not_valid(params_container* cmd_parms);


struct {
char *name;
void (*func)(params_container* cmd_parms);
} cmd[]={
  {"read_mat",read_mat},
  {"print_mat",print_mat},
  {"add_mat",add_mat},
  {"sub_mat",sub_mat},
  {"mul_mat",mul_mat},
  {"mul_scalar",mul_scalar},
  {"trans_mat",trans_mat},
  {"stop",stop},
  {"help",help},
  {"not_valid",NULL}
};



int main()
{

  /*int i;*/
  int command_id;
  char command_string[20];
  char parameters_string[100];
  params_container params_struct;

  printf("*************************<MATRIX CALCULATOR for Terminal or CMD - version 1.1 by Roman Meyerson>************************\n");
  ;printf("\n");
  printf("Please type 'help' to see the list of available commands\n");printf("\n");
  while(!stop_program)
  {
      printf("\n");
	  printf("Please enter your Command:\n");


    if (scanf("%s",command_string)==1)/*read input until "space" to get command_string*/
    {


         command_id = check_command(command_string);

	     if(command_id!=9)/*check if command exist*/

          {
          /*Read rest of the input to get parameters_string*/
           if (fgets(parameters_string, sizeof(parameters_string), stdin) != NULL)
           {


              /*printf("params with spaces:%s\n",parameters_string);*/
              remove_spaces(parameters_string);/*clean spaces from input*/


			  bool result=validate_input(parameters_string);
			  if(result)
              {
                 // remove newline from the end , which fgets puts by default
                 int len = strlen(parameters_string);
                 if( parameters_string[len-1] == '\n' )
                   parameters_string[len-1] = 0;

                reset_elements_arr(&params_struct);
                result = validate_params(command_string,parameters_string,&params_struct);
                if(result)
                {

                    (*(cmd[command_id].func))(&params_struct);
                }
              }
           }

          }
          else
          {

              clear_stdin();

          }

     }

   }
 return 0;
}



void print_help()
{
  printf("-----------------AVAILABLE MATRICES:------------------------------------\n");
  printf("            MAT_A, MAT_B, MAT_C, MAT_D, MAT_E, MAT_F \n");
  printf("\n");
  printf("-----------------COMMANDS:------------------------------------\n");
  printf("         <read_mat MATRIX_NAME,SCALAR_NAME1,SCALAR_NAME2...>\n");     printf("-read matrix elements from the standart input\n");printf("\n");
  printf("         <print_mat MATRIX_NAME>\n");                                 printf("-read matrix elements to the  standart output\n");printf("\n");
  printf("         <add_mat MATRIX1_NAME,MATRIX2_NAME,RESULT_MATRIX_NAME>\n");  printf("-add two matrices and save the result in the third one\n");printf("\n");
  printf("         <sub_mat MATRIX1_NAME,MATRIX2_NAME,RESULT_MATRIX_NAME>\n"); printf(" -subtract two matrices and save the result in the third one\n");printf("\n");
  printf("         <mul_mat MATRIX1_NAME,MATRIX2_NAME,RESULT_MATRIX_NAME>\n");  printf("-multiply two matrices and save the result in the third one\n");printf("\n");
  printf("         <mul_scalar MATRIX_NAME,SCALAR_NAME,RESULT_MATRIX_NAME>\n"); printf("-multiply a matrix by scalar and save the result in the third one\n");printf("\n");
  printf("         <trans_mat MATRIX_NAME,RESULT_MATRIX_NAME>\n");              printf("-transpose a matrix  and save the result in the third one\n");printf("\n");
  printf("         <help>  - print help section with list of all available commands\n");
  printf("         <stop>  - exit program by stopping it's execution\n");
  printf("-------------------------------------------\n");

}


int check_command(char* command)
{
    int i;
	for(i=0; cmd[i].func!=NULL; i++)

    if (strcmp(command,cmd[i].name)==0)
     break;

    if (cmd[i].func==NULL)
	{
     fprintf(stderr,"ERROR: Command '%s' does not exist\n",command);
     return 9;
	}
    else
     {
       if (strcmp(command,"stop")==0)
       {
	      stop_program=true;
	      return 9;
        }
		else if (strcmp(command,"help")==0)
		{
          print_help();
	      return 9;
		}
     else
       //printf("%s\n",cmd[i].name);
	    return i;
    }

}



bool validate_params(char* command,char* input,params_container* cmd_parms)
{
     matrix *first_matrix;
	 matrix *second_matrix;
	 matrix *result_matrix;
     float number;
	 char* param_name;

	switch(get_enum_value(command))
   {

       case 0 : /* ******************************** read_mat ********************************* */
        {

		   /* ------------------------- get matrix name from the parameters list -------------------------*/
            if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }

		    char** input_s=&input;
	        param_name = strTok(input_s, ",");


		    first_matrix=get_matrix(param_name);
            if (first_matrix==NULL) return false;
			cmd_parms->first_mat_parm=first_matrix;

		    /*------------------------- get values of matrix elements *-------------------------------------------*/

		   /* try get value of first  element from comma separated string*/

            if (input!=0)
	        {
              int i=0;
              param_name = strtok(input, ",");

		    /*check if number*/
            if(!check_ifnumber(param_name))
             {
               fprintf(stderr,"ERROR: Argument is not a real number\n");
               return false;
             }

			else cmd_parms->elements[i]=atof(param_name);

		  	/* the following loop gets the rest of the elements until the
	           end of the message. NULL must be used to get tokens from the previous string now */
		   	while ((param_name = strtok(NULL, ",")) != NULL)
			{
		     /*check if number*/
			 if(!check_ifnumber(param_name))
             {
               fprintf(stderr,"ERROR: Argument is not a real number\n");
               return false;
             }
			  else
			  {
				  i++;
				  cmd_parms->elements[i]=atof(param_name);
			  }

			}
            int j=i+1;
			/*fill the rest of element values with 0 */
			for(j;j<NUM_ELEMENTS;j++)
		    {

			   cmd_parms->elements[j]=0;
		    }
		    return true;
	        }
	        else
            {
              fprintf(stderr,"ERROR: Missing argument\n");
              return false;
            }
		  /*------------------------------------------------------------------------------------------------------*/
	    }
         break;

      case 1 : /* ********************************  print_mat ******************************** */
	  {
		   /* ------------------------- get matrix name from the parameters list ------------------------- */
            if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
	       param_name = strtok(input, ",");
		   first_matrix=get_matrix(param_name);
           if (first_matrix==NULL) return false;

		   else
           {
           cmd_parms->first_mat_parm=first_matrix;
           return true;
           }

	  }
      break;


      case 2 : /* ******************************** add_mat ******************************** */
	  {
	        /* ----------------------extract matrices names from the parameters list and check them ------------------------- */
            if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
	       param_name = strtok(input, ",");
		   first_matrix=get_matrix(param_name);
           if (first_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   second_matrix=get_matrix(param_name);
           if (second_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   result_matrix=get_matrix(param_name);
           if (result_matrix==NULL) return false;

            cmd_parms->first_mat_parm=first_matrix;
            cmd_parms->second_mat_parm=second_matrix;
		    cmd_parms->result_mat_param=result_matrix;

	        return true;
	  }

       case 3 : /* ******************************** sub_mat ******************************** */
	  {
	        /* ----------------------extract matrices names from the parameters list and check them ------------------------- */
            if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
	       param_name = strtok(input, ",");
		   first_matrix=get_matrix(param_name);
           if (first_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   second_matrix=get_matrix(param_name);
           if (second_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   result_matrix=get_matrix(param_name);
           if (result_matrix==NULL) return false;

            cmd_parms->first_mat_parm=first_matrix;
            cmd_parms->second_mat_parm=second_matrix;
		    cmd_parms->result_mat_param=result_matrix;

	        return true;
	  }

	  break;

      case 4 : /* ******************************** mul_mat ******************************** */
	  {
	        /* ----------------------extract matrices names from the parameters list and check them ------------------------- */
            if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
	       param_name = strtok(input, ",");
		   first_matrix=get_matrix(param_name);
           if (first_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   second_matrix=get_matrix(param_name);
           if (second_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   result_matrix=get_matrix(param_name);
           if (result_matrix==NULL) return false;

            cmd_parms->first_mat_parm=first_matrix;
            cmd_parms->second_mat_parm=second_matrix;
		    cmd_parms->result_mat_param=result_matrix;

	        return true;
	  }

      case 5 : /* ******************************** mul_scalar ******************************** */
	  {
	        /* ----------------------extract matrix name and scalar from the parameters list and check them ------------------------- */
           if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
	       param_name = strtok(input, ",");
		   first_matrix=get_matrix(param_name);
           if (first_matrix==NULL) return false;

            /* try get value of scalar  element from comma separated string*/
		    param_name = strtok(NULL, ",");
            if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		    /*check if number*/
            if(!check_ifnumber(param_name))
             {
               fprintf(stderr,"ERROR: Argument is not a real number\n");
               return false;
             }
            else
             {
				  cmd_parms->scalar_parm=atof(param_name);
             }

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   result_matrix=get_matrix(param_name);
           if (result_matrix==NULL) return false;

            cmd_parms->first_mat_parm=first_matrix;
		    cmd_parms->result_mat_param=result_matrix;

	        return true;
	  }

	  break;

      case 6 : /* ******************************** trans_mat ******************************** */
	  {
	        /* ----------------------extract matrices names from the parameters list and check them ------------------------- */
            if (*input==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
	       param_name = strtok(input, ",");
		   first_matrix=get_matrix(param_name);
           if (first_matrix==NULL) return false;

	       param_name = strtok(NULL, ",");
           if (param_name==0)
	        {
	             fprintf(stderr,"ERROR: Missing argument\n");
	             return false;
	        }
		   result_matrix=get_matrix(param_name);
           if (result_matrix==NULL) return false;

            cmd_parms->first_mat_parm=first_matrix;
		    cmd_parms->result_mat_param=result_matrix;

	        return true;
	  }

	  break;


   }

}


bool validate_input(char* _parameters)

{
     char *lasttoken = strrchr(_parameters, ',');
     if(lasttoken!=NULL)
     {


       if (*(lasttoken+2)=='\0')
       {
         printf("ERROR: Extraneous text after end of command\n");
         return false;
       }
       char *ptr_parameters = _parameters;
       char** strP = &ptr_parameters;
       char *token;
       char* stoken =",";

      while((token=strTok(strP,stoken)))
         {
            remove_spaces(token);

              if(token[0]=='\0')
              {
                printf("ERROR: Multiple consecutive commas\n");
                return false;
              }

          }
       }

    return true;

}

void reset_elements_arr(params_container* cmd_parms)
{

int i;
  for(i=0;i<NUM_ELEMENTS;i++)
  {

    cmd_parms->elements[i]=0;

  }

}

void stop(params_container* cmd_parms){}
void help(params_container* cmd_parms){}
void not_valid(params_container* cmd_parms){}


