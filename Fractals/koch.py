import turtle
from turtle import *

speed(0)
penup()
goto(-250, 0)
pendown()

def koch(size, depth):
    if depth==0:
        forward(size)
    else:
        koch(size/3.0, depth-1)
        left(60)
        koch(size/3.0, depth-1)
        right(120)
        koch(size/3.0, depth-1)
        left(60)
        koch(size/3.0, depth-1)
    
koch(500,4)    
turtle.done()


# import turtle
# from turtle import *

# speed(0)
# penup()
# goto(-250, -50)
# left(60)
# pendown()

# def koch(size, depth):
#     if depth==0:
#         forward(size)
#     else:
#         koch(size/3.0, depth-1)
#         left(60)
#         koch(size/3.0, depth-1)
#         right(120)
#         koch(size/3.0, depth-1)
#         left(60)
#         koch(size/3.0, depth-1)
    
# koch(150,3) 
# right(120)
# koch(150,3)
# right(120)
# koch(150,3)   
# turtle.done()