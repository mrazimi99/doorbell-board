#include <Process.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <ArduinoJson.h>

SoftwareSerial wifiLCD(12, 11);
String data = "";
byte x = 0;

void setup() {
  Wire.begin(8);
  Serial.begin(115200); // Communication rate of the Bluetooth Module
  wifiLCD.begin(115200);
}

void loop() {

  if(Serial.available() > 0){

    data = Serial.readString();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(data);

    if(!root.success()) {
      Wire.beginTransmission(12); // transmit to device #4
      Wire.write(data.c_str());        // sends five bytes
      Wire.endTransmission();    // stop transmitting
    }
    else{
      Wire.beginTransmission(4); // transmit to device #4
      Wire.write(data.c_str());        // sends five bytes
      Wire.endTransmission();    // stop transmitting
    }

    x++;
    
  }

  
}
