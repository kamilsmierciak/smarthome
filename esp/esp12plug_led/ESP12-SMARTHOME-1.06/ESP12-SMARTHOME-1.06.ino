#include <ArduinoJson.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <OneWire.h>
#include <DallasTemperature.h>


#define RED_LED 7
#define GREEN_LED 6
#define BLUE_LED 5
#define TEMP_PIN 19
#define PLUG_PIN 20

unsigned long previousMillis = 0; //variable for temp
const long interval = 1000;
float temp = 0;

//****TEMP****
OneWire oneWire(TEMP_PIN);
DallasTemperature sensors(&oneWire);


//WIFI & server HTTP
ESP8266WebServer server(80);
#define WIFI_SSID "NETAMO.PL_ZYGMUNTA"
#define WIFI_PASSWORD "wawa2233pl"

const char* host = "esp12";

//timer
uint32_t t_now;

//json
String json = "";

void setup(void) {
  //Setup pin mode
  

  Serial.begin(115200);
  Serial.println("Smarthome");

  //Setup WIFI 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WIFI");

  //Wait for WIFI connection
  while( WiFi.status() != WL_CONNECTED ) {
    delay(200);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println( WIFI_SSID );
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  //DNS
  MDNS.begin(host);

  //Setup HTTP server

  server.on("/", handleMain);
  server.on("/json", handleJson);
  server.on("/plug", handlePlug);
  server.on("/setcolor", handleColor);
  server.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.println("HTTP server started");
  delay(1000);

//  //***TEMP***
//  sensors.begin();
//  sensors.requestTemperatures();

  delay(1000);
  //pinmode led
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  digitalWrite(RED_LED, 0);
  digitalWrite(GREEN_LED, 0);
  digitalWrite(BLUE_LED, 0);

  
}
 
void loop(void) {



  //****Handlers****
  
//  server.handleClient();
//
//  //****Temp****
//  unsigned long currentMillis = millis();
//
//  if (currentMillis - previousMillis >= interval) {
//    previousMillis = currentMillis; 
//    temp = sensors.getTempCByIndex(0);
//    sensors.requestTemperatures();
//  }

}

String jsonReturner(int red, int green, int blue, String plugstat){
  
  String json = "";
  const size_t bufferSize = JSON_OBJECT_SIZE(4);
  
DynamicJsonBuffer jsonBuffer(bufferSize);

    JsonObject& root = jsonBuffer.createObject();
    root["red"] = red;
    root["green"] = green;
    root["blue"] = blue;
    root["plug"] = plugstat;
    root.printTo(json);

    return json;
}

//****Plug****
void handlePlug(){
  if (server.arg("turn")== "on"){
    digitalWrite(PLUG_PIN, HIGH);
  }else if(server.arg("turn")== "off"){
    digitalWrite(PLUG_PIN, 1);
  }

  String ip = WiFi.localIP().toString();
  server.sendHeader("Location", String("http://") + ip, true);
  server.send ( 302, "text/plain", "");
  server.client().stop();
}





void handleMain(){
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head>";
  html += "<meta charset='UTF-8'>\r\n";
  html += "<title>Super fancy LED remote</title><br>";
  html += "<body>";

  html += "Super fancy remote - ";
  html += host;
  html += "</br>";
  html += "parametr: turn";
  html += "</br>";
  html += "wartosc: on/off";
  html += "</br>";
  
  html += "</body>";
  html += "</html>";

  
  server.send(200, "text/html", html);
}

void handleJson(){
    //****JSON****
  
  String plugstat = "";
  int red = digitalRead(RED_PIN);
  int green = digitalRead(GREEN_PIN);
  int blue = digitalRead(BLUE_PIN);

  //****Plug Status****
  if(digitalRead(PLUG_PIN) == HIGH){
    plugstat = "on";
  }else {
    plugstat = "off";
  }
  
  
    server.send(200, "application/json", jsonReturner(red, green, blue, temp, plugstat));
   
}

void handleColor(){
  const size_t bufferSize2 = JSON_OBJECT_SIZE(3) + 30;
DynamicJsonBuffer jsonBuffer(bufferSize2);

const char* json2 = "{\"red\":225,\"green\":0,\"blue\":21}";

JsonObject& root = jsonBuffer.parseObject(json2);

int red = root["red"];
int green = root["green"];
int blue = root["blue"];

digitalWrite(RED_LED, red);
digitalWrite(GREEN_LED, green);
digitalWrite(BLUE_LED, blue);
}

