#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include "DHT.h"        // including the library of DHT11 temperature and humidity sensor
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 0  //here we are defining the pin number where we will recieve the datas
DHT dht(dht_dpin, DHTTYPE); 
float tmp=0,hum=0;
void getdata(){
    float h = dht.readHumidity();
    float t = dht.readTemperature();  
    tmp=t;
    hum=h;       
    Serial.print("Current humidity = ");
    Serial.print(h);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(t); 
    Serial.println("C  ");
}


void setup() {
  dht.begin();
  Serial.begin(9600);                 //Serial connection
//   WiFi.begin("Your Network Name", "network password");   //WiFi connection
WiFi.begin("your wifi name", "your wifi password");   //WiFi 
  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion
    delay(500);
    Serial.println("Waiting for connection");

  }
 
}

void loop() {
 
if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status
 Serial.println("Connected Working");
HTTPClient http;  //Declare an object of class HTTPClient
getdata();
 http.begin("http://yourlink.herokuapp.com/nodemcujson");  //Specify request destination
 http.addHeader("Content-Type", "application/json");
 String s1 = String(tmp);
 String s2 = String(hum);
 String api="\"babayaga_home\"";
String s4="\"humidity\":"+s2;
String api_key="\"api_key\":"+api;
String payload="{\"tmp\":"+s1+","+s4+","+api_key+" }";
//here in this code for testing purpose we are sending the data of living //room  i.e the data of humidity and temperature along with the API key , this api key
//is used to verify each of the users uniquely and thus API key is assigned //to each user uniquely .
int httpCode = http.POST(payload);
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

delay(100);    //Send a request every 30 seconds
 
}

