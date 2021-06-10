#include <Process.h>
#include <SoftwareSerial.h>
#include <Bridge.h>

#define capture A0

const int ledPin = 13; // Built in LED in Arduino board
String msg, pic;
SoftwareSerial vSerial(9, 10);
SoftwareSerial comSerial(12, 11);

void setup() {
  // Initialization
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  msg = "";
  pic = "";

  vSerial.begin(115200);
  comSerial.begin(115200);
  pinMode(capture, INPUT);
}

void loop() {
  int isCaptureEn = digitalRead(capture);

  if(isCaptureEn == HIGH) {
    vSerial.println("start capture ...");
    comSerial.println("startcapture");
    vSerial.println("capture done ...");
    Serial.println("someone is here !\n" );
    delay(4000);
    if(Serial.available() > 0){
      String newMsg = Serial.readString();
      vSerial.println(newMsg); 
    }
  }

  else{
      // To read message received from other Bluetooth Device
  if (Serial.available() > 0){ // Check if there is data coming
    msg = Serial.readString();
    // Read the message as String
    vSerial.println("Android Command: " + msg);
  }
  }




  while(digitalRead(capture) == HIGH);
  delay(1000);
}
