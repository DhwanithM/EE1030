# Code by GVV Sharma
# September 12, 2023
# Revised July 21, 2024
# Released under GNU GPL
# Point Vectors

import sys                                          # for path to external scripts
sys.path.insert(0, '/home/dhwalith/matgeo/codes/CoordGeo')        # path to my scripts
import numpy as np
import numpy.linalg as LA
import matplotlib.pyplot as plt
import matplotlib.patches as patches

# Local imports
from line.funcs import *
from triangle.funcs import *
from conics.funcs import circ_gen

# Function to read vectors from a file
def read_vectors_from_file(filename):
    data = np.loadtxt(filename)
    if data.shape[1] != 2:
        raise ValueError("Each line in the file should contain exactly two values (x, y).")
    return data

# Read vectors from the file
vectors = read_vectors_from_file('output.txt')

if len(vectors) < 3:
    raise ValueError("The file should contain at least three lines of coordinates.")

# Given points from the file
B = np.array((vectors[0, :])).reshape(-1,1)  # First vector
C = np.array((vectors[1, :])).reshape(-1,1)  # Second vector
D = np.array((vectors[2, :])).reshape(-1,1)  # Third vector

# Create figure and axis
fig, ax = plt.subplots()

# Plotting lines from origin to each point with arrows
def add_arrow(x_start, y_start, x_end, y_end, color='k'):
    arrow = patches.FancyArrowPatch((x_start, y_start), (x_end, y_end), 
                                    mutation_scale=10,  # Adjust the size of the arrowhead
                                    arrowstyle='->',    # Arrowhead style
                                    color=color)
    ax.add_patch(arrow)

# Add arrows from origin to each point with different colors
add_arrow(0, 0, B[0, 0], B[1, 0], color='red')
add_arrow(0, 0, C[0, 0], C[1, 0], color='blue')
add_arrow(0, 0, D[0, 0], D[1, 0], color='green')

# Plot lines connecting the origin to each point with different colors
ax.plot([0, B[0, 0]], [0, B[1, 0]], label='$v_b$', color='red')
ax.plot([0, C[0, 0]], [0, C[1, 0]], label='$v_c$', color='blue')
ax.plot([0, D[0, 0]], [0, D[1, 0]], label='$v_r$', color='green')

# Scatter plot for points B, C, D
tri_coords = np.block([[B, C, D]])
ax.scatter(tri_coords[0,:], tri_coords[1,:], c=np.arange(1, 4))

# Labeling the coordinates without using a for loop
ax.annotate(f'\n({tri_coords[0,0]:.2f}, {tri_coords[1,0]:.2f})',
            (tri_coords[0,0], tri_coords[1,0]), textcoords="offset points", xytext=(25,5), ha='center', color='red')
ax.annotate(f'\n({tri_coords[0,1]:.2f}, {tri_coords[1,1]:.2f})',
            (tri_coords[0,1], tri_coords[1,1]), textcoords="offset points", xytext=(25,5), ha='center', color='blue')
ax.annotate(f'\n({tri_coords[0,2]:.2f}, {tri_coords[1,2]:.2f})',
            (tri_coords[0,2], tri_coords[1,2]), textcoords="offset points", xytext=(25,5), ha='center', color='green')

# Use set_position
ax.spines['top'].set_color('none')
ax.spines['left'].set_position('zero')
ax.spines['right'].set_color('none')
ax.spines['bottom'].set_position('zero')

plt.grid()  # minor
plt.axis('equal')

plt.legend()
plt.savefig('../plots/plot.png', format='png', bbox_inches='tight')

