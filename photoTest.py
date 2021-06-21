import binascii
import requests
import base64
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


with open("test3.jpg", "rb") as image_file:
    encoded_string = str(base64.b64encode(image_file.read()))
    res = requests.put(url='http://192.168.1.5/python',
                    data=encoded_string[0:11],
                    headers={'Content-Type': 'text/plain'})
    print(type(res.content))
    #print(type(encoded_string))
    print(str(res.content))



