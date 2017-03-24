/*
 * File: BP.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Mar-2017 02:25:18
 */

#ifndef __BP_H__
#define __BP_H__

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtwtypes.h"
#include "BP_types.h"

/* Function Declarations */
extern void BP(const double x[8], const double t[4], double rate, float
               max_times, double target, double w_init[2], double *err_1, double
               w_final[2], double *err_final, double *times);

#endif

/*
 * File trailer for BP.h
 *
 * [EOF]
 */
