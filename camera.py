import os
import serial
arduino = serial.Serial('COM2', 115200)
while True:
    data = arduino.readline() # The last bit gets rid of the new-line chars
    if data:
    
        strdata = str(data.decode("utf-8")[:-2])
        if strdata == "startcapture":
            print("starting to capture ... ")
            os.system('python webcam-capture-v1.0.1-windows.py')
            print("capture done ... ")
