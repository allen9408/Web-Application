/*
 * File: BP_initialize.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 22-Mar-2017 18:13:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BP.h"
#include "BP_initialize.h"
#include "eml_rand_shr3cong_stateful.h"
#include "eml_rand_mcg16807_stateful.h"
#include "eml_rand.h"
#include "eml_rand_mt19937ar_stateful.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void BP_initialize(void)
{
  rt_InitInfAndNaN(8U);
  state_not_empty_init();
  eml_rand_init();
  eml_rand_mcg16807_stateful_init();
  eml_rand_shr3cong_stateful_init();
}

/*
 * File trailer for BP_initialize.c
 *
 * [EOF]
 */
