/*
 * File: mrdivide.c
 *
 * MATLAB Coder version            : 3.2
 * C/C++ source code generated on  : 23-Feb-2017 21:47:32
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BayesCurFit.h"
#include "mrdivide.h"
#include "BayesCurFit_emxutil.h"
#include "xzgetrf.h"
#include "xgeqp3.h"

/* Function Definitions */

/*
 * Arguments    : emxArray_real_T *A
 *                const emxArray_real_T *B
 * Return Type  : void
 */
void mrdivide(emxArray_real_T *A, const emxArray_real_T *B)
{
  emxArray_real_T *Y;
  emxArray_real_T *b_A;
  emxArray_real_T *tau;
  emxArray_int32_T *jpvt;
  emxArray_real_T *b_B;
  unsigned int unnamed_idx_1;
  int j;
  int rankR;
  int mn;
  int minmn;
  int maxmn;
  double tol;
  emxInit_real_T1(&Y, 1);
  emxInit_real_T(&b_A, 2);
  emxInit_real_T1(&tau, 1);
  emxInit_int32_T(&jpvt, 2);
  emxInit_real_T1(&b_B, 1);
  if ((A->size[1] == 0) || ((B->size[0] == 0) || (B->size[1] == 0))) {
    unnamed_idx_1 = (unsigned int)B->size[0];
    j = A->size[0] * A->size[1];
    A->size[0] = 1;
    A->size[1] = (int)unnamed_idx_1;
    emxEnsureCapacity((emxArray__common *)A, j, (int)sizeof(double));
    mn = (int)unnamed_idx_1;
    for (j = 0; j < mn; j++) {
      A->data[A->size[0] * j] = 0.0;
    }
  } else if (B->size[0] == B->size[1]) {
    rankR = B->size[1];
    j = b_A->size[0] * b_A->size[1];
    b_A->size[0] = B->size[0];
    b_A->size[1] = B->size[1];
    emxEnsureCapacity((emxArray__common *)b_A, j, (int)sizeof(double));
    mn = B->size[0] * B->size[1];
    for (j = 0; j < mn; j++) {
      b_A->data[j] = B->data[j];
    }

    xzgetrf(B->size[1], B->size[1], b_A, B->size[1], jpvt, &minmn);
    if (A->size[1] != 0) {
      for (j = 0; j + 1 <= rankR; j++) {
        minmn = rankR * j;
        for (maxmn = 0; maxmn + 1 <= j; maxmn++) {
          if (b_A->data[maxmn + minmn] != 0.0) {
            A->data[j] -= b_A->data[maxmn + minmn] * A->data[maxmn];
          }
        }

        tol = b_A->data[j + minmn];
        A->data[j] *= 1.0 / tol;
      }
    }

    if (A->size[1] != 0) {
      for (j = B->size[1]; j > 0; j--) {
        minmn = rankR * (j - 1);
        for (maxmn = j; maxmn + 1 <= rankR; maxmn++) {
          if (b_A->data[maxmn + minmn] != 0.0) {
            A->data[j - 1] -= b_A->data[maxmn + minmn] * A->data[maxmn];
          }
        }
      }
    }

    for (minmn = B->size[1] - 2; minmn + 1 > 0; minmn--) {
      if (jpvt->data[minmn] != minmn + 1) {
        tol = A->data[A->size[0] * minmn];
        A->data[A->size[0] * minmn] = A->data[A->size[0] * (jpvt->data[minmn] -
          1)];
        A->data[A->size[0] * (jpvt->data[minmn] - 1)] = tol;
      }
    }
  } else {
    j = b_A->size[0] * b_A->size[1];
    b_A->size[0] = B->size[1];
    b_A->size[1] = B->size[0];
    emxEnsureCapacity((emxArray__common *)b_A, j, (int)sizeof(double));
    mn = B->size[0];
    for (j = 0; j < mn; j++) {
      minmn = B->size[1];
      for (maxmn = 0; maxmn < minmn; maxmn++) {
        b_A->data[maxmn + b_A->size[0] * j] = B->data[j + B->size[0] * maxmn];
      }
    }

    xgeqp3(b_A, tau, jpvt);
    rankR = 0;
    if (b_A->size[0] < b_A->size[1]) {
      minmn = b_A->size[0];
      maxmn = b_A->size[1];
    } else {
      minmn = b_A->size[1];
      maxmn = b_A->size[0];
    }

    if (minmn > 0) {
      tol = (double)maxmn * fabs(b_A->data[0]) * 2.2204460492503131E-16;
      while ((rankR < minmn) && (fabs(b_A->data[rankR + b_A->size[0] * rankR]) >=
              tol)) {
        rankR++;
      }
    }

    minmn = b_A->size[1];
    j = Y->size[0];
    Y->size[0] = minmn;
    emxEnsureCapacity((emxArray__common *)Y, j, (int)sizeof(double));
    for (j = 0; j < minmn; j++) {
      Y->data[j] = 0.0;
    }

    j = b_B->size[0];
    b_B->size[0] = A->size[1];
    emxEnsureCapacity((emxArray__common *)b_B, j, (int)sizeof(double));
    mn = A->size[1];
    for (j = 0; j < mn; j++) {
      b_B->data[j] = A->data[A->size[0] * j];
    }

    maxmn = b_A->size[0];
    minmn = b_A->size[0];
    mn = b_A->size[1];
    if (minmn <= mn) {
      mn = minmn;
    }

    for (j = 0; j + 1 <= mn; j++) {
      if (tau->data[j] != 0.0) {
        tol = b_B->data[j];
        for (minmn = j + 1; minmn + 1 <= maxmn; minmn++) {
          tol += b_A->data[minmn + b_A->size[0] * j] * b_B->data[minmn];
        }

        tol *= tau->data[j];
        if (tol != 0.0) {
          b_B->data[j] -= tol;
          for (minmn = j + 1; minmn + 1 <= maxmn; minmn++) {
            b_B->data[minmn] -= b_A->data[minmn + b_A->size[0] * j] * tol;
          }
        }
      }
    }

    for (minmn = 0; minmn + 1 <= rankR; minmn++) {
      Y->data[jpvt->data[minmn] - 1] = b_B->data[minmn];
    }

    for (j = rankR - 1; j + 1 > 0; j--) {
      Y->data[jpvt->data[j] - 1] /= b_A->data[j + b_A->size[0] * j];
      for (minmn = 0; minmn + 1 <= j; minmn++) {
        Y->data[jpvt->data[minmn] - 1] -= Y->data[jpvt->data[j] - 1] * b_A->
          data[minmn + b_A->size[0] * j];
      }
    }

    j = A->size[0] * A->size[1];
    A->size[0] = 1;
    A->size[1] = Y->size[0];
    emxEnsureCapacity((emxArray__common *)A, j, (int)sizeof(double));
    mn = Y->size[0];
    for (j = 0; j < mn; j++) {
      A->data[A->size[0] * j] = Y->data[j];
    }
  }

  emxFree_real_T(&b_B);
  emxFree_int32_T(&jpvt);
  emxFree_real_T(&tau);
  emxFree_real_T(&b_A);
  emxFree_real_T(&Y);
}

/*
 * File trailer for mrdivide.c
 *
 * [EOF]
 */
