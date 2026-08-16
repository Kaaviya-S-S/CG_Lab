from turtle import *
import turtle

# # Setup turtle
# speed(0)   
# penup()
# goto(-100, 0)
# pendown()

# # Recursive function to draw the Levy C Curve
# def levy_curve(length, level):
#     if level == 0:
#         forward(length)
#     else:
#         right(45)
#         levy_curve(length / (2 ** 0.5), level - 1)
#         left(90)
#         levy_curve(length / (2 ** 0.5), level - 1)
#         right(45)

# # Draw the Levy C Curve
# levy_curve(200, 5)  # (initial length, recursion level)
# turtle.done()


# Setup turtle
speed(0)   
penup()
goto(-100, 0)
pendown()

# Recursive function to draw the dragon C Curve
def dragon_curve(length, level, sign=1):
    if level == 0:
        forward(length)
    else:
        right(sign*45)
        dragon_curve(length / (2 ** 0.5), level-1, 1)
        left(sign*90)
        dragon_curve(length / (2 ** 0.5), level-1, -1)
        right(sign*45)

# Draw the dragon Curve
dragon_curve(200, 5, 1)  # (initial length, recursion level, sign) [sign alternating]
turtle.done()
