/*
 * File: _coder_BayesCurFit_api.h
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 23-Feb-2017 20:46:04
 */

#ifndef ___CODER_BAYESCURFIT_API_H__
#define ___CODER_BAYESCURFIT_API_H__

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_BayesCurFit_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void BayesCurFit(real_T x[1024], real_T t[1024], real32_T size, real32_T
  M, real_T x_new, real_T *m, real_T *b_std);
extern void BayesCurFit_api(const mxArray *prhs[5], const mxArray *plhs[2]);
extern void BayesCurFit_atexit(void);
extern void BayesCurFit_initialize(void);
extern void BayesCurFit_terminate(void);
extern void BayesCurFit_xil_terminate(void);

#endif

/*
 * File trailer for _coder_BayesCurFit_api.h
 *
 * [EOF]
 */
