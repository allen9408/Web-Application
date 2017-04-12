#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

double f(double x) {
	return 1.0/(1.0 + exp(-x));
}

double f_prime(double x) {
	return f(x) * (1 - f(x));
}

int main(int argc, char const *argv[])
{
	// Initial x and t
	double x[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
	double t[4] = {0, 1, 1, 0};
	// Intialize v's and w's
	double w[2], w_delta[2];
	double v[2][2], v_delta[2][2];
	double b[2], b_delta[2];
	double c, c_delta;
	// int epoch = 0;
	double err = 0;
	int i = 0;

	int maxTime = atoi(argv[1]);
	double tarErr = atof(argv[2]);
	double rate = atof(argv[3]);

	srand((unsigned)time(NULL));  
	for (i = 0; i < 2; i++) {
		w[i] = rand()/double(RAND_MAX) * 2 - 1;
		v[i][0] = rand()/double(RAND_MAX) * 2 - 1;
		v[i][1] = rand()/double(RAND_MAX) * 2 - 1;
		b[i] = rand()/double(RAND_MAX) * 2 - 1;
	}
	c = rand()/double(RAND_MAX) * 2 - 1;

	// Output Initial weight;
	cout << "Initial:" << endl;
	cout << "W's: " << w[0] << ", " << w[1] << endl;
	cout << "V's: " << v[0][0] << ", " << v[0][1] << endl;
	cout << "     " << v[1][0] << ", " << v[1][1] << endl;
	cout << "Learning Rate: " << rate << endl;
	cout << "Target error: " << tarErr << endl;
	for (i = 0; i < maxTime; i++) {
		err = 0;
		w_delta[0] = 0;
		w_delta[1] = 0;
		v_delta[0][0] = 0;
		v_delta[0][1] = 0;
		v_delta[1][0] = 0;
		v_delta[1][1] = 0;
		b_delta[0] = 0;
		b_delta[1] = 0;
		c_delta = 0;
		double hnode[4][2];
		double y[4];
		for (int j = 0; j < 4; j++) {
			// Calculate hidden layer
			hnode[j][0] = f(v[0][0] * x[j][0] + v[0][1] * x[j][1] - b[0]);
			hnode[j][1] = f(v[1][0] * x[j][0] + v[1][1] * x[j][1] - b[1]);
			// Calculate output layer
			y[j] = f(w[0] * hnode[j][0] + w[1] * hnode[j][1] - c);
			err += 0.5 * (t[j] - y[j]) * (t[j] - y[j]);
		}

		if (i == 0)
			cout << "First Batch Error: " << err << endl;
		if (err < tarErr) 
			break;

		for (int j=0; j<4; j++){
			double ddd = (t[j] - y[j]) * f_prime(w[0] * hnode[j][0] + w[1] * hnode[j][1] - c);
			// Calculate w_delta
			w_delta[0] += ddd * hnode[j][0];
			w_delta[1] += ddd * hnode[j][1];
			c_delta += (-1) * ddd;				
			// Calculate v_delta
			v_delta[0][0] += ddd * w[0] * f_prime(v[0][0] * x[j][0] + v[0][1] * x[j][1] - b[0]) * x[j][0];
			v_delta[0][1] += ddd * w[0] * f_prime(v[0][0] * x[j][0] + v[0][1] * x[j][1] - b[0]) * x[j][1];
			v_delta[1][0] += ddd * w[1] * f_prime(v[1][0] * x[j][0] + v[1][1] * x[j][1] - b[1]) * x[j][0];
			v_delta[1][1] += ddd * w[1] * f_prime(v[1][0] * x[j][0] + v[1][1] * x[j][1] - b[1]) * x[j][1];
			b_delta[0] += ddd * w[0] * f_prime(v[0][0] * x[j][0] + v[0][1] * x[j][1] - b[0]) * (-1);
			b_delta[1] += ddd * w[1] * f_prime(v[1][0] * x[j][0] + v[1][1] * x[j][1] - b[1]) * (-1);			

		}
		// Update w's
		for (int k = 0; k < 2; k++) {
			w[k] += rate * w_delta[k];
		}
		c += c_delta;
		// Claculate v_delta
		// for (int j=0; j<4; j++) {
		// 	double ddd = (t[j] - y[j]) * f_prime(w[0] * hnode[j][0] + w[1] * hnode[j][1] - c);

		// }
		for (int k = 0; k < 2; k++) {
			v[k][0] += rate * v_delta[k][0];
			v[k][1] += rate * v_delta[k][1];
			b[k] += rate * b_delta[k];
		}


	}
	cout << "Final Error: " << err << endl;
	cout << "Training Epochs: " << i << endl;
	// cout << f(2) << endl;
	return 0;
}