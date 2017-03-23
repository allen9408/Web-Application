/*
 * File: eml_rand_shr3cong_stateful.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 22-Mar-2017 18:13:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BP.h"
#include "eml_rand_shr3cong_stateful.h"
#include "BP_data.h"

/* Function Definitions */

/*
 * Arguments    : void
 * Return Type  : void
 */
void eml_rand_shr3cong_stateful_init(void)
{
  int i1;
  for (i1 = 0; i1 < 2; i1++) {
    b_state[i1] = 362436069U + 158852560U * i1;
  }
}

/*
 * File trailer for eml_rand_shr3cong_stateful.c
 *
 * [EOF]
 */
