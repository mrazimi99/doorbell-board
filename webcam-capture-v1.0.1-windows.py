import cv2
from time import sleep
key = cv2. waitKey(1)
webcam = cv2.VideoCapture(0)
sleep(1)
imageLength = 1024

def sendPartialImage(partialImage):
    print(len(partialImage))
    requests.put(url='http://192.168.1.5/python',data=partialImage,headers={'Content-Type': 'text/plain'})


def sendImage():
    with open("saved_img-final.jpg", "rb") as img_file:
        my_string = str(base64.b64encode(img_file.read()))
        temp = my_string
        sendImg("start")
        while(len(temp) > imageLength):
            sendPartialImage(temp[:imageLength])
            temp = temp[imageLength:]
        sendPartialImage(temp)
        sendPartialImage("end")


try:
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
    sendImage()
    print("Image sent to nodemcu!")
            

    
except(KeyboardInterrupt):
    print("Turning off camera.")
    webcam.release()
    print("Camera off.")
    print("Program ended.")
    cv2.destroyAllWindows()
