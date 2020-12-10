from vjoy import vj, setJoy
import numpy as np
import time

print("vj opening", flush=True)
vj.open()

time.sleep(0.3)

# valueX, valueY between -1.0 and 1.0
# scale between 0 and 16000
scale = 16000.0
setJoy(0,0,0,0,0,0,scale)

# pattern
# X = Left LR
# Rz = Right LR
# setJoy(1,0,0,0,0,1,scale)
# time.sleep(3)
# setJoy(-1,0,0,0,0,-1,scale)
# time.sleep(3)
print("starting")
setJoy(0,-0.55,0,0,0,0,scale)
time.sleep(2)
setJoy(0,-1,0,0,0,0,scale)
time.sleep(0.5)
print("opening")
setJoy(-1,-1,0,0,0,1,scale)
time.sleep(4)
print ("closing")
setJoy(1,-1,0,0,0,-1,scale)
time.sleep(3)
print ("continuing")
setJoy(0,-1,0,0,0,0,scale)
time.sleep(1)
setJoy(0,0,0,0,0,0,scale)
print("vj closing", flush=True)
vj.close()