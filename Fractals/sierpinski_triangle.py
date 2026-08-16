from turtle import *
import turtle

# simple triangle
# speed(1)
# left(60)
# forward(100)
# right(120)
# forward(100)
# right(120)
# forward(100)
# turtle.done()

# spiral triangle
# speed(1)
# left(60)
# size = 10
# forward(size)
# for i in range(1,10):
#     right(120)
#     forward(size + i*10)
# turtle.done()

# sierpenski triangle
speed(1)
def drawTriangle(points):
    penup()
    goto(points[0][0],points[0][1])
    pendown()
    goto(points[1][0], points[1][1])
    goto(points[2][0], points[2][1])
    goto(points[0][0], points[0][1])
    
def midpoint(p1, p2):
    return ((p1[0]+p2[0])/2, (p1[1]+p2[1])/2)

def Sierpinski(points,depth):
    drawTriangle(points)
    if depth > 0:
        Sierpinski([points[0],
                    midpoint(points[0], points[1]),
                    midpoint(points[0], points[2])],
                   depth-1)
        Sierpinski([points[1],
                    midpoint(points[0], points[1]),
                    midpoint(points[1], points[2])],
                   depth-1)
        Sierpinski([points[2],
                    midpoint(points[2], points[1]),
                    midpoint(points[0], points[2])],
                   depth-1)


points = [[-100,-50],[0,100],[100,-50]]
depth = 4
Sierpinski(points,depth)
turtle.done()