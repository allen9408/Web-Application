/*
 * File: _coder_BP_api.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 22-Mar-2017 18:13:22
 */

#ifndef ___CODER_BP_API_H__
#define ___CODER_BP_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_BP_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void BP(real_T x[8], real_T t[4], real_T rate, real32_T max_times, real_T
               target, real_T w_init[2], real_T *err_1, real_T w_final[2],
               real_T *err_final, real_T *times);
extern void BP_api(const mxArray *prhs[5], const mxArray *plhs[5]);
extern void BP_atexit(void);
extern void BP_initialize(void);
extern void BP_terminate(void);
extern void BP_xil_terminate(void);

#endif

/*
 * File trailer for _coder_BP_api.h
 *
 * [EOF]
 */
