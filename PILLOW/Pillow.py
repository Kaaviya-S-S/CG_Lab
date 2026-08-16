from PIL import Image
import numpy as np

# with Image.open('samplepicture.jpg') as image:
#     image.show()

#import the image
image=Image.open('samplepicture.jpg')

img2=Image.open('sample2.jpg')
# img2=img2.resize(image.size)
# img2.save('sample2.jpg')
# img2.show()

# #Display the image
# image.show()

# #Display the rotated image
# image.rotate(45).show()

# print(image.mode)
# print(img2.size)
# print(img2.mode)

image=image.convert('RGBA')
img2=img2.convert('RGBA')

# Image.alpha_composite(image,img2).show()

#out = image1 * (1.0 - alpha) + image2 * alpha
# Image.blend(image,img2,0.5).show()





# Image.new('RGBA',(100,200),color=(255,0,0)).show()

# im = Image.fromarray(a, mode="L")

img=np.zeros([16,16])
for i in range(0,8):
  for j in range(0,i+1):
    img[i,j]=j
  for j in range(i+1,8):
    img[i,j]=i
  for j in range(8,15-i):
    img[i,j]=i
  for j in range(i,-1,-1):
    img[i,15-j]=j

k=1
for i in range(8-1,-1,-1):
  for j in range(0,i+1):
    img[k+i,j]=j
  for j in range(i+1,8):
    img[k+i,j]=i
  for j in range(8,15-i):
    img[k+i,j]=i
  for j in range(i,-1,-1):
    img[k+i,15-j]=j
  k=k+2

img=img*(255/8.0)
# Image.fromarray(img).show()


radius=100
thickness=20
img=np.zeros([256,256])
for i in range(256):
  for j in range(256):
    if (i-128)**2+(j-128)**2<=(radius+thickness/2)**2 and (i-128)**2+(j-128)**2>=(radius-thickness/2)**2:
      img[i,j]=255

# Image.fromarray(img).show()

# Image.effect_noise(image.size,0.5).show()

# # Increase brightness
# bright_img = Image.eval(image, lambda x: min(x+50,255))
# bright_img.show()

image.point(lambda x: min(x+50,255)).show()




# image.copy().show()
# np.asarray(image)