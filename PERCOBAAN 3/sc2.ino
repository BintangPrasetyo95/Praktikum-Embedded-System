#define BLYNK_TEMPLATE_ID "TMPL6_iWzfGmv"
#define BLYNK_TEMPLATE_NAME "ESP8266 WIFI"
#define BLYNK_AUTH_TOKEN "aYNjiBwOM07ouE-YQqguo1uu22cZ62m-"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] = BLYNK_AUTH_TOKEN;

// Your WiFi credentials
char ssid[] = "antek asing";
char pass[] = "iloveprabowo";

#define DHTPIN D4
#define DHTTYPE DHT11

#define BUZZER_PIN D5

float batasSuhu = 25.0;

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendSensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C, Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, h);

  if (t > batasSuhu) {
    tone(BUZZER_PIN, 1000);
    Blynk.virtualWrite(V4, 1);
    Serial.println("Peringatan: suhu tinggi, buzzer menyala");
  } else {
    noTone(BUZZER_PIN);
    Blynk.virtualWrite(V4, 0);
  }
}

BLYNK_CONNECTED() {
  Blynk.setProperty(V5, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V5, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V5, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void setup() {
  Serial.begin(115200);

  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);

  Blynk.begin(auth, ssid, pass);
  dht.begin();

  timer.setInterval(2000L, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}