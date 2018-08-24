#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

//SETUP LED
#define LED_PIN 2
#define PLUG_PIN 5

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
