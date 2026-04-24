import matplotlib.pyplot as plt
raw_data = """
START ROW 0 ---> SWEEP LEFT TO RIGHT (0 to 30cm)!
0.00,0.00,37.83
0.31,0.00,37.37
0.63,0.00,35.53
0.94,0.00,35.53
1.25,0.00,35.02

<The whole Serial monitor is pasted here>

1.51,6.00,69.65
1.19,6.00,70.01
0.88,6.00,70.45
0.56,6.00,70.01
0.24,6.00,69.73
--- ALL 4 ROWS COMPLETE! ---
Copy your data to generate the 3D Map.

"""

x_vals = []
y_vals = []
z_vals = []

# 2. Smart Parser: Extract only valid X,Y,Z data lines
for line in raw_data.strip().split('\n'):
    parts = line.split(',')
    
    # Only look at lines that have exactly 3 items separated by commas
    if len(parts) == 3:
        try:
            x = float(parts[0])
            y = float(parts[1])
            z = float(parts[2])
            
            # Filter out the -1.0 errors (when the sensor times out/points at nothing)
            if z > 0: 
                x_vals.append(x)
                y_vals.append(y)
                z_vals.append(z)
        except ValueError:
            # If it has commas but isn't a number, skip it silently
            pass 

# 3. Create the 3D Map
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# plot_trisurf connects irregular points into a solid surface
# cmap='terrain' gives it that classic topography coloring (blue=deep, green/brown=high)
surf = ax.plot_trisurf(x_vals, y_vals, z_vals, cmap='terrain', edgecolor='none', alpha=0.9)

# 4. Formatting
ax.set_title("3D Topographical Terrain Map")
ax.set_xlabel("X-Axis: Horizontal Sweep (cm)")
ax.set_ylabel("Y-Axis: Forward Step (cm)")
ax.set_zlabel("Z-Axis: Depth/Distance (cm)")

# Add a color bar legend to the side
fig.colorbar(surf, ax=ax, shrink=0.5, aspect=5, label='Depth (cm)')

# Invert Z axis if you want it to look like a "floor" instead of a "ceiling" 
# (Uncomment the line below if the map looks upside down to you)
# ax.invert_zaxis()

# Show the interactive map!
plt.show()
