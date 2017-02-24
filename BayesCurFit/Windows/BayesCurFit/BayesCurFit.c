/*
 * File: BayesCurFit.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 23-Feb-2017 16:43:48
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
  int I;
  int loop_ub;
  emxArray_real_T *phi_sum;
  emxArray_real_T *b_I;
  emxArray_real_T *tmp_m;
  emxArray_real_T *phi_new_t;
  int i;
  emxArray_real_T *phi;
  float y_data[1024];
  double a_data[1024];
  int c_I;
  emxArray_real_T *b_phi;
  int i0;
  emxArray_real_T *b_phi_t;
  emxArray_real_T *phi_new;
  emxArray_int32_T *ipiv;
  emxArray_real_T *a;
  double y;
  emxInit_real_T(&phi_t, 2);
  I = phi_t->size[0] * phi_t->size[1];
  phi_t->size[0] = (int)size;
  phi_t->size[1] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)phi_t, I, (int)sizeof(double));
  loop_ub = (int)size * (int)(M + 1.0F);
  for (I = 0; I < loop_ub; I++) {
    phi_t->data[I] = 1.0;
  }

  emxInit_real_T(&phi_sum, 2);

  /*  p=zeros(1,N); */
  I = phi_sum->size[0] * phi_sum->size[1];
  phi_sum->size[0] = (int)(M + 1.0F);
  phi_sum->size[1] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)phi_sum, I, (int)sizeof(double));
  loop_ub = (int)(M + 1.0F) * (int)(M + 1.0F);
  for (I = 0; I < loop_ub; I++) {
    phi_sum->data[I] = 0.0;
  }

  emxInit_real_T(&b_I, 2);
  emxInit_real_T1(&tmp_m, 1);
  eye(M + 1.0F, b_I);

  /*  s_2 = zeros(size,size); */
  I = tmp_m->size[0];
  tmp_m->size[0] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)tmp_m, I, (int)sizeof(double));
  loop_ub = (int)(M + 1.0F);
  for (I = 0; I < loop_ub; I++) {
    tmp_m->data[I] = 0.0;
  }

  emxInit_real_T(&phi_new_t, 2);
  I = phi_new_t->size[0] * phi_new_t->size[1];
  phi_new_t->size[0] = 1;
  phi_new_t->size[1] = (int)(M + 1.0F);
  emxEnsureCapacity((emxArray__common *)phi_new_t, I, (int)sizeof(double));
  loop_ub = (int)(M + 1.0F);
  for (I = 0; I < loop_ub; I++) {
    phi_new_t->data[I] = 1.0;
  }

  for (i = 0; i < (int)M; i++) {
    if (1.0F > size) {
      loop_ub = 0;
    } else {
      loop_ub = (int)size;
    }

    for (I = 0; I < loop_ub; I++) {
      a_data[I] = x[I];
    }

    for (I = 0; I + 1 <= loop_ub; I++) {
      y_data[I] = rt_powf_snf((float)a_data[I], 1.0F + (float)i);
    }

    loop_ub = (short)loop_ub;
    for (I = 0; I < loop_ub; I++) {
      phi_t->data[I + phi_t->size[0] * ((int)((1.0F + (float)i) + 1.0F) - 1)] =
        y_data[I];
    }
  }

  emxInit_real_T(&phi, 2);
  I = phi->size[0] * phi->size[1];
  phi->size[0] = phi_t->size[1];
  phi->size[1] = phi_t->size[0];
  emxEnsureCapacity((emxArray__common *)phi, I, (int)sizeof(double));
  loop_ub = phi_t->size[0];
  for (I = 0; I < loop_ub; I++) {
    c_I = phi_t->size[1];
    for (i0 = 0; i0 < c_I; i0++) {
      phi->data[i0 + phi->size[0] * I] = phi_t->data[I + phi_t->size[0] * i0];
    }
  }

  i = 0;
  emxInit_real_T1(&b_phi, 1);
  emxInit_real_T(&b_phi_t, 2);
  while (i <= (int)size - 1) {
    if (1.0F > M + 1.0F) {
      loop_ub = 0;
      c_I = 0;
    } else {
      loop_ub = (int)(M + 1.0F);
      c_I = (int)(M + 1.0F);
    }

    I = b_phi->size[0];
    b_phi->size[0] = loop_ub;
    emxEnsureCapacity((emxArray__common *)b_phi, I, (int)sizeof(double));
    for (I = 0; I < loop_ub; I++) {
      b_phi->data[I] = phi->data[I + phi->size[0] * ((int)(1.0F + (float)i) - 1)];
    }

    I = b_phi_t->size[0] * b_phi_t->size[1];
    b_phi_t->size[0] = 1;
    b_phi_t->size[1] = c_I;
    emxEnsureCapacity((emxArray__common *)b_phi_t, I, (int)sizeof(double));
    for (I = 0; I < c_I; I++) {
      b_phi_t->data[b_phi_t->size[0] * I] = phi_t->data[((int)(1.0F + (float)i)
        + phi_t->size[0] * I) - 1];
    }

    I = phi_sum->size[0] * phi_sum->size[1];
    phi_sum->size[0] = b_phi->size[0];
    phi_sum->size[1] = b_phi_t->size[1];
    emxEnsureCapacity((emxArray__common *)phi_sum, I, (int)sizeof(double));
    loop_ub = b_phi->size[0];
    for (I = 0; I < loop_ub; I++) {
      c_I = b_phi_t->size[1];
      for (i0 = 0; i0 < c_I; i0++) {
        y = b_phi->data[I] * b_phi_t->data[b_phi_t->size[0] * i0];
        phi_sum->data[I + phi_sum->size[0] * i0] += y;
      }
    }

    i++;
  }

  emxFree_real_T(&b_phi_t);
  emxFree_real_T(&b_phi);
  emxFree_real_T(&phi_t);
  I = b_I->size[0] * b_I->size[1];
  emxEnsureCapacity((emxArray__common *)b_I, I, (int)sizeof(double));
  I = b_I->size[0];
  c_I = b_I->size[1];
  loop_ub = I * c_I;
  for (I = 0; I < loop_ub; I++) {
    b_I->data[I] = 0.005 * b_I->data[I] + 11.1 * phi_sum->data[I];
  }

  if (!((b_I->size[0] == 0) || (b_I->size[1] == 0))) {
    I = phi_sum->size[0] * phi_sum->size[1];
    phi_sum->size[0] = b_I->size[0];
    phi_sum->size[1] = b_I->size[1];
    emxEnsureCapacity((emxArray__common *)phi_sum, I, (int)sizeof(double));
    loop_ub = b_I->size[0] * b_I->size[1];
    for (I = 0; I < loop_ub; I++) {
      phi_sum->data[I] = b_I->data[I];
    }

    emxInit_int32_T(&ipiv, 2);
    xzgetrf(b_I->size[0], b_I->size[0], phi_sum, b_I->size[0], ipiv, &I);
    emxFree_int32_T(&ipiv);
  }

  emxFree_real_T(&phi_sum);

  /*  test new value */
  for (i = 0; i < (int)M; i++) {
    phi_new_t->data[phi_new_t->size[0] * ((int)((1.0F + (float)i) + 1.0F) - 1)] =
      rt_powf_snf((float)x_new, 1.0F + (float)i);
  }

  emxInit_real_T1(&phi_new, 1);
  I = phi_new->size[0];
  phi_new->size[0] = phi_new_t->size[1];
  emxEnsureCapacity((emxArray__common *)phi_new, I, (int)sizeof(double));
  loop_ub = phi_new_t->size[1];
  for (I = 0; I < loop_ub; I++) {
    phi_new->data[I] = phi_new_t->data[phi_new_t->size[0] * I];
  }

  emxInit_real_T(&a, 2);
  I = a->size[0] * a->size[1];
  a->size[0] = 1;
  a->size[1] = phi_new_t->size[1];
  emxEnsureCapacity((emxArray__common *)a, I, (int)sizeof(double));
  loop_ub = phi_new_t->size[0] * phi_new_t->size[1];
  for (I = 0; I < loop_ub; I++) {
    a->data[I] = phi_new_t->data[I];
  }

  mrdivide(a, b_I);
  if ((a->size[1] == 1) || (phi_new->size[0] == 1)) {
    y = 0.0;
    for (I = 0; I < a->size[1]; I++) {
      y += a->data[a->size[0] * I] * phi_new->data[I];
    }
  } else {
    y = 0.0;
    for (I = 0; I < a->size[1]; I++) {
      y += a->data[a->size[0] * I] * phi_new->data[I];
    }
  }

  emxFree_real_T(&a);
  emxFree_real_T(&phi_new);
  for (i = 0; i < (int)size; i++) {
    I = tmp_m->size[0];
    emxEnsureCapacity((emxArray__common *)tmp_m, I, (int)sizeof(double));
    loop_ub = tmp_m->size[0];
    for (I = 0; I < loop_ub; I++) {
      tmp_m->data[I] += phi->data[I + phi->size[0] * ((int)(1.0F + (float)i) - 1)]
        * t[(int)(1.0F + (float)i) - 1];
    }
  }

  emxFree_real_T(&phi);
  I = phi_new_t->size[0] * phi_new_t->size[1];
  phi_new_t->size[0] = 1;
  emxEnsureCapacity((emxArray__common *)phi_new_t, I, (int)sizeof(double));
  I = phi_new_t->size[0];
  c_I = phi_new_t->size[1];
  loop_ub = I * c_I;
  for (I = 0; I < loop_ub; I++) {
    phi_new_t->data[I] *= 11.1;
  }

  mrdivide(phi_new_t, b_I);
  emxFree_real_T(&b_I);
  if ((phi_new_t->size[1] == 1) || (tmp_m->size[0] == 1)) {
    *m = 0.0;
    for (I = 0; I < phi_new_t->size[1]; I++) {
      *m += phi_new_t->data[phi_new_t->size[0] * I] * tmp_m->data[I];
    }
  } else {
    *m = 0.0;
    for (I = 0; I < phi_new_t->size[1]; I++) {
      *m += phi_new_t->data[phi_new_t->size[0] * I] * tmp_m->data[I];
    }
  }

  emxFree_real_T(&phi_new_t);
  emxFree_real_T(&tmp_m);
  *b_std = 0.0900900900900901 + y;
}

/*
 * File trailer for BayesCurFit.c
 *
 * [EOF]
 */
