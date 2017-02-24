/*
 * File: BayesCurFit_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 23-Feb-2017 20:46:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BayesCurFit.h"
#include "BayesCurFit_initialize.h"
#include "BayesCurFit_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void BayesCurFit_initialize(void)
{
  rt_InitInfAndNaN(8U);
  omp_init_nest_lock(&emlrtNestLockGlobal);
}

/*
 * File trailer for BayesCurFit_initialize.c
 *
 * [EOF]
 */
