#include <Arduino.h>
#include <SoftwareSerial.h>
#include <AltSoftSerial.h>
#include <LiquidCrystal.h>
#include <Wire.h>




LiquidCrystal lcd(4, 6, 10, 11, 12, 13);


bool newData;


char receivedMsg[16];

String data;


void recieveMessageWithBluetooth()
{
 
     if (Serial.available() > 0) 
     {
        
         data = Serial.readString();
         if(data.indexOf("bluetooth ack") != 0){
             newData = true;
         }

     }
}

// function that executes whenever data is received from master
// this function is registered as an event, see setup()
void receiveEvent(int howMany)
{
  data = "";
  while(1 < Wire.available()) // loop through all but the last
  {
    char c = Wire.read(); // receive byte as a character
    data += c;
  }
  int x = Wire.read();    // receive byte as an integer
  newData = true;
}



void setup() {

    // i2c
    Wire.begin(12);                // join i2c bus with address #4
    Wire.onReceive(receiveEvent);  
    // i2c

	lcd.begin(20, 4);
    Serial.begin(9600); 

    newData = false;

}


void loop() {

    recieveMessageWithBluetooth();


    if (newData)   { 
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print(data);
        newData = false;
    }


}