#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoJson.h>

//SETUP LED
#define LED_PIN 2
#define PLUG_PIN 5
#define RED_PIN 13
#define GREEN_PIN 12
#define BLUE_PIN 14

//WIFI & server HTTP
ESP8266WebServer server(80);
#define WIFI_SSID "NETAMO.PL_ZYGMUNTA"
#define WIFI_PASSWORD "wawa2233pl"

const char* host = "espkamil";

//timer
uint32_t t_now;

void setup() {
  //Setup pin mode
  pinMode(LED_PIN, OUTPUT); //Initialize onboard LED as output
  pinMode(PLUG_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  
  Serial.begin(115200);
  Serial.println("Starting fancy remote LED");

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

  server.on("/json", handleJson);
  server.on("/rgb", handleRgb);
  server.on("/led", handleSwitch);
  server.on("/plug", handlePlug);
  server.on("/", handleMain);
  server.begin();
  MDNS.addService("http", "tcp", 80);
  Serial.println("HTTP server started");
  digitalWrite(LED_PIN, 0);
  delay(1000);
  digitalWrite(LED_PIN, 1);
}
 
void loop() {
  
  server.handleClient();

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
  
  
    server.send(200, "application/json", jsonReturner(red, green, blue, plugstat));
   
}


void handleRgb(){
 String prered = server.arg("r");
 String pregreen = server.arg("g");
 String preblue = server.arg("b");

 int red = atoi(prered.c_str());
 int green = atoi(pregreen.c_str());
 int blue = atoi(preblue.c_str());

analogWrite(RED_PIN, map(red, 0, 1023, 0, 255));
analogWrite(GREEN_PIN, map(green, 0, 1023, 0, 255));
analogWrite(BLUE_PIN, map(blue, 0, 1023, 0, 255));

String ip = WiFi.localIP().toString();
  server.sendHeader("Location", String("http://") + ip, true);
  server.send ( 200, "text/plain", "");
  server.client().stop();
}

void handlePlug(){
  if (server.arg("turn")== "on"){
    digitalWrite(PLUG_PIN, HIGH);
  }else{
    digitalWrite(PLUG_PIN, LOW);
  }

  String ip = WiFi.localIP().toString();
  server.sendHeader("Location", String("http://") + ip, true);
  server.send ( 302, "text/plain", "");
  server.client().stop();
}

void handleSwitch(){
  if (server.arg("turn")== "on"){
    digitalWrite(LED_PIN, 0);
  }else{
    digitalWrite(LED_PIN, 1);
  }

  String ip = WiFi.localIP().toString();
  server.sendHeader("Location", String("http://") + ip, true);
  server.send ( 302, "text/plain", "");
  server.client().stop();
}

void handleMain(){
  String html = "<!DOCTYPE html>\r\n";
  html += "<html>\r\n";
  html += "<head>\r\n";
  html += "<meta charset='UTF-8'>\r\n";
  html += "<title>Super fancy LED remote</title>\r\n";
  html += "<body>\r\n";

  html += "Super fancy remote - ";
  html += host;
  html += "\r\n";
  html += "parametr: turn";
  html += "\r\n";
  html += "wartosc: on/off";
  html += "\r\n";
  
  html += "</body>\r\n";
  html += "</html>\r\n";

  
  server.send(200, "text/html", html);
}
