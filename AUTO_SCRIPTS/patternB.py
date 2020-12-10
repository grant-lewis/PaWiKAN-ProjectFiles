from vjoy import vj, setJoy
import numpy as np
import time

print("vj opening", flush=True)
vj.open()

time.sleep(0.3)

print("sending axes", flush=True)

# valueX, valueY between -1.0 and 1.0
# scale between 0 and 16000
scale = 16000.0
setJoy(0,0,0,0,0,0,scale)

# pattern
# X = Left LR
# Rz = Right LR
print("left")
setJoy(-1,-1,0,0,0,-1,scale)
time.sleep(2)
print("right")
setJoy(1,-1,0,0,0,-1,scale)
time.sleep(4)
print("left")
setJoy(-1,-1,0,0,0,-1,scale)
time.sleep(2)
print ("continue")
setJoy(0,-1,0,0,0,0,scale)
time.sleep(1)

setJoy(0,0,0,0,0,0,scale)
print("vj closing", flush=True)
vj.close()