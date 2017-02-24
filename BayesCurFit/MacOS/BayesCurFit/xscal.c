/*
 * File: xscal.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 23-Feb-2017 21:47:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BayesCurFit.h"
#include "xscal.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                double a
 *                emxArray_real_T *x
 *                int ix0
 * Return Type  : void
 */
void xscal(int n, double a, emxArray_real_T *x, int ix0)
{
  int i4;
  int k;
  i4 = (ix0 + n) - 1;
  for (k = ix0; k <= i4; k++) {
    x->data[k - 1] *= a;
  }
}

/*
 * File trailer for xscal.c
 *
 * [EOF]
 */
