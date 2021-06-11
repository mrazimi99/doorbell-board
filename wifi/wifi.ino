#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

/*Put your SSID & Password*/
const char* ssid = "nasseri";  // Enter SSID here
const char* password = "ER8QPPNU";  //Enter Password here

ESP8266WebServer server(8888);

String msg = "";

void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.on("/see", handle_see);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}
void loop() {
  
  if(Serial.available() > 0){
    msg = Serial.readString();
  }
  server.handleClient();

}

void handle_see() {

  server.send(200, "text/plain", msg); 
  //server.send(200, "text/plain", "");
}

void handle_OnConnect() {

  server.send(200, "text/html", SendHTML()); 
}

void handle_ledon() {
  server.send(200, "text/html", "handle_ledon"); 
}

void handle_ledoff() {
  server.send(200, "text/html", "handle_ledoff"); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(){
  String ptr = "<!DOCTYPE html>\n";
  ptr +="<html>\n";
  ptr +="<head>\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>HII</h1>\n";
  ptr +="<img src=\"flower.jpg\">\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
