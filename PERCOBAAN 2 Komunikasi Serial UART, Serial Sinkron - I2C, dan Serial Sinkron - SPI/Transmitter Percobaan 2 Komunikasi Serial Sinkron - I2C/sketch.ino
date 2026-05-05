#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String message = Serial.readString();
    Wire.beginTransmission (8);
    Wire.write(message.c_str());
    Wire.endTransmission();
    Serial.println("Message sent: " + message);
  }
  delay(1000);
}
