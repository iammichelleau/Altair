import numpy as np
import math

x_array = np.linspace(-10, 10, 100)
y_array = np.linspace(-1, 1, 10)

file = open('sin_times.txt','w')

for y in y_array:
	for x in x_array:
		f = math.sin(x * y)
		print >> file, str(f) + " " + str(x) + " " + str(y)