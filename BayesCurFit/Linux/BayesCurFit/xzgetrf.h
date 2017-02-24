/*
 * File: xzgetrf.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 23-Feb-2017 20:46:04
 */

#ifndef __XZGETRF_H__
#define __XZGETRF_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "omp.h"
#include "BayesCurFit_types.h"

/* Function Declarations */
extern void xzgetrf(int m, int n, emxArray_real_T *A, int lda, emxArray_int32_T *
                    ipiv, int *info);

#endif

/*
 * File trailer for xzgetrf.h
 *
 * [EOF]
 */
