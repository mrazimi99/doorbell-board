import os
import serial
import time
import base64
arduino = serial.Serial('COM2', 9600, timeout=.1)
arduino2 = serial.Serial(port='COM7', baudrate=9600, timeout=.1)
#time.sleep(2)
while True:
    data = arduino.readline() # The last bit gets rid of the new-line chars
    if data:
    
        strdata = str(data.decode("utf-8")[:-2])
        if strdata == "startcapture":
        
                
            print("starting to capture ... ")
            os.system('python webcam-capture-v1.0.1-windows.py')

            '''with open("saved_img-final.jpg", "rb") as imageFile:
                content = imageFile.read()
                arduino2.write(content)'''
            print("capture done ... ")


