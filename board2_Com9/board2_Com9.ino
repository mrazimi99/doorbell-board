#include <Process.h>
#include <SoftwareSerial.h>




//SoftwareSerial wifiSerial2(5, 4);
void setup() {
  Serial.begin(115200); // Communication rate of the Bluetooth Module
}

void loop() {

  if(Serial.available() > 0){
    String x = Serial.readString();
    
  }
  
}
