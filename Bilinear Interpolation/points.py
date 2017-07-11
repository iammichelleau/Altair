import numpy as np
import math

x_array = np.linspace(-math.pi, math.pi, 100)
y_array = np.linspace(-1, 1, 5)

file = open('input0.txt','w')

for y in y_array:
	for x in x_array:
		f = math.sin(x + y)
		print >> file, str(f) + " " + str(x) + " " + str(y)