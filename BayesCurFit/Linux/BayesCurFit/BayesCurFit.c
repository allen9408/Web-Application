/*
 * File: BayesCurFit.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 23-Feb-2017 20:46:04
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BayesCurFit.h"
#include "BayesCurFit_emxutil.h"
#include "mrdivide.h"
#include "xzgetrf.h"
#include "eye.h"

/* Function Declarations */
static float rt_powf_snf(float u0, float u1);

/* Function Definitions */

/*
 * Arguments    : float u0
 *                float u1
 * Return Type  : float
 */
static float rt_powf_snf(float u0, float u1)
{
  float y;
  float f0;
  float f1;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = ((real32_T)rtNaN);
  } else {
    f0 = (float)fabs(u0);
    f1 = (float)fabs(u1);
    if (rtIsInfF(u1)) {
      if (f0 == 1.0F) {
        y = ((real32_T)rtNaN);
      } else if (f0 > 1.0F) {
        if (u1 > 0.0F) {
          y = ((real32_T)rtInf);
        } else {
          y = 0.0F;
        }
      } else if (u1 > 0.0F) {
        y = 0.0F;
      } else {
        y = ((real32_T)rtInf);
      }
    } else if (f1 == 0.0F) {
      y = 1.0F;
    } else if (f1 == 1.0F) {
      if (u1 > 0.0F) {
        y = u0;
      } else {
        y = 1.0F / u0;
      }
    } else if (u1 == 2.0F) {
      y = u0 * u0;
    } else if ((u1 == 0.5F) && (u0 >= 0.0F)) {
      y = (float)sqrt(u0);
    } else if ((u0 < 0.0F) && (u1 > (float)floor(u1))) {
      y = ((real32_T)rtNaN);
    } else {
      y = (float)pow(u0, u1);
    }
  }

  return y;
}

/*
 * x=zeros(1,size);
 *  t=zeros(1,size);
 *
 *  % xin = fopen(xfile,'r');
 *  x(1,1:size)=load(xfile)';
 *  t(1,1:size)=load(tfile)'
 *  % for i = 1:1:size
 *  %     x(1,i) = fgetl(xin);
 *  % end
 *  % tin = fopen(tfile,'r');
 *  % for i=1:1:size
 *  %     t(1,i) = fgetl(tin);
 *  % end
 * Arguments    : const double x[1024]
 *                const double t[1024]
 *                float size
 *                float M
 *                double x_new
 *                double *m
 *                double *b_std
 * Return Type  : void
 */
