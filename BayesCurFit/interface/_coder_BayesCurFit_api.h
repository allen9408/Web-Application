/*
 * File: _coder_BayesCurFit_api.h
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 16-Feb-2017 15:53:01
 */

#ifndef _CODER_BAYESCURFIT_API_H
#define _CODER_BAYESCURFIT_API_H

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
extern real_T BayesCurFit(real_T x_data[], int32_T x_size[2], real_T t_data[],
  int32_T t_size[2], real32_T N, real_T x_new);
extern void BayesCurFit_api(const mxArray *prhs[4], const mxArray *plhs[1]);
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
