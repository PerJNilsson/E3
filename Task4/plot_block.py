# plot the energies
# Created by Martin Gren 2014-10-25.

# imports
import matplotlib.pylab as plt
import numpy as np

# input file
filename = 'block_value.dat'

# import data
data = np.loadtxt(filename)

# initial size of plot window
plt.figure(figsize=(8,6))


sum = 0
for i in range(1000, len(data[:,1])):
    sum = sum + data[i,1] / (len(data[:,1])-1000)
g = float("{0:.2f}".format(sum))
sum2 = []
for i in range(0, len(data[:,0])):
    sum2.append(sum)

# plot
plt.plot(data[:,0], data[:,1],'X', label='s block value')
plt.plot(data[:,0], sum2,'-r', label=r'$s=\lim_{B\rightarrow large}\frac{B*Var(F)}{Var(f)}$='+str(g))

# labels
plt.xlabel('Blocks', fontsize=20)
plt.ylabel('s', fontsize=20)

# legend
plt.legend(loc='lower right')
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
