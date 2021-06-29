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

bool gettingImage = false;
//bool firstImgPart = false;


String i2cResponse = "";
//double location_x;
//double location_y;
boolean isClose = true;

SoftwareSerial vSerial(2, 3);
SoftwareSerial lcd(10, 9);
//SoftwareSerial comSerialSend(12, 11);

void setup() {
  // i2c
//  Wire.begin(4);                // join i2c bus with address #4
//  Wire.onReceive(receiveEvent);  
  // i2c

  //blue
  Serial.begin(9600); // Communication rate of the Bluetooth Module

  // lcd communication
  lcd.begin(115200);

  // vSerial
  vSerial.begin(115200);

  // Wifi
  Serial1.begin(115200);

  // pythonSend
  Serial2.begin(9600);

  // pythonRecv
  Serial3.begin(9600);
  Serial3.setTimeout(1);
  
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
  
  msg = "";
  pic = "";

  pinMode(capture, INPUT);
}


void loop() {

  // wifi data receive
  if(Serial1.available() > 0){

    String data = Serial1.readString();
    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(data);

    if(!root.success()) {
      vSerial.println(data);
      lcd.println(data);
       
    }
    else{
      isClose = root["close"];
      vSerial.println(isClose);
    }
    
  }

  // GET image from python
  if(Serial3.available() > 0 ){
    vSerial.println("image part here ! ");
    pic = Serial3.readString();
    Serial.println(pic);
    vSerial.println(pic);
  }
  
  int isCaptureEn = digitalRead(capture);
  
  if(isCaptureEn == HIGH && gettingImage == false && bluetoothSent == false) {
    vSerial.println("start capture ...");
    Serial2.println("startcapture");
    vSerial.println("capture done ...");
    if(isClose == true){
      //Serial.println("BlueTooth : Someone Arrived ! " );
      bluetoothSent = true;
      wifiSent = false;
      gettingImage = false;
      bluetooth = 0;
      Serial2.println("sendImageBluetooth");
      vSerial.println("start sending image with bluetooth ... ");
    }
    else{
      wifiSent = false;
      bluetoothSent = false;
      bluetooth = 0;
      gettingImage = false;
      Serial2.println("sendImageWifi");
      vSerial.println("sent with wifi");
    }
  }


  
    // To read message received from other Bluetooth Device
    if (Serial.available() > 0){ // Check if there is data coming
      msg = Serial.readString();
 
      vSerial.println("Android Command : " + msg);
      
      if(msg == "start ack" && bluetoothSent == true){
        bluetooth = 0;
        //bluetoothSent = false;
        wifiSent = false;
        gettingImage = true;
        vSerial.println("starttttttt");
      }

      if(msg == "success" && gettingImage == true){
        bluetooth = 0;
        bluetoothSent = false;
        wifiSent = false;
        gettingImage = false;
        vSerial.println("doroooooost");
      }

      if(msg == "unsuccess" && gettingImage == true){
        bluetooth = 0;
        bluetoothSent = false;
        wifiSent = false;
        gettingImage = false;
        Serial2.println("sendImageWifi");
        vSerial.println("qalaaaaaat");
      }

      else{
        lcd.println(msg);
      }
    }
    if (bluetoothSent == true && gettingImage == false && bluetooth < 10){
      vSerial.println("bluetooth not ok");
      bluetooth += 1;
    }
    if(bluetoothSent == true && gettingImage == false && bluetooth == 10){
      bluetoothSent = false;
      bluetooth = 0;
      wifiSent = false;
      gettingImage = false;
      Serial2.println("sendImageWifi");
      vSerial.println("bluetooth failed ! now wifi !");
    }
    

//  else if(wifiSent){
//    wifiSent = false;
//    vSerial.println("sent with wifi");
//  }
  
  while(digitalRead(capture) == HIGH);


   delay(500);
  
}
