
/**
   BasicHTTPSClientNofingerprint.ino

   1.03.2019

*/

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ArduinoJson.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>


ESP8266WiFiMulti WiFiMulti;


String app_key = "x13q7uul";
bool wifiSent = false;
int wifi = 0;
String wifiMsg = "";

void setup() {

  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("nasseri", "ER8QPPNU");

  wifi = 0;
  wifiSent = false;
  wifiMsg = "";
}

int func(){
    if ((WiFiMulti.run() == WL_CONNECTED)) {

    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

    //client->setFingerprint(fingerprint);
    client->setInsecure();

    HTTPClient https;

    //Serial.print("[HTTPS] begin...\n");
    if (https.begin(*client, "https://keyvalue.immanuel.co/api/KeyVal/UpdateValue/3c76qujn/yourkey/azimi")) {  // HTTPS

      //https.addHeader("kvstoreio_api_key","64daf7295b57e3dd7762ecd7792327b894aed6317bd1e8eb1a888f7f65399f1b");
      //https.addHeader("Content-Type", "text/plain");

      //Serial.print("[HTTPS] post...\n");
      // start connection and send HTTP header
      int httpCode = https.POST("");

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        //Serial.printf("[HTTPS] POST... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = https.getString();
          //Serial.println(payload);
          return 200;

          // Json
          
//          StaticJsonBuffer<200> jsonBuffer;
//          JsonObject& root = jsonBuffer.parseObject(payload);
//          if(!root.success()) {
//            Serial.println("parseObject() failed");
//            //return false;
//          }
//          else{
//            const char* dataa = root["value"];
//            Serial.println("final res");
//            Serial.println(String(dataa));
//          }

          //
        }
      } else {
        //Serial.printf("[HTTPS] POST... failed, error: %s\n", https.errorToString(httpCode).c_str());
      }

      https.end();
    } else {
      //Serial.printf("[HTTPS] Unable to connect\n");
    }
  }
  return -1;
}

void loop() {
 

  // wait for WiFi connection

  if(Serial.available() > 0){
    wifiMsg = Serial.readString();
    
    wifiSent = true;
    wifi = 0;
  }
  
  
  if(wifiSent && wifi < 5){
    int result = func();
    if(result == 200){
      wifiSent = false;
      wifi = 0;
      wifiMsg = "";
    }
    else{
      wifi += 1; 
    }
  }

  if(wifiSent && wifi == 5){
     wifiSent = false;
     wifi = 0;
     wifiMsg = "";
  }
  //Serial.println("Wait 10s before next round...");

  if(wifiSent){
    delay(10000);
  }
}
