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
  }

//  if (comSerial.available() > 0){ // Check if there is data coming from camera
//    pic = comSerial.readString(); // Read the message as String
//  }

  // To read message received from other Bluetooth Device
  if (Serial.available() > 0){ // Check if there is data coming
    msg = Serial.readString();
    // Read the message as String
    vSerial.println("Android Command: " + msg);
  }

  // Control LED in Arduino board
  if (msg == "haniyeh"){
    digitalWrite(ledPin, HIGH); // Turn on LED
    vSerial.println("LED is turned on\n"); // Then send status message to Android
    msg = ""; // reset command
  } else {
    if (msg == "samin"){
      digitalWrite(ledPin, LOW); // Turn off LED
      vSerial.println("LED is turned off\n"); // Then send status message to Android
      msg = ""; // reset command
    }
  }

  while(digitalRead(capture) == HIGH);
}
