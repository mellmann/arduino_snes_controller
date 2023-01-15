import keyboard
import serial
import time
import struct

ser = serial.Serial(port = 'COM6', baudrate=115200, timeout=1)
time.sleep(2)

buttons = [
    "B",
    "Y",
    "SELECT",
    "START",
    "UP",
    "DOWN",
    "LEFT",
    "RIGHT",
    "A",
    "X",
    "L",
    "R"
]

buttons2key = {
    "B" : "c",
    "Y" : "x",
    "SELECT" : "enter",
    "START" : "space",
    "UP" : "up",
    "DOWN" : "down",
    "LEFT" : "left",
    "RIGHT" : "right",
    "A": "v",
    "X" : "enter", #"d",
    "L" : "a",
    "R" : "s"
}

# binary
while True:
    data = ser.read() # read a byte
    
    try:
        value, = struct.unpack("<b", data) # signed char
    except:
        continue
        
    #print(value)
    
    button = buttons[abs(value)-1]
    key    = buttons2key[button]
    
    if value > 0:
        #keyboard.press(buttons2key[buttons[i]])
        print("press: gamepad {} -> key {}".format(button, key))
    else:
        #keyboard.release(buttons2key[buttons[i]])
        print("release: gamepad {} -> key {}".format(button, key))

# human readable
'''
while True:
    b = ser.readline()
    
    try:
        n = int(b.decode("utf-8"))
    except:
        continue
        
    
    i = abs(n)-1
    print(n)
    
    if n > 0:
        #keyboard.press(buttons2key[buttons[i]])
        print("press {}:{}".format(buttons[i], buttons2key[buttons[i]]))
    else:
        #keyboard.release(buttons2key[buttons[i]])
        print("release {}:{}".format(buttons[i], buttons2key[buttons[i]]))
'''
    