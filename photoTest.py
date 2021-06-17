import binascii
filename = 'test.jpg'
with open(filename, 'rb') as f:
    content = f.read()
    print(binascii.hexlify(content), file=open('f', 'w'))
