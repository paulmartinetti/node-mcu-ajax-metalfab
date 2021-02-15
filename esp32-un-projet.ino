#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

/**** Remplace ces trois vars*/
const char* ssid = "paU1m4rT1n3TTi";
const char* password = "c4fa1$v1ngt4n5";
// chez David
//const char* projet_uri = "http://192.168.0.33:3001/projet";
// chez Paul
const char* projet_uri = "http://10.0.0.251:3001/projet";

void setup() {

  Serial.begin(115200);

  // connect to WiFi
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  // display WiFi status on watch
  Serial.println(F("Connecting ..."));

  // cancel if failed WiFi
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    return;
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  String projJson;
  projJson.reserve(500);

  HTTPClient http;
  // il faut mettre l'adresse wifi de l'ordi
  http.begin(projet_uri);
  delay(2000);
  int httpCode = http.GET();
  if (httpCode > 399) {
    Serial.print("http error");
    http.end();
  } else if (httpCode > 0) {
    // no longer need uri value, so swap w incoming json
    // (saves memory creating another String)
    projJson = http.getString();
  }  else {
    projJson = "failed";
  }
  http.end();
  delay(500);

  DynamicJsonDocument doc(500);
  DeserializationError err = deserializeJson(doc, projJson);

  struct pr {
    uint8_t id;
    char nom[40] = {NULL};
    uint16_t delayStart;
    uint16_t rampePWM;
    uint16_t pulseWelding;
    float speedBalayage;
    float speedWelding;
    float speedWire;
    float balayage;
    uint8_t pulseWire;
    uint8_t retractWire;
  };
  typedef struct pr Projet;
  Projet pr;

  // id
  if (doc["id"]) {
    pr.id = doc["id"];
    Serial.print("id = "); Serial.println(pr.id);
  } else {
    Serial.print(err.c_str());
  }
  // nom
  if (doc["nom"]) {
    strncat(pr.nom, doc["nom"], 40);
    Serial.print("nom = "); Serial.println(pr.nom);
  } else {
    Serial.println(err.c_str());
  }
  // delayStart
  if (doc["delayStart"]) {
    pr.delayStart = doc["delayStart"];
    Serial.print("delayStart = "); Serial.println(pr.delayStart);
  } else {
    Serial.print(err.c_str());
  }
  // rampePWM
  if (doc["rampePWM"]) {
    pr.rampePWM = doc["rampePWM"];
    Serial.print("rampePWM = "); Serial.println(pr.rampePWM);
  } else {
    Serial.print(err.c_str());
  }
  // pulseWelding
  if (doc["pulseWelding"]) {
    pr.pulseWelding = doc["pulseWelding"];
    Serial.print("pulseWelding = "); Serial.println(pr.pulseWelding);
  } else {
    Serial.print(err.c_str());
  }
  // speedBalayage
  if (doc["speedBalayage"]) {
    pr.speedBalayage = doc["speedBalayage"];
    Serial.print("speedBalayage = "); Serial.println(pr.speedBalayage);
  } else {
    Serial.print(err.c_str());
  }
  // speedWelding
  if (doc["speedWelding"]) {
    pr.speedWelding = doc["speedWelding"];
    Serial.print("speedWelding = "); Serial.println(pr.speedWelding);
  } else {
    Serial.print(err.c_str());
  }
  // speedWire
  if (doc["speedWire"]) {
    pr.speedWire = doc["speedWire"];
    Serial.print("speedWire = "); Serial.println(pr.speedWire);
  } else {
    Serial.print(err.c_str());
  }
  // balayage
  if (doc["balayage"]) {
    pr.balayage = doc["balayage"];
    Serial.print("balayage = "); Serial.println(pr.balayage);
  } else {
    Serial.print(err.c_str());
  }
  // pulseWire
  if (doc["pulseWire"]) {
    pr.pulseWire = doc["pulseWire"];
    Serial.print("pulseWire = "); Serial.println(pr.pulseWire);
  } else {
    Serial.print(err.c_str());
  }
  // retractWire
  if (doc["retractWire"]) {
    pr.retractWire = doc["retractWire"];
    Serial.print("retractWire = "); Serial.println(pr.retractWire);
  } else {
    Serial.print(err.c_str());
  }
}
