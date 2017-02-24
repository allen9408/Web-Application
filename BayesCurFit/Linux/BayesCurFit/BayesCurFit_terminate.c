/*
 * File: BayesCurFit_terminate.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 23-Feb-2017 20:46:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BayesCurFit.h"
#include "BayesCurFit_terminate.h"
#include "BayesCurFit_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void BayesCurFit_terminate(void)
{
  omp_destroy_nest_lock(&emlrtNestLockGlobal);
}

/*
 * File trailer for BayesCurFit_terminate.c
 *
 * [EOF]
 */
