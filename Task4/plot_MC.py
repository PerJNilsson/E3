# plot the energies
# Created by Martin Gren 2014-10-25.

# imports
import matplotlib.pylab as plt
import numpy as np

# input file
filename = 'MC.txt'

# import data
data = np.loadtxt(filename)

# initial size of plot window
plt.figure(figsize=(8,6))

data_x = []
data_y = []
# plot
for i in range(0, 10000):
    data_x.append(i*100)
    data_y.append(data[i*100])

plt.plot(data_x, data_y,'-', label='MC')


# labels
plt.xlabel('k', fontsize=20)
plt.ylabel('$\phi$(k)', fontsize=20)

# legend
plt.legend(loc='upper right')
leg = plt.gca().get_legend()
ltext  = leg.get_texts()
plt.setp(ltext, fontsize=12)

# axis limits
#plt.xlim([0,data[-1,0]])
#plt.ylim([min(data[:,3])-0.002,max(data[:,1])+0.002])

# tick fontsize
plt.xticks(fontsize=12)
plt.yticks(fontsize=12)

# display the plot

plt.show()
