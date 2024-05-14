import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Read the data from the output.txt file
data = []
dimensions = []
with open("output.txt", "r") as file:
    for line in file:
        line = line.strip()
        if line.startswith("Dimension:"):
            dimension = int(line.split(":")[1])
            dimensions.append(dimension)
            data.append([])
        else:
            data[-1].extend(map(float, line.split()))

# Convert data to numpy arrays
data = np.array(data)
dimensions = np.array(dimensions)

# Create a meshgrid of dimensions and distances
dim_range = np.arange(dimensions.min(), dimensions.max() + 1)
dist_range = np.arange(len(data[0]))
dim_mesh, dist_mesh = np.meshgrid(dim_range, dist_range)

# Plot the 3D surface
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')
surf = ax.plot_surface(dim_mesh, dist_mesh, data.T, rstride=1, cstride=1, cmap='viridis')
ax.set_xlabel('Dimension')
ax.set_ylabel('Distance')
ax.set_zlabel('Fraction')
ax.set_title('Fraction as a Function of Dimension and Distance')
fig.colorbar(surf, shrink=0.5, aspect=5)

# Save the plot as an image file
plt.savefig('surface_plot.png', dpi=300, bbox_inches='tight')