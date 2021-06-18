# Doorbell-Board

Bluetooth:

1 -> install android app (https://github.com/haniyehnasseri/doorbell)

2 -> add new com in bluetooth settings (com5 here) 

3 -> set bluetooth module com in proteus to 5

4 -> upoad .ino into arduino and start simulation

5 -> use android app and connect to pc bluetooth

6 -> send request to the board using bluetooth

Camera:

1 -> create pair com1 <-> com2

2 -> open .pdsprj and set COMPIM ports to com1

3 -> compile and upload .ino into arduino

4 -> start simulation and run python script (python serial port is set to com2)

Wifi:

1 -> upload wifi.ino to nodemcu (com3)

2 -> open Virtual Serial Port Driver Pro app and split com3 into com8 and com9 (com8 for sending data from board to nodemcu and com9 for receiving location from nodemcu)

3 -> connect one compim to main arduino with com8 and connect another one to a new board (right-side board in our diagram) with com9


* Full Setup Board guidance in boardSetup.txt

* Server code : https://github.com/mrazimi99/doorbell-server

Start the simulation and open the android app =)
