#define BLYNK_TEMPLATE_ID "TMPL6_iWzfGmv"
#define BLYNK_TEMPLATE_NAME "ESP8266 WIFI"
#define BLYNK_AUTH_TOKEN "U7p2Lc2fhan1VmD4ec_B6nYxi_rsWmIx"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "antek asing";
char pass[] = "iloveprabowo";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0) {
  int pinValue = param.asInt();
  digitalWrite(D1, pinValue);
}

BLYNK_WRITE(V1) {
  int pinValue = param.asInt();
  digitalWrite(D2, pinValue);
}

BLYNK_CONNECTED() {
  Blynk.setProperty(V3, "offImageUrl", "https://static image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");

  Blynk.setProperty(V3, "onImageUrl", "https://static image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");

  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup() {
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

  pinMode(D1, OUTPUT);   // PIN DIGITAL D1
  pinMode(D2, OUTPUT);   // PIN DIGITAL D2
}

void loop() {
  Blynk.run();
  timer.run();
}