/*
 * File: BP.c
 *
 * MATLAB Coder version            : 3.0
 * C/C++ source code generated on  : 24-Mar-2017 02:25:18
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "BP.h"
#include "rand.h"
#include <time.h>
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
  double b[2];
  double c;
  double err;
  int k;
  boolean_T exitg1;
  double w_delta[2];
  double v_delta[4];
  double b_delta[2];
  double c_delta;
  int l;
  double y;
  double b_y;
  double c_y;
  double a;
  double ddd;
  srand(time(NULL));
  b_rand(w_final);
  for (i0 = 0; i0 < 2; i0++) {
    b_w_final = 2.0 * rand()/(RAND_MAX) - 1.0;
    w_init[i0] = b_w_final;
    w_final[i0] = b_w_final;
  }

  c_rand(v);
  for (i0 = 0; i0 < 4; i0++) {
    v[i0] = 2.0 * rand()/(RAND_MAX) - 1.0;
  }

  b_rand(b);
  for (i0 = 0; i0 < 2; i0++) {
    b[i0] = 2.0 * rand()/(RAND_MAX) - 1.0;
  }

  c = 2.0 * rand()/(RAND_MAX) - 1.0;
  *times = 0.0;
  *err_1 = 0.0;
  err = 0.0;

  /*  start traning */
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k <= (int)max_times - 1)) {
    err = 0.0;
    for (i0 = 0; i0 < 2; i0++) {
      w_delta[i0] = 0.0;
    }

    for (i0 = 0; i0 < 4; i0++) {
      v_delta[i0] = 0.0;
    }

    for (i0 = 0; i0 < 2; i0++) {
      b_delta[i0] = 0.0;
    }

    c_delta = 0.0;
    for (l = 0; l < 4; l++) {
      /*  calculate hidden layer */
      y = 1.0 / (1.0 + exp(-((v[0] * x[l] + v[1] * x[4 + l]) + -b[0])));
      b_y = 1.0 / (1.0 + exp(-((v[2] * x[l] + v[3] * x[4 + l]) + -b[1])));

      /*  calculate output layer */
      c_y = 1.0 / (1.0 + exp(-((w_final[0] * (1.0 / (1.0 + exp(-((v[0] * x[l] +
        v[1] * x[4 + l]) + -b[0])))) + w_final[1] * (1.0 / (1.0 + exp(-((v[2] *
        x[l] + v[3] * x[4 + l]) + -b[1]))))) + -c)));
      a = t[l] - c_y;
      err += 0.5 * (a * a);
      ddd = (t[l] - c_y) * (1.0 / (1.0 + exp(-c_y)) * (1.0 - 1.0 / (1.0 + exp
        (-c_y))));

      /*  calculate delta_w */
      w_delta[0] += rate * y * ddd;
      w_delta[1] += rate * b_y * ddd;
      c_delta += -rate * ddd;

      /*  calculate delta_v */
      v_delta[0] += rate * ddd * w_final[0] * (1.0 / (1.0 + exp(-y)) * (1.0 -
        1.0 / (1.0 + exp(-y)))) * x[l];
      v_delta[2] += rate * ddd * w_final[1] * (1.0 / (1.0 + exp(-b_y)) * (1.0 -
        1.0 / (1.0 + exp(-b_y)))) * x[l];
      v_delta[1] += rate * ddd * w_final[0] * (1.0 / (1.0 + exp(-y)) * (1.0 -
        1.0 / (1.0 + exp(-y)))) * x[4 + l];
      v_delta[3] += rate * ddd * w_final[1] * (1.0 / (1.0 + exp(-b_y)) * (1.0 -
        1.0 / (1.0 + exp(-b_y)))) * x[4 + l];
      b_delta[0] += -(rate * ddd * w_final[0] * (1.0 / (1.0 + exp(-y)) * (1.0 -
        1.0 / (1.0 + exp(-y)))));
      b_delta[1] += -(rate * ddd * w_final[1] * (1.0 / (1.0 + exp(-b_y)) * (1.0
        - 1.0 / (1.0 + exp(-b_y)))));
    }

    /*  output first-batch error */
    if (1.0F + (float)k == 1.0F) {
      *err_1 = err;
    }

    /*  count times */
    (*times)++;
    if (err < target) {
      exitg1 = true;
    } else {
      /*  update v and w */
      for (i0 = 0; i0 < 2; i0++) {
        w_final[i0] += w_delta[i0];
      }

      for (i0 = 0; i0 < 4; i0++) {
        v[i0] += v_delta[i0];
      }

      for (i0 = 0; i0 < 2; i0++) {
        b[i0] += b_delta[i0];
      }

      c += c_delta;
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
