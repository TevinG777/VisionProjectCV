import cv2
import numpy as np
import serial.tools.list_ports
import time

#initilize global time variable
last_send = time.time()

#Get list of ports to interact with arduino
ports = list(serial.tools.list_ports.comports())
#initialize serial port
ser = serial.Serial()
#select port that has Arduino in description
for p in ports:
    print(p.description)
