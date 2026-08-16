from turtle import *
import turtle
  
speed(1.1)
left(90)
  
angle = 30
  
def ytree(size, lvl):   
    if lvl > 0:
        #colormode(255)
        #pencolor(0, 255//lvl, 0)          
        forward(size)  
        right(angle) 
        
        ytree(0.8 * size, lvl-1)      
        
        #pencolor(0, 255//lvl, 0)        
        print("going to turn left..")
        left( 2 * angle )  
        print("turned left",lvl)
        
        ytree(0.8 * size, lvl-1)     
        
        #pencolor(0, 255//lvl, 0)          
        right(angle)
        forward(-size)
           
ytree(80, 3)
turtle.done()