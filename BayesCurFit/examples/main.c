/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Feb-2017 15:53:01
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "rt_nonfinite.h"
#include "BayesCurFit.h"
#include "main.h"
#include "BayesCurFit_terminate.h"
#include "BayesCurFit_initialize.h"

/* Function Declarations */
static void argInit_1xd32_real_T(double result_data[], int result_size[2]);
static float argInit_real32_T(void);
static double argInit_real_T(void);
static void main_BayesCurFit(void);

/* Function Definitions */

/*
 * Arguments    : double result_data[]
 *                int result_size[2]
 * Return Type  : void
 */
static void argInit_1xd32_real_T(double result_data[], int result_size[2])
{
  int idx1;

  /* Set the size of the array.
     Change this size to the value that the application requires. */
  result_size[0] = 1;
  result_size[1] = 2;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 2; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result_data[idx1] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : float
 */
static float argInit_real32_T(void)
{
  return 0.0F;
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_BayesCurFit(void)
{
  double x_data[32];
  int x_size[2];
  double t_data[32];
  int t_size[2];
  double p;

  /* Initialize function 'BayesCurFit' input arguments. */
  /* Initialize function input argument 'x'. */
  argInit_1xd32_real_T(x_data, x_size);

  /* Initialize function input argument 't'. */
  argInit_1xd32_real_T(t_data, t_size);

  /* Call the entry-point 'BayesCurFit'. */
  p = BayesCurFit(x_data, x_size, t_data, t_size, argInit_real32_T(),
                  argInit_real_T());
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  BayesCurFit_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_BayesCurFit();

  /* Terminate the application.
     You do not need to do this more than one time. */
  BayesCurFit_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
