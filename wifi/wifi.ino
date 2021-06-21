

/**
   BasicHTTPSClientNofingerprint.ino

   1.03.2019

*/


#include "ESP8266HTTPClient.h"
#include "ESP8266WiFi.h"
#include <ArduinoJson.h>

#include <ESP8266WebServer.h>

ESP8266WebServer server(80);




const char* ssid = "nasseri";
const char* password =  "ER8QPPNU";
WiFiClient client;

bool wifiSent = false;
int wifi = 0;
String wifiMsg = "";
bool getLocation = true;

unsigned long locationTimerDelay = 20000;
unsigned long locationLastTime = 0;


//unsigned long lcdMsgTimerDelay = 20000;
//unsigned long lcdMsgLastTime = 0;


int sendDataToServer(){
   if(WiFi.status()== WL_CONNECTED){

   HTTPClient http;  

    
   // time
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


int sendImageToServer(String message){
   if(WiFi.status()== WL_CONNECTED){

   HTTPClient http;   

   // image (body)
   http.begin(client,"http://103.215.221.170/message?text=" + message);
   http.addHeader("Content-Type", "text/plain");            

   int httpResponseCode = http.PUT("");   

   if(httpResponseCode>0){

    Serial.println("image sent");

    String response = http.getString(); 

    Serial.println(httpResponseCode);

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

   if( (WiFi.status() == WL_CONNECTED)  && ((millis() - locationLastTime) > locationTimerDelay)){
    locationLastTime = millis();
   HTTPClient http;   

   // location
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

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());  //Print the local IP
 
  server.on("/python", handleBody); //Associate the handler function to the path
 
  server.begin(); //Start the server
  Serial.println("Server listening");

  wifi = 0;
  wifiSent = false;
  wifiMsg = "";

  getLocation = true;

}


void handleBody() { //Handler for the body path
 
      if (server.hasArg("plain")== false){ //Check if body received
 
            server.send(200, "text/plain", "Body not received");
            return;
 
      }
 
      String message = server.arg("plain");
 
      server.send(200, "text/plain", message);
      sendImageToServer(message);
}


void loop() {

  server.handleClient(); //Handling of incoming requests
 
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
