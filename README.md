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
