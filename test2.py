import base64
import requests
def sendImg(img_part):
    print(len(img_part))
    requests.put(url='http://192.168.1.5/python',data=img_part,headers={'Content-Type': 'text/plain'})

with open("saved_img-final.jpg", "rb") as img_file:
    my_string = str(base64.b64encode(img_file.read()))
    temp = my_string
    sendImg("start")
    while(len(temp) > 1024):
    	sendImg(temp[:1024])
    	temp = temp[1024:]
    sendImg(temp)
    sendImg("end")
print(my_string)
