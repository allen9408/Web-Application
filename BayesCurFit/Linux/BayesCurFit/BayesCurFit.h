/*
 * File: BayesCurFit.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 23-Feb-2017 20:46:04
 */

#ifndef __BAYESCURFIT_H__
#define __BAYESCURFIT_H__

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
extern void BayesCurFit(const double x[1024], const double t[1024], float size,
  float M, double x_new, double *m, double *b_std);

#endif

/*
 * File trailer for BayesCurFit.h
 *
 * [EOF]
 */
