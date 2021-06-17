#include <Process.h>
#include <SoftwareSerial.h>
#include <Bridge.h>


#define capture A0

const int ledPin = 13; // Built in LED in Arduino board
String msg, pic;
int bluetooth = 0;
bool bluetoothSent = false;
bool wifiSent = false;
bool getLocation = true;

String x = "";
String y = "";

SoftwareSerial vSerial(9, 10);
SoftwareSerial comSerialSend(12, 11);
SoftwareSerial wifiSerial(3, 2);
//SoftwareSerial wifiSerial2(5, 4);
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
  comSerialSend.begin(9600);
  //comSerialReceive.begin(9600);
  wifiSerial.begin(115200);
  //wifiSerial2.begin(115200);
  pinMode(capture, INPUT);
}

void loop() {

  int isCaptureEn = digitalRead(capture);


  if(isCaptureEn == HIGH) {
    vSerial.println("start capture ...");
    comSerialSend.println("startcapture");
    vSerial.println("capture done ...");
    Serial.println("someone is here !" );
    bluetoothSent = true;
    //getLocation = false;
  }

//  if(getLocation == true){
//    //vSerial.println("ava");
//    if(wifiSerial2.available() > 0){
//      vSerial.println("location");
//      x = wifiSerial2.readString();
//      vSerial.println("x: " + x);
//      y = wifiSerial2.readString();
//      vSerial.println("y: " + y);
//    }
//  }

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
        //getLocation = true;
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
    getLocation = true;
  }
  
  while(digitalRead(capture) == HIGH);
  //if(getLocation == false){
  delay(1000);
  //}
  
}
