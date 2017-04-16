import csv
# init
x = [[0 for i in range(2)] for i in range (251)]
y = [[0] for i in range (251)]
# print(x);

# Read csv file
size = 0
with open('test.csv') as f:
	f_csv = csv.DictReader(f)
	for row in f_csv:
		# print(row['Close'])
		x[size][0] = size
		# x[size][1] = row['Close']
		x[size][1] = row['Volume']
		y[size] = row['Adj Close']
		size += 1
print(x)
print(y)

