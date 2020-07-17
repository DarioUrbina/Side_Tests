"""
import numpy as np 
from matplotlib import pyplot as plt 

x = np.array([1,11]) 
y = 2 * x + 5 
plt.title("Matplotlib demo") 
plt.xlabel("x axis caption") 
plt.ylabel("y axis caption") 
plt.plot(x,y) 
plt.show()
print(x)
"""

import numpy as np
from matplotlib import pyplot as plt 

a = np.array([[1,2,3],[4,5,6]]) 

print ('First array:') 
print (a) 
print ('\n')  

print ('Append elements to array:') 
print (np.append(a, [7,8,9]) )
print ('\n')

print ('Append elements along axis 0:' )
print (np.append(a, [[7,8,9]],axis = 0) )
print ('\n'  )

print ('Append elements along axis 1:' )
print (np.append(a, [[5,5,5],[7,8,9]],axis = 1))

print ('\n'  )
print (a)

plt.figure(1)
plt.title("a")
plt.plot(a[1,:],a[0,:])
plt.grid(True)
#plt.show()

plt.figure(2)
plt.title("b")
plt.plot(a[0,:],a[1,:])
plt.grid(True)
plt.show()





