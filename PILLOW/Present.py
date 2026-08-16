from PIL import Image,ImageColor,ImageEnhance,ImageFilter

# with Image.open('samplepicture.jpg') as image:
#     image.show()

#import the image
image=Image.open('samplepicture.jpg')

# #Display the image
# image.show()

# #create a new image from scratch
# img=Image.new('RGBA',(1000,600))
# img.show()

# #saving the picture
# image.save('saved_picture.jpg')


# #Information on image
# print(image.size)
# print(image.filename)
# print(image.format)
# print(image.format_description)


###Rotate
# #Rotation without lossing pixels
# image.rotate(45,expand=True).show()


# #Fill color for the extra background
# image.rotate(45,expand=True,fillcolor=(255,0,0)).show()
# 
# print(ImageColor.colormap)#Available list of colors
# image.rotate(45,expand=True,fillcolor=ImageColor.getcolor('red','RGB')).show()


# #Crop
# #image.crop((left_x,top_y,right_x,bottom_y))
# cropped_image=image.crop((0,0,600,500))
# cropped_image.show()


# # Flip / Transpose
# image.show()
#image.transpose(Image.Transpose.FLIP_LEFT_RIGHT).show()
#image.transpose(Image.Transpose.FLIP_TOP_BOTTOM).show()
#image.transpose(Image.Transpose.ROTATE_90).show()

#Flips both sides
#image.transpose(Image.Transpose.TRANSPOSE).show() #Rotate and flip
#image.transpose(Image.Transpose.TRANSVERSE).show()


# #Resize
# image.resize((600,1000)).show()

# #Better to use a scaling factor to preseve the image
# image.resize((image.size[0]*2,image.size[1]*2)).show()


# # Filters and Enhancements
# ImageEnhance.Color(image).enhance(5).show()
# #1 is default

# ImageEnhance.Contrast(image).enhance(2).show()

# ImageEnhance.Brightness(image).enhance(5).show()

# ImageEnhance.Sharpness(image).enhance(5).show()

# image.filter(ImageFilter.BLUR).show()
# image.filter(ImageFilter.CONTOUR).show()
# image.filter(ImageFilter.DETAIL).show()
# image.filter(ImageFilter.EDGE_ENHANCE).show()
# image.filter(ImageFilter.EDGE_ENHANCE_MORE).show()
# image.filter(ImageFilter.FIND_EDGES).show()
# image.filter(ImageFilter.EMBOSS).show()
# image.filter(ImageFilter.SHARPEN).show()
# image.filter(ImageFilter.SMOOTH).show()
# image.filter(ImageFilter.SMOOTH_MORE).show()

# #Min Filter
# image.filter(ImageFilter.MinFilter(size=5)).show()

# #Max Filter
# image.filter(ImageFilter.MaxFilter(size=5)).show()

# #Median Filter
# image.filter(ImageFilter.MedianFilter(size=5)).show()

# image.filter(ImageFilter.BoxBlur(radius=4)).show()
# image.filter(ImageFilter.GaussianBlur(radius=4)).show()
# image.filter(ImageFilter.UnsharpMask(radius=4)).show()

# #Filter combinations
# img1=image.filter(ImageFilter.BLUR)
# img2=img1.filter(ImageFilter.MaxFilter(size=5))
# img2.show()


##Colors in pillow
#Get color value at (x,y)
print(image.getpixel((0,0)))

#Get all colors used in the image
print(image.getcolors(maxcolors=image.size[0]*image.size[1]))
