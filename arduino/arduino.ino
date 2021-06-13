#include <Process.h>
#include <SoftwareSerial.h>
#include <Bridge.h>

#define capture A0

const int ledPin = 13; // Built in LED in Arduino board
String msg, pic;
int bluetooth = 0;
bool bluetoothSent = false;
bool wifiSent = false;
SoftwareSerial vSerial(9, 10);
SoftwareSerial comSerial(12, 11);
SoftwareSerial wifiSerial(3, 2);
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
  wifiSerial.begin(115200);
  pinMode(capture, INPUT);
}

void loop() {
  int isCaptureEn = digitalRead(capture);

  if(isCaptureEn == HIGH) {
    vSerial.println("start capture ...");
    comSerial.println("startcapture");
    vSerial.println("capture done ...");
    Serial.println("someone is here !" );
    bluetoothSent = true;
  }

  else if(wifiSent == false && bluetoothSent == true){
    // To read message received from other Bluetooth Device
    if (Serial.available() > 0){ // Check if there is data coming
      msg = Serial.readString();
      // Read the message as String
      vSerial.println("Android Command: " + msg);
      if(msg == "bluetooth ack"){
        bluetooth = 0;
        bluetoothSent = false;
        wifiSent = false;
      }
    }
    if (bluetoothSent && bluetooth < 5){
      vSerial.println("bluetooth not ok");
      bluetooth += 1;
    }
    if(bluetoothSent && bluetooth == 5){
      bluetoothSent = false;
      bluetooth = 0;
      wifiSent = true;
    }
    
  }

  else if(wifiSent){
    wifiSerial.print("start");
    vSerial.println("sent to wifi");
    wifiSent = false;
  }




  while(digitalRead(capture) == HIGH);
  delay(800);
}
