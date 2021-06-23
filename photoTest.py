import binascii
import requests
import base64
from time import sleep
'''filename = 'test.jpg'
with open(filename, 'rb') as f:
    data = f.read()
    res = requests.put(url='http://192.168.1.5/python',
                    data=data,
                    headers={'Content-Type': 'application/octet-stream'})
    print(type(res.content))
    file = open('byte.txt', 'wb')
    file.write(res.content)
    file.close()'''

def sendImg(imagePart):
    res = requests.put(url='http://103.215.221.170/bmage',
                       data=imagePart,
                       headers={'Content-Type': 'text/plain'})
    

with open("test3.jpg", "rb") as image_file:
    encoded_string = str(base64.b64encode(image_file.read()))

    '''sendImg("start")
    sleep(2)
    sendImg(encoded_string[0:1024])
    sleep(2)
    sendImg(encoded_string[1024:2048])
    sleep(2)
    sendImg("end")'''
    sendImg("start")
    temp = encoded_string
    while len(temp) > 1024:
        sendImg(temp[0:1024])
        temp = temp[1024:]
    sendImg(temp)
    sendImg("end")
    '''res = requests.put(url='http://192.168.1.5/python',
                    data=encoded_string,
                    headers={'Content-Type': 'text/plain'})
    #print(type(res.content))
    #print(type(encoded_string))
    print(str(res.content))'''



