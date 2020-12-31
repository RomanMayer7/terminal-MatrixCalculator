/******************************************************************************
"mat.h"

MATRIX CMD CALCULATOR
by Roman Meyerson ,December 2020
-------------------------------------------------------------------------------
Definitions of Matrix Operations
*******************************************************************************/

typedef float matrix;
typedef struct  params params_container;

/* Returning pointer to an matrix */
matrix* get_matrix(char* matrix_name);

/* Reseting elements in the matrix*/
void reset_mat_elements(matrix* mat);

/* Storing elements in the matrix*/
void read_mat(params_container* cmd_parms);

/* Printing elements of the matrix*/
void print_mat(params_container* cmd_parms);

/* Adding two matrices,storing result in third matrix*/
void add_mat(params_container* cmd_parms);

/* Subtracting two matrices,storing result in third matrix*/
void sub_mat(params_container* cmd_parms);

/* Multiplying two matrices,storing result in third matrix*/
void mul_mat(params_container* cmd_parms);

/* Multiplying a matrix by scalar,storing result in third matrix*/
void mul_scalar(params_container* cmd_parms);

/* Transposing the matrix,storing result in other matrix*/
void trans_mat(params_container* cmd_parms);
