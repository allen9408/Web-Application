/*
 * File: BP.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 22-Mar-2017 18:13:22
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BP.h"
#include "rand.h"

/* Function Definitions */

/*
 * Initialize v's and w's
 * Arguments    : const double x[8]
 *                const double t[4]
 *                double rate
 *                float max_times
 *                double target
 *                double w_init[2]
 *                double *err_1
 *                double w_final[2]
 *                double *err_final
 *                double *times
 * Return Type  : void
 */
void BP(const double x[8], const double t[4], double rate, float max_times,
        double target, double w_init[2], double *err_1, double w_final[2],
        double *err_final, double *times)
{
  int i0;
  double b_w_final;
  double v[4];
  double err;
  int k;
  boolean_T exitg1;
  double b_x;
  double y;
  double b_y;
  double c_y;
  double a;
  double w_delta[2];
  double v_delta[4];
  b_rand(w_final);
  for (i0 = 0; i0 < 2; i0++) {
    b_w_final = 2.0 * w_final[i0] - 1.0;
    w_init[i0] = b_w_final;
    w_final[i0] = b_w_final;
  }

  c_rand(v);
  for (i0 = 0; i0 < 4; i0++) {
    v[i0] = 2.0 * v[i0] - 1.0;
  }

  *times = 0.0;
  *err_1 = 0.0;
  err = 0.0;

  /*  start traning */
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= (int)max_times - 1)) {
    /* for l = 1:1:4 */
    /*  randomly choose one input vector */
    b_x = 4.0 * d_rand();
    if (b_x < 0.0) {
      b_x = ceil(b_x);
    } else {
      b_x = floor(b_x);
    }

    /*  output = t(1,l); */
    /*  calculate hidden layer */
    y = 1.0 / (1.0 + exp(-(v[0] * x[(int)(b_x + 1.0) - 1] + v[1] * x[(int)(b_x +
      1.0) + 3])));
    b_y = 1.0 / (1.0 + exp(-(v[2] * x[(int)(b_x + 1.0) - 1] + v[3] * x[(int)(b_x
      + 1.0) + 3])));

    /*  calculate output layer */
    c_y = 1.0 / (1.0 + exp(-(w_final[0] * y + w_final[1] * b_y)));
    a = t[(int)(b_x + 1.0) - 1] - c_y;
    err = 0.5 * (a * a);

    /* end */
    /*  output first-batch error */
    if (1.0F + (float)k == 1.0F) {
      *err_1 = err;
    }

    /*  count times */
    (*times)++;
    if (err < target) {
      exitg1 = true;
    } else {
      /*  calculate delta_w */
      w_delta[0] = rate * y * (t[(int)(b_x + 1.0) - 1] - c_y) * (-(1.0 / (1.0 +
        exp(-c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y))));
      w_delta[1] = rate * b_y * (t[(int)(b_x + 1.0) - 1] - c_y) * (-(1.0 / (1.0
        + exp(-c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y))));

      /*  calculate delta_v */
      v_delta[0] = rate * (t[(int)(b_x + 1.0) - 1] - c_y) * (-(1.0 / (1.0 + exp(
        -c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * w_final[0] * (-(1.0 / (1.0
        + exp(-c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * x[(int)(b_x + 1.0) -
        1];
      v_delta[2] = rate * (t[(int)(b_x + 1.0) - 1] - c_y) * (-(1.0 / (1.0 + exp(
        -c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * w_final[0] * (-(1.0 / (1.0
        + exp(-c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * x[(int)(b_x + 1.0) +
        3];
      v_delta[1] = rate * (t[(int)(b_x + 1.0) - 1] - c_y) * (-(1.0 / (1.0 + exp(
        -c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * w_final[1] * (-(1.0 / (1.0
        + exp(-c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * x[(int)(b_x + 1.0) -
        1];
      v_delta[3] = rate * (t[(int)(b_x + 1.0) - 1] - c_y) * (-(1.0 / (1.0 + exp(
        -c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * w_final[1] * (-(1.0 / (1.0
        + exp(-c_y))) * (1.0 - 1.0 / (1.0 + exp(-c_y)))) * x[(int)(b_x + 1.0) +
        3];

      /*  update v and w */
      for (i0 = 0; i0 < 2; i0++) {
        w_final[i0] += w_delta[i0];
      }

      for (i0 = 0; i0 < 4; i0++) {
        v[i0] += v_delta[i0];
      }

      k++;
    }
  }

  *err_final = err;
}

/*
 * File trailer for BP.c
 *
 * [EOF]
 */
