import numpy as np
import matplotlib.pyplot as plt

# Mandelbrot function
def mandelbrot(c, max_iter):
    z = 0
    n = 0
    while abs(z) <= 2 and n < max_iter:
        z = z*z + c
        n += 1
    return n

# Image size
width, height = 800, 800
# Plot window (real and imaginary range)
re_min, re_max = -2.0, 1.0
im_min, im_max = -1.5, 1.5

# Create an image
image = np.zeros((height, width))

max_iter = 100

for x in range(width):
    for y in range(height):
        # Convert pixel coordinate to complex number
        real = re_min + (x / width) * (re_max - re_min)
        imag = im_min + (y / height) * (im_max - im_min)
        c = complex(real, imag)

        color = mandelbrot(c, max_iter)
        image[y, x] = color

# Show the image
plt.imshow(image, cmap='hot', extent=(re_min, re_max, im_min, im_max))
plt.colorbar()
plt.title('Mandelbrot Set')
plt.show()
