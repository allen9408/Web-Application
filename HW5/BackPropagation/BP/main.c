/*
 * File: main.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 22-Mar-2017 17:40:37
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
#include "BP.h"
#include "main.h"
#include "BP_terminate.h"
#include "BP_initialize.h"
#include <stdio.h>

/* Function Declarations */
static void argInit_1x4_real_T(double result[4]);
static void argInit_4x2_real_T(double result[8]);
static float argInit_real32_T(void);
static double argInit_real_T(void);
static void main_BP(float rate, int maxTimes, float target);

/* Function Definitions */

/*
 * Arguments    : double result[4]
 * Return Type  : void
 */
static void argInit_1x4_real_T(double result[4])
{
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx1 = 0; idx1 < 4; idx1++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx1] = argInit_real_T();
  }
}

/*
 * Arguments    : double result[8]
 * Return Type  : void
 */
static void argInit_4x2_real_T(double result[8])
{
  int idx0;
  int idx1;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 4; idx0++) {
    for (idx1 = 0; idx1 < 2; idx1++) {
      /* Set the value of the array element.
         Change this value to the value that the application requires. */
      result[idx0 + (idx1 << 2)] = argInit_real_T();
    }
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
static void main_BP(float rate, int maxTimes, float target)
{
  double dv0[8]= {0,0,0,1,1,0,1,1};
  double dv1[4] = {0,1,1,0};
  double w_init[2];
  double err_1;
  double w_final[2];
  double err_final;
  double times;

  /* Initialize function 'BP' input arguments. */
  /* Initialize function input argument 'x'. */
  /* Initialize function input argument 't'. */
  /* Call the entry-point 'BP'. */
  // argInit_4x2_real_T(dv0);
  // argInit_1x4_real_T(dv1);

  BP(dv0, dv1, rate, maxTimes, target, w_init,
     &err_1, w_final, &err_final, &times);

  printf("First batch error: %f\n", err_1);
  printf("Final error: %f\n", err_final);
  printf("Training epoch: %d\n", (int) times);
  printf("Initial weights: %f, %f\n", w_init[0], w_init[1]);
  printf("Final weights: %f, %f\n", w_final[0], w_final[1]);
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

  double rate = atof(argv[1]);
  int maxTimes = atoi(argv[2]);
  double target = atof(argv[3]);
  /* Initialize the application.
     You do not need to do this more than one time. */
  BP_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_BP(rate, maxTimes, target);

  /* Terminate the application.
     You do not need to do this more than one time. */
  BP_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
