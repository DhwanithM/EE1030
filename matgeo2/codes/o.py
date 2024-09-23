# Code by GVV Sharmai
# September 12, 2023
# Revised July 21, 2024
# Released under GNU GPL
# Point Vectors

import sys                                          # for path to external scripts
sys.path.insert(0, '/home/dhwalith/matgeo/codes/CoordGeo')        # path to my scripts
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.image as mpimg

# Local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen


# Function to read points from a file
def read_points_from_file(filename):
    data = np.loadtxt(filename)
    if data.shape[1] != 2:
        raise ValueError("Each line in the file should contain exactly two values (x, y).")
    return data

# Read points from the file
points = read_points_from_file('output.txt')

if len(points) != 2:
    raise ValueError("The file should contain exactly two lines of coordinates.")

# Given points from the file
P = np.array((points[0, :])).reshape(-1,1)  # First point
O = np.array((points[1, :])).reshape(-1,1)  # Second point

# Compute the midpoint C
I = np.eye((2))
e1 = I[:,0].reshape(-1, 1)
x = (LA.norm(P)*2 - LA.norm(O)*2) / (2 * (P - O).T @ e1)
C = x * e1

# Compute the distance between P and O
distance = LA.norm(P - O)

# Generating lines
x_PO = line_gen(P, O)

# Plotting the line between the points and the points themselves
plt.plot(x_PO[0,:], x_PO[1,:], label='$PO$')

# Scatter plot for points P and O
tri_coords = np.block([[P, O]])
plt.scatter(tri_coords[0,:], tri_coords[1,:])

# Labeling the coordinates and distance
plt.annotate(f'P\n({tri_coords[0,0]:.0f}, {tri_coords[1,0]:.0f})',
             (tri_coords[0,0], tri_coords[1,0]), textcoords="offset points",
             xytext=(20,5), ha='center')
plt.annotate(f'O\n({tri_coords[0,1]:.0f}, {tri_coords[1,1]:.0f})',
             (tri_coords[0,1], tri_coords[1,1]), textcoords="offset points",
             xytext=(20,5), ha='center')

# Plot the distance between points
midpoint = (P + O) / 2
plt.text(midpoint[0,0], midpoint[1,0], f'd={distance:.2f}', fontsize=12, ha='center')

# Use set_position
ax = plt.gca()
ax.spines['top'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('zero')

plt.legend(loc='best')
plt.grid()  # minor
plt.axis('equal')

plt.savefig('../plots/plot.png', format='png', bbox_inches='tight')
plt.plot()
