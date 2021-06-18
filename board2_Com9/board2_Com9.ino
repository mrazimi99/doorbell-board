#include <Process.h>
#include <SoftwareSerial.h>
#include <Wire.h>

String data = "";
byte x = 0;

void setup() {
  Wire.begin(8);
  Serial.begin(115200); // Communication rate of the Bluetooth Module
   
}

void loop() {

  if(Serial.available() > 0){
    data = Serial.readString();
    Wire.beginTransmission(4); // transmit to device #4
    Wire.write(data.c_str());        // sends five bytes
    Wire.endTransmission();    // stop transmitting

    x++;
    
  }
  
}
