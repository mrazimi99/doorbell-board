

/**
   BasicHTTPSClientNofingerprint.ino

   1.03.2019

*/


#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include <ArduinoJson.h>


const char* ssid = "HUAWEI P10 Plus";
const char* password =  "hani1234";
WiFiClient client;

bool wifiSent = false;
int wifi = 0;
String wifiMsg = "";
bool getLocation = true;

unsigned long timerDelay = 20000;
unsigned long lastTime = 0;


int sendDataToServer(){
   if(WiFi.status()== WL_CONNECTED){

   HTTPClient http;   

   http.begin(client,"http://103.215.221.170/message?text=someone_arrived!");
   http.addHeader("Content-Type", "text/plain");            

   int httpResponseCode = http.PUT("");   

   if(httpResponseCode>0){

    String response = http.getString();            

    if(httpResponseCode == 200){
      return 200;        
    }

   }else{

   }

   http.end();

 }else{
 }
 return -1;
}


String getDataFromServer(){

   if( (WiFi.status() == WL_CONNECTED)  && ((millis() - lastTime) > timerDelay)){
    lastTime = millis();
   HTTPClient http;   

   http.begin(client,"http://103.215.221.170/location");
   http.addHeader("Content-Type", "text/plain");            

   int httpResponseCode = http.GET();


   if(httpResponseCode>0){
    String response = http.getString();

    StaticJsonBuffer<200> jsonBuffer;
    JsonObject& root = jsonBuffer.parseObject(response);

    if(!root.success()) {
      return "";
    }

    return response;
    
   }else{
   }

   http.end();
   
 }else{
 }
 return "";
}

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password); 

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");

  wifi = 0;
  wifiSent = false;
  wifiMsg = "";

  getLocation = true;

}


void loop() {
 
  // wait for WiFi connection

  if(Serial.available() > 0){
    wifiMsg = Serial.readString();
    if(wifiMsg == "start"){
        wifiSent = true;
        wifi = 0;
        getLocation = false;
    }
  }

  if(getLocation == true){
    String location = getDataFromServer();
    if(location != ""){
      Serial.println(location);
    }  
  }
  
  
  if(wifiSent && wifi < 5){
    int result = sendDataToServer();
    if(result == 200){
      wifiSent = false;
      wifi = 0;
      wifiMsg = "";
      getLocation = true;
    }
    else{
      wifi += 1; 
    }
  }

  if(wifiSent && wifi == 5){
     wifiSent = false;
     wifi = 0;
     wifiMsg = "";
     getLocation = true;
  }

  if(wifiSent){
    delay(10000);
  }
}
