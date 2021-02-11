#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <ArduinoJson.h>
#include "index.h"

const char* ssid = "";
const char* password = "";

WebServer server(80);

void handleRoot() {
 String s = webpage;
 server.send(200, "text/html", s);
}

void sendJson(){  
  //StaticJsonDocument<1100> jsonBuffer;
  String jsonStr = "{\"projet1\":{\"id\":1,\"nom\":\"D1_Eco 50\",\"delayStart\":1000,\"rampePWM\":40,\"speedWelding\":7.5,\"balayage\":0.8,\"speedWire\":18,\"pulseWire\":5,\"retractWire\":7,\"huitieme\":5,\"neuvieme\":3},\"projet2\":{\"id\":2,\"nom\":\"D2_Janisol\",\"delayStart\":1200,\"rampePWM\":60,\"speedWelding\":3,\"balayage\":1,\"speedWire\":6,\"pulseWire\":3,\"retractWire\":9,\"huitieme\":2,\"neuvieme\":7},\"projet3\":{\"id\":3,\"nom\":\"Janisol_2\",\"delayStart\":800,\"rampePWM\":20,\"speedWelding\":1,\"balayage\":2,\"speedWire\":16,\"pulseWire\":2,\"retractWire\":4,\"huitieme\":10,\"neuvieme\":5}}";
  server.send(200, "application/json", jsonStr);
}

/*void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
}*/

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  //digitalWrite(led, 0);
}

void setup(void) {
  //pinMode(led, OUTPUT);
  //digitalWrite(led, 0);
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/my_json", sendJson);
  
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
}
