import numpy as np
import math

x_array = np.linspace(-1, 1, 100)
y_array = np.linspace(-10, 10, 5)

file = open('input_sample.txt','w')

for y in y_array:
	for x in x_array:
		f = x * y
		print >> file, str(f) + " " + str(x) + " " + str(y)