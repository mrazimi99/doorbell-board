#include <Process.h>
#include <SoftwareSerial.h>
#include <Bridge.h>
#include <Wire.h>
#include <ArduinoJson.h>

#define capture A0

const int ledPin = 13; // Built in LED in Arduino board
String msg, pic;
int bluetooth = 0;
bool bluetoothSent = false;
bool wifiSent = false;
bool getLocation = true;


String i2cResponse = "";
//double location_x;
//double location_y;
boolean isClose = true;

SoftwareSerial vSerial(9, 10);
SoftwareSerial comSerialSend(12, 11);
//SoftwareSerial wifiSerial(3, 2);

void setup() {
  // Initialization
  //pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  // i2c
  Wire.begin(4);                // join i2c bus with address #4
  Wire.onReceive(receiveEvent);  
  // i2c
  Serial.begin(9600); // Communication rate of the Bluetooth Module
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  msg = "";
  pic = "";

  vSerial.begin(115200);
  comSerialSend.begin(9600);
  //wifiSerial.begin(9600);
  pinMode(capture, INPUT);
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  i2cResponse = "";
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    i2cResponse += c;
  }
  int x = Wire.read();    // receive byte as an integer
  vSerial.println(i2cResponse);         // print the integer
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(i2cResponse);

  if(!root.success()) {
    return;
  }

  isClose = root["close"];

  vSerial.println(isClose);
  //vSerial.println(location_y);
  
}

void loop() {

//  if(wifiSerial.available() > 0){
//    String img = wifiSerial.readString();
//    vSerial.println(img);
//  }

  int isCaptureEn = digitalRead(capture);
  
  if(isCaptureEn == HIGH) {
    vSerial.println("start capture ...");
    comSerialSend.println("startcapture");
    vSerial.println("capture done ...");
    if(isClose == true){
      Serial.println("BlueTooth : Someone Arrived ! " );
      //comSerialSend.println("sendImageBluetooth");
      bluetoothSent = true;
      wifiSent = false;
      vSerial.println("sent with bluetooth");
    }
    else{
      comSerialSend.println("sendImageWifi");
      wifiSent = false;
      bluetoothSent = false;
      bluetooth = 0;
      vSerial.println("sent with wifi");
    }
  }


  else if(wifiSent == false){
    // To read message received from other Bluetooth Device
    if (Serial.available() > 0){ // Check if there is data coming
      msg = Serial.readString();
 
      vSerial.println("Android Command : " + msg);
      
      if(msg == "bluetooth ack"){
        bluetooth = 0;
        bluetoothSent = false;
        wifiSent = false;
      }

      else{
        Wire.beginTransmission(12); // transmit to device #4
        Wire.write(msg.c_str());        // sends five bytes
        Wire.endTransmission();    // stop transmitting
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
    //wifiSerial.print("start");
    comSerialSend.println("sendImageWifi");
    wifiSent = false;
    vSerial.println("sent with wifi");
  }
  
  while(digitalRead(capture) == HIGH);

  delay(500);
  
}
