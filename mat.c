/******************************************************************************
"mat.c"

MATRIX CMD CALCULATOR
by Roman Meyerson ,December 2020
-------------------------------------------------------------------------------
Implementations of Matrix Operations
*******************************************************************************/
#include <stddef.h>
#include <stdio.h>
#define SIZE 4


typedef float matrix[SIZE][SIZE];

typedef enum {false, true} bool;

matrix mat_a,mat_b,mat_c,mat_d,mat_e,mat_f;


struct {
 char* name;
 matrix *mat;} mats[]={
       {"MAT_A",&mat_a},
       {"MAT_B",&mat_b},
       {"MAT_C",&mat_c},
       {"MAT_D",&mat_d},
       {"MAT_E",&mat_e},
       {"MAT_F",&mat_f},
       {"mat_a",&mat_a},
       {"mat_b",&mat_b},
       {"mat_c",&mat_c},
       {"mat_d",&mat_d},
       {"mat_e",&mat_e},
       {"mat_f",&mat_f},
       {"#",NULL}
};

 typedef struct  params {
matrix *first_mat_parm;
matrix *second_mat_parm;
float scalar_parm;
float elements[16];
matrix *result_mat_param;
}params_container;


//---------------------------------------------------------------------------------------------------------------------------------

matrix* get_matrix(char* matrix_name)
{
    int i;

    for(i=0; mats[i].mat!=NULL; i++)

    if (strcmp(matrix_name,mats[i].name)==0)
     break;

    if (mats[i].mat==NULL)
	{
     fprintf(stderr,"Undefined matrix name:%s\n",matrix_name);
     return NULL;
	}
    else
	return mats[i].mat;

}


void reset_mat_elements(matrix* mat)
{

  int i,j;
  for(i=0;i<SIZE;i++)
  {
    for(j=0;j<SIZE;j++)
     {
       mat[0][i][j]=0;
     }
  }
}

void read_mat(params_container* cmd_parms)
{

    /* Storing elements in the matrix*/
    int i,j;
  for(i=0;i<SIZE;i++)
  {
      for(j=0;j<SIZE;j++)
      {
          int var=cmd_parms->elements[(i*SIZE)+j];


          matrix* arr=cmd_parms->first_mat_parm;
          arr[0][i][j]=var;

      }
  }

}

void print_mat(params_container* cmd_parms)
/* Printing elements of the matrix*/
{
 int i,j;
printf("-------------------------------------------\n");
  for(i=0;i<SIZE;i++)
  {
      printf("     ");
      for(j=0;j<SIZE;j++)
      {
        printf("%7.2f",cmd_parms->first_mat_parm[0][i][j]);

      }
      printf("\n");
  }
  printf("-------------------------------------------\n");


}

void add_mat(params_container* cmd_parms)
{
  /*Reset the result matrix before performing operation */
   reset_mat_elements(cmd_parms->result_mat_param);

  /* Adding two matrices,storing result in third matrix*/
  int i,j;
  for(i=0;i<SIZE;i++)
  {
      for(j=0;j<SIZE;j++)
      {
          float var1=cmd_parms->first_mat_parm[0][i][j];
          float var2=cmd_parms->second_mat_parm[0][i][j];

          matrix* arr=cmd_parms->result_mat_param;
          arr[0][i][j]=var1+var2;

      }
  }

}

void sub_mat(params_container* cmd_parms)
{
   /*Reset the result matrix before performing operation */
   reset_mat_elements(cmd_parms->result_mat_param);

  /* Subtracting two matrices,storing result in third matrix*/
  int i,j;
  for(i=0;i<SIZE;i++)
  {
      for(j=0;j<SIZE;j++)
      {
          float var1=cmd_parms->first_mat_parm[0][i][j];
          float var2=cmd_parms->second_mat_parm[0][i][j];

          matrix* arr=cmd_parms->result_mat_param;
          arr[0][i][j]=var1-var2;

      }
  }

}

void mul_mat(params_container* cmd_parms)
{
   /*Reset the result matrix before performing operation */
   reset_mat_elements(cmd_parms->result_mat_param);

  /* Multiplying two matrices,storing result in third matrix*/
  int i,j,k;
  for(i=0;i<SIZE;i++)
  {
      for(j=0;j<SIZE;j++)
      {

         for(k=0;k<SIZE;k++)
         {
          float var1=cmd_parms->first_mat_parm[0][i][k];
          float var2=cmd_parms->second_mat_parm[0][k][j];

          matrix* arr=cmd_parms->result_mat_param;
          arr[0][i][j]+=var1*var2;
         }

      }
  }

}

void mul_scalar(params_container* cmd_parms)
{
   /*Reset the result matrix before performing operation */
   reset_mat_elements(cmd_parms->result_mat_param);

  /* Multiplying a matrix by scalar,storing result in third matrix*/
  int i,j;
  for(i=0;i<SIZE;i++)
  {
      for(j=0;j<SIZE;j++)
      {
          float var1=cmd_parms->scalar_parm;
          float var2=cmd_parms->first_mat_parm[0][i][j];

          matrix* arr=cmd_parms->result_mat_param;
          arr[0][i][j]=var1*var2;

      }
  }

}

void trans_mat(params_container* cmd_parms)
{
   /*Reset the result matrix before performing operation */
   reset_mat_elements(cmd_parms->result_mat_param);

  /* Transposing the matrix,storing result in other matrix*/
  int i,j;
  for(i=0;i<SIZE;i++)
  {
      for(j=0;j<SIZE;j++)
      {

          float var1=cmd_parms->first_mat_parm[0][i][j];
          matrix* arr=cmd_parms->result_mat_param;
          arr[0][j][i]+=var1;

      }
  }

}
