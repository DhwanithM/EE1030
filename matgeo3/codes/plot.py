import numpy as np
import matplotlib.pyplot as plt

# Load the points from the text file
points = np.loadtxt("points.dat", delimiter=',')

# Extract the x and y coordinates for the points on the line
x1 = points[:21, 0]
y1 = points[:21, 1]

# Load the direction vector and normal vector from the last two lines
dirvector = [points[41, 0], points[41, 1]]
normvector = [points[62, 0], points[62, 1]]

# Normalize the direction and normal vectors to unit vectors
dirvector_magnitude = np.linalg.norm(dirvector)
normvector_magnitude = np.linalg.norm(normvector)

# Normalize both vectors to unit vectors
dirvector_unit = dirvector / dirvector_magnitude
normvector_unit = normvector / normvector_magnitude

# Define a scaling factor for the vectors (to make them visible)
scale_factor = 1.0

# Scale both vectors to the same length (common length)
dirvector_scaled = dirvector_unit * scale_factor
normvector_scaled = normvector_unit * scale_factor

# Set the origin to the point (2, 0)
origin = np.array([0, 0])

# Create a wider figure
plt.figure(figsize=(8, 9))  # Wider aspect ratio, 14 units wide and 6 units high

# Plot the line points (blue line)
plt.plot(x1, y1, label='Line x=3y', color='blue')

# Plot the scaled direction vector (green) from the new origin
plt.quiver(origin[0], origin[1], dirvector_scaled[0], dirvector_scaled[1], angles='xy', scale_units='xy', scale=0.5, color='green', label='Direction vector')

# Plot the scaled normal vector (red) from the new origin
plt.quiver(origin[0], origin[1], normvector_scaled[0], normvector_scaled[1], angles='xy', scale_units='xy', scale=0.5, color='red', label='Normal vector')

# Set equal aspect ratio to ensure correct proportions
plt.gca().set_aspect('equal', adjustable='box')

# Define limits for x and y axis to keep vectors in frame
vector_max = max(np.abs(dirvector_scaled).max(), np.abs(normvector_scaled).max())
#plt.xlim(-6, 6)
plt.ylim(-vector_max * 3, vector_max * 3)

# Add labels, title, and grid
plt.xlabel("x")
plt.ylabel("y")
plt.title("Line and Vectors: Direction and Normal")
plt.grid(True)

# Move legend to the top-left corner
plt.legend(loc='upper left')

# Save and show the plot
plt.savefig('../figs/fig.png')
plt.show()
