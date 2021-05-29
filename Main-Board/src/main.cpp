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
         newData = true;
         data = Serial.readString();

     }
}


void setup() {

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