void BayesCurFit(const double x[1024], const double t[1024], float size, float M,
                 double x_new, double *m, double *b_std)
{
  emxArray_real_T *phi_t;
  int i0;
  int loop_ub;
  emxArray_real_T *phi_sum;
  emxArray_real_T *I;
  emxArray_real_T *tmp_m;
  emxArray_real_T *phi_new_t;
  int i;
  emxArray_int32_T *r0;
  int b_I;
  int i1;
  double a_data[1024];
  double x_data[1024];
  float y;
  float y_data[1024];
  int c_I;
  int k;
  int b_k;
  emxArray_real_T *phi;
  emxArray_real_T *b_phi;
  emxArray_real_T *b_phi_t;
  double d0;
  emxArray_int32_T *ipiv;
  emxArray_real_T *phi_new;
  emxArray_real_T *a;
  double b_y;
  emxInit_real_T(&phi_t, 2);
  i0 = phi_t->size[0] * phi_t->size[1];
  phi_t->size[0] = (int)size;
  phi_t->size[1] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)phi_t, i0, (int)sizeof(double));
  loop_ub = (int)size * (int)(M + 1.0F);
  for (i0 = 0; i0 < loop_ub; i0++) {
    phi_t->data[i0] = 1.0;
  }

  emxInit_real_T(&phi_sum, 2);

  /*  p=zeros(1,N); */
  i0 = phi_sum->size[0] * phi_sum->size[1];
  phi_sum->size[0] = (int)(M + 1.0F);
  phi_sum->size[1] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)phi_sum, i0, (int)sizeof(double));
  loop_ub = (int)(M + 1.0F) * (int)(M + 1.0F);
  for (i0 = 0; i0 < loop_ub; i0++) {
    phi_sum->data[i0] = 0.0;
  }

  emxInit_real_T(&I, 2);
  emxInit_real_T1(&tmp_m, 1);
  eye(M + 1.0F, I);

  /*  s_2 = zeros(size,size); */
  i0 = tmp_m->size[0];
  tmp_m->size[0] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)tmp_m, i0, (int)sizeof(double));
  loop_ub = (int)(M + 1.0F);
  for (i0 = 0; i0 < loop_ub; i0++) {
    tmp_m->data[i0] = 0.0;
  }

  emxInit_real_T(&phi_new_t, 2);
  i0 = phi_new_t->size[0] * phi_new_t->size[1];
  phi_new_t->size[0] = 1;
  phi_new_t->size[1] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)phi_new_t, i0, (int)sizeof(double));
  loop_ub = (int)(M + 1.0F);
  for (i0 = 0; i0 < loop_ub; i0++) {
    phi_new_t->data[i0] = 1.0;
  }

  i0 = (int)M;
  i = 0;
  emxInit_int32_T(&r0, 1);
  while (i <= i0 - 1) {
    if (1.0F > size) {
      loop_ub = 0;
    } else {
      loop_ub = (int)size;
    }

    if (1.0F > size) {
      b_I = 0;
    } else {
      b_I = (int)size;
    }

    i1 = r0->size[0];
    r0->size[0] = b_I;
    emxEnsureCapacity((emxArray__common *)r0, i1, (int)sizeof(int));
    for (i1 = 0; i1 < b_I; i1++) {
      r0->data[i1] = i1;
    }

    i1 = (int)((1.0F + (float)i) + 1.0F) - 1;
    for (b_I = 0; b_I < loop_ub; b_I++) {
      a_data[b_I] = x[b_I];
    }

    for (b_I = 0; b_I < loop_ub; b_I++) {
      x_data[b_I] = a_data[b_I];
    }

    y = 1.0F + (float)i;
    c_I = (short)loop_ub;

#pragma omp parallel for \
 num_threads(omp_get_max_threads()) \
 private(b_k)

    for (k = 1; k <= loop_ub; k++) {
      b_k = k;
      y_data[b_k - 1] = rt_powf_snf((float)x_data[b_k - 1], y);
    }

    for (b_I = 0; b_I < c_I; b_I++) {
      phi_t->data[r0->data[b_I] + phi_t->size[0] * i1] = y_data[b_I];
    }

    i++;
  }

  emxFree_int32_T(&r0);
  emxInit_real_T(&phi, 2);
  i0 = phi->size[0] * phi->size[1];
  phi->size[0] = phi_t->size[1];
  phi->size[1] = phi_t->size[0];
  emxEnsureCapacity((emxArray__common *)phi, i0, (int)sizeof(double));
  loop_ub = phi_t->size[0];
  for (i0 = 0; i0 < loop_ub; i0++) {
    b_I = phi_t->size[1];
    for (i1 = 0; i1 < b_I; i1++) {
      phi->data[i1 + phi->size[0] * i0] = phi_t->data[i0 + phi_t->size[0] * i1];
    }
  }

  i = 0;
  emxInit_real_T1(&b_phi, 1);
  emxInit_real_T(&b_phi_t, 2);
  while (i <= (int)size - 1) {
    if (1.0F > M + 1.0F) {
      loop_ub = 0;
    } else {
      loop_ub = (int)(M + 1.0F);
    }

    if (1.0F > M + 1.0F) {
      b_I = 0;
    } else {
      b_I = (int)(M + 1.0F);
    }

    i0 = b_phi->size[0];
    b_phi->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)b_phi, i0, (int)sizeof(double));
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_phi->data[i0] = phi->data[i0 + phi->size[0] * ((int)(1.0F + (float)i) -
        1)];
    }

    i0 = b_phi_t->size[0] * b_phi_t->size[1];
    b_phi_t->size[0] = 1;
    b_phi_t->size[1] = b_I;
    emxEnsureCapacity((emxArray__common *)b_phi_t, i0, (int)sizeof(double));
    for (i0 = 0; i0 < b_I; i0++) {
      b_phi_t->data[b_phi_t->size[0] * i0] = phi_t->data[((int)(1.0F + (float)i)
        + phi_t->size[0] * i0) - 1];
    }

    i0 = phi_sum->size[0] * phi_sum->size[1];
    phi_sum->size[0] = b_phi->size[0];
    phi_sum->size[1] = b_phi_t->size[1];
    emxEnsureCapacity((emxArray__common *)phi_sum, i0, (int)sizeof(double));
    loop_ub = b_phi->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      b_I = b_phi_t->size[1];
      for (i1 = 0; i1 < b_I; i1++) {
        d0 = b_phi->data[i0] * b_phi_t->data[b_phi_t->size[0] * i1];
        phi_sum->data[i0 + phi_sum->size[0] * i1] += d0;
      }
    }

    i++;
  }

  emxFree_real_T(&b_phi_t);
  emxFree_real_T(&b_phi);
  emxFree_real_T(&phi_t);
  i0 = I->size[0] * I->size[1];
  emxEnsureCapacity((emxArray__common *)I, i0, (int)sizeof(double));
  b_I = I->size[0];
  c_I = I->size[1];
  loop_ub = b_I * c_I;
  for (i0 = 0; i0 < loop_ub; i0++) {
    I->data[i0] = 0.005 * I->data[i0] + 11.1 * phi_sum->data[i0];
  }

  if ((I->size[0] == 0) || (I->size[1] == 0)) {
  } else {
    i0 = phi_sum->size[0] * phi_sum->size[1];
    phi_sum->size[0] = I->size[0];
    phi_sum->size[1] = I->size[1];
    emxEnsureCapacity((emxArray__common *)phi_sum, i0, (int)sizeof(double));
    loop_ub = I->size[0] * I->size[1];
    for (i0 = 0; i0 < loop_ub; i0++) {
      phi_sum->data[i0] = I->data[i0];
    }

    emxInit_int32_T1(&ipiv, 2);
    xzgetrf(I->size[0], I->size[0], phi_sum, I->size[0], ipiv, &b_I);
    emxFree_int32_T(&ipiv);
  }

  emxFree_real_T(&phi_sum);

  /*  test new value */
  for (i = 0; i < (int)M; i++) {
    phi_new_t->data[phi_new_t->size[0] * ((int)((1.0F + (float)i) + 1.0F) - 1)] =
      rt_powf_snf((float)x_new, 1.0F + (float)i);
  }

  emxInit_real_T1(&phi_new, 1);
  i0 = phi_new->size[0];
  phi_new->size[0] = phi_new_t->size[1];
  emxEnsureCapacity((emxArray__common *)phi_new, i0, (int)sizeof(double));
  loop_ub = phi_new_t->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    phi_new->data[i0] = phi_new_t->data[phi_new_t->size[0] * i0];
  }

  emxInit_real_T(&a, 2);
  i0 = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = phi_new_t->size[1];
  emxEnsureCapacity((emxArray__common *)a, i0, (int)sizeof(double));
  loop_ub = phi_new_t->size[0] * phi_new_t->size[1];
  for (i0 = 0; i0 < loop_ub; i0++) {
    a->data[i0] = phi_new_t->data[i0];
  }

  mrdivide(a, I);
  if ((a->size[1] == 1) || (phi_new->size[0] == 1)) {
    b_y = 0.0;
    for (i0 = 0; i0 < a->size[1]; i0++) {
      b_y += a->data[a->size[0] * i0] * phi_new->data[i0];
    }
  } else {
    b_y = 0.0;
    for (i0 = 0; i0 < a->size[1]; i0++) {
      b_y += a->data[a->size[0] * i0] * phi_new->data[i0];
    }
  }

  emxFree_real_T(&a);
  emxFree_real_T(&phi_new);
  for (i = 0; i < (int)size; i++) {
    i0 = tmp_m->size[0];
    emxEnsureCapacity((emxArray__common *)tmp_m, i0, (int)sizeof(double));
    loop_ub = tmp_m->size[0];
    for (i0 = 0; i0 < loop_ub; i0++) {
      tmp_m->data[i0] += phi->data[i0 + phi->size[0] * ((int)(1.0F + (float)i) -
        1)] * t[(int)(1.0F + (float)i) - 1];
    }
  }

  emxFree_real_T(&phi);
  i0 = phi_new_t->size[0] * phi_new_t->size[1];
  phi_new_t->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)phi_new_t, i0, (int)sizeof(double));
  b_I = phi_new_t->size[0];
  c_I = phi_new_t->size[1];
  loop_ub = b_I * c_I;
  for (i0 = 0; i0 < loop_ub; i0++) {
    phi_new_t->data[i0] *= 11.1;
  }

  mrdivide(phi_new_t, I);
  emxFree_real_T(&I);
  if ((phi_new_t->size[1] == 1) || (tmp_m->size[0] == 1)) {
    d0 = 0.0;
    for (i0 = 0; i0 < phi_new_t->size[1]; i0++) {
      d0 += phi_new_t->data[phi_new_t->size[0] * i0] * tmp_m->data[i0];
    }

    *m = d0;
  } else {
    d0 = 0.0;
    for (i0 = 0; i0 < phi_new_t->size[1]; i0++) {
      d0 += phi_new_t->data[phi_new_t->size[0] * i0] * tmp_m->data[i0];
    }

    *m = d0;
  }

  emxFree_real_T(&phi_new_t);
  emxFree_real_T(&tmp_m);
  *b_std = 0.0900900900900901 + b_y;
}

/*
 * File trailer for BayesCurFit.c
 *
 * [EOF]
 */
