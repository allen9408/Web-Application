import csv
from sklearn import svm, preprocessing
from sklearn.neural_network import MLPClassifier
import time
import os,sys
import numpy as np
from sklearn.model_selection import GridSearchCV

sys.path.append('./bcf.py')
import bcf

vol = bcf.Bayes_volume(sys.argv[1])
print vol

date = time.strftime('%m-%d-%Y', time.localtime(time.time()))
# init
# print(x);

# Read csv file
filename = './real_data/' + sys.argv[1] + '-' + date + '.csv'
f_tmp = open(filename, 'r')
cont = f_tmp.readlines()
size = len(cont) - 1
f_tmp.close()

x = [[0 for i in range(2)] for i in range(size)]
y = [0 for i in range(size)]

i = 0
with open(filename) as f:
	f_csv = csv.DictReader(f)
	for row in f_csv:
		# print i
		# print(row['Close'])
		x[i][0] = i
		# x[i][1] = row['Close']
		x[i][1] = row['volume']
		y[i] = row['close']
		i += 1
# print(x)
# print(y)
x = np.array(x)
y = np.array(y)

scalerx = preprocessing.RobustScaler()
x_scaled = scalerx.fit_transform(x)
scalery = preprocessing.RobustScaler()
y_scaled = scalery.fit_transform(y)
# x_scaled.fit_transform(x)
# paras = {'kernel':('poly','rbf'), 'C':[1,10]}
svr = svm.SVR()
# clf = GridSearchCV(svr, paras)
svr.fit(x_scaled,y_scaled)

price_index = [[i+1+j, vol[j]] for j in range(15)]
print price_index
result = svr.predict(scalerx.transform(np.array(price_index)))
print scalery.inverse_transform(result)