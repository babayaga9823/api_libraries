#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

void setup() {
 
  Serial.begin(9600);                 //Serial connection
  WiFi.begin("Your wifi Name", "Your wifi Password");   //WiFi connection
 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");

  }
 
}

void loop() {
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 Serial.println("Connected Working");

HTTPClient http;  //Declare an object of class HTTPClient
 http.useHTTP10(true);
 http.begin("your hosted server url");  //Specify request destination
int httpCode = http.GET();                                                                  //Send the request
  if (httpCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpCode);
      }

http.end();   //Close connection
}

delay(10000);    //Send a request every 30 seconds
 
}

