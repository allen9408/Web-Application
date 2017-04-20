import numpy as np
import time,csv
import os,sys

def BayesCurFit(x, t, size, M, x_predict):
	a = 0.005
	b = 11.1
	phi_t = [[0 for i in range(M+1)] for i in range(size)]
	for i in range(size):
		for j in range(M+1):
			phi_t[i][j] = x[i][0] ** j

	# print 'phi_t:'
	# print phi_t
	phi_t = np.mat(phi_t)
	phi = phi_t.T
	# print 'phi:'
	# print phi

	phi_sum = np.zeros((M+1,M+1))
	for i in range(size):
		tmp = np.dot(phi[:,i], phi_t[i,:])
		phi_sum += tmp

	# print 'phi_sum:'
	# print phi_sum

	I_mat = np.mat(np.eye(M+1))
	s_inv = a*I_mat + b*phi_sum
	# print 's_inv:'
	# print s_inv

	s = s_inv.I
	# print 's:'
	# print s

	phi_new_t = np.ones((1,M+1))  
	for i in range(M+1):
		phi_new_t[0][i] = x_predict ** i
	phi_new = phi_new_t.T
	# print 'phi_new_t:'
	# print phi_new_t

	s_2 = b**(-1) + np.dot(np.dot(phi_new_t, s), phi_new)
	# print s_2

	tmp_m = np.zeros((M+1, 1))
	for i in range(size):
		tmp = phi[:,i] * t[i][0]
		tmp_m += tmp
	# print 'tmp_m:'
	# print tmp_m

	phi_new_t = np.mat(phi_new_t)
	tmp_m = np.mat(tmp_m)
	m_m = np.dot(b*phi_new_t, s)
	# print m_m
	m = np.dot(m_m, tmp_m)
	print m

# x = [[1],[2],[3],[4],[5]]
# t = [[1],[4],[9],[16],[25]]
date = time.strftime('%m-%d-%Y', time.localtime(time.time()))
# init
# print(x);

# Read csv file
filename = './real_data/' + sys.argv[1] + '-' + date + '.csv'
f_tmp = open(filename, 'r')
cont = f_tmp.readlines()
size = len(cont) - 1
f_tmp.close()

x = [[0 for i in range(1)] for i in range(size)]
y = [[0 for i in range(1)] for i in range(size)]
# x = [[0] for i in range(size)]

i = 0
with open(filename) as f:
	f_csv = csv.DictReader(f)
	for row in f_csv:
		# print i
		# print(row['Close'])
		x[i][0] = i
		y[i][0] = float(row['close'])
		# x[i][1] = 0
		# y[i][0] = int(row['close'])
		i += 1
for j in range(15):
	BayesCurFit(x, y, i, 4, i+1000+j)