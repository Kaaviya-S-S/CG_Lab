import numpy as np
import matplotlib.pyplot as plt

# Julia function
def julia(z, c, max_iter):
    n = 0
    while abs(z) <= 2 and n < max_iter:
        z = z*z + c
        n += 1
    return n

# Image size
width, height = 800, 800
# Real and Imaginary ranges
re_min, re_max = -1.5, 1.5
im_min, im_max = -1.5, 1.5

# Create image
image = np.zeros((height, width))

# Choose a fixed c
c = complex(-0.8, 0.156)  # You can change this for different patterns!

max_iter = 300

for x in range(width):
    for y in range(height):
        # Map pixel to complex plane
        real = re_min + (x / width) * (re_max - re_min)
        imag = im_min + (y / height) * (im_max - im_min)
        z = complex(real, imag)

        # Compute how fast it escapes
        m = julia(z, c, max_iter)
        image[y, x] = m

# Show the image
plt.figure(figsize=(10, 10))
plt.imshow(image, cmap='inferno', extent=(re_min, re_max, im_min, im_max))
plt.colorbar()
plt.title(f'Julia Set for c = {c}')
plt.show()
