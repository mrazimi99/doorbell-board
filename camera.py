import os
import serial
import time
import base64
import cv2
from time import sleep
import base64
import requests
imageLength = 1024

arduino = serial.Serial('COM2', 9600)
arduino2 = serial.Serial(port='COM7', baudrate=9600)
#time.sleep(2)

def sendPartialImage(partialImage):
    print(len(partialImage))
    requests.put(url='http://192.168.1.5/python',data=partialImage,headers={'Content-Type': 'text/plain'})


def sendImage():
    with open("saved_img-final.jpg", "rb") as img_file:
        my_string = str(base64.b64encode(img_file.read()))
        temp = my_string
        print("writing")
        #arduino2.write(temp.encode())
        sendPartialImage("start")
        while(len(temp) > imageLength):
            sendPartialImage(temp[:imageLength])
            temp = temp[imageLength:]
        sendPartialImage(temp)
        sendPartialImage("end")

def sendImageBluetooth():
    with open("saved_img-final.jpg", "rb") as img_file:
        my_string = str(base64.b64encode(img_file.read()))
        arduino2.write(bytes(my_string[0:128], 'utf-8'))
        
def captureImage():
    try:
        key = cv2. waitKey(1)
        webcam = cv2.VideoCapture(0)
        sleep(1)
        print("capture image part")
        check, frame = webcam.read()
        cv2.imshow("Capturing", frame)
        #key = cv2.waitKey(1)
        #if key == ord('s'):
        cv2.imwrite(filename='saved_img.jpg', img=frame)
        webcam.release()
        print("Processing image...")
        img_ = cv2.imread('saved_img.jpg', cv2.IMREAD_ANYCOLOR)
        print("Converting RGB image to grayscale...")
        gray = cv2.cvtColor(img_, cv2.COLOR_BGR2GRAY)
        print("Converted RGB image to grayscale...")
        print("Resizing image to 225x225 scale...")
        img_ = cv2.resize(gray,(225,225))
        print("Resized...")
        img_resized = cv2.imwrite(filename='saved_img-final.jpg', img=img_)
        print("Image saved!")

            

    
    except(KeyboardInterrupt):
        print("Turning off camera.")
        webcam.release()
        print("Camera off.")
        print("Program ended.")
        cv2.destroyAllWindows()
        
while True:
    data = arduino.readline() # The last bit gets rid of the new-line chars
    if data:
    
        strdata = str(data.decode("utf-8")[:-2])
        if strdata == "startcapture":  
            print("starting to capture ... ")
            os.system('python webcam-capture-v1.0.1-windows.py')
            #captureImage()

            '''with open("saved_img-final.jpg", "rb") as imageFile:
                content = imageFile.read()
                arduino2.write(content)'''
            print("capture done ... ")

        elif strdata == "sendImageWifi":
            sendImage()
            print("Image sent to nodemcu!")
        elif strdata == "sendImageBluetooth":
            print("bluetooth image ! ")
            sendImageBluetooth()
            print("Image sent bluetooth!")


