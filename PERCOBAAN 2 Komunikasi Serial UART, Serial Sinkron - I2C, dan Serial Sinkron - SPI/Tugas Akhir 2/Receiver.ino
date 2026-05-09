#include <Wire.h>

#define MY_ADDR   0x08
#define LDR_PIN   A0

int ldrValue = 0;

void receiveEvent(int numBytes) {
  if (numBytes >= 2) {
    int distance = (Wire.read() << 8) | Wire.read();
    Serial.print("[ULTRASONIC] Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
}

void requestEvent() {
  ldrValue = analogRead(LDR_PIN);
  Wire.write((ldrValue >> 8) & 0xFF);
  Wire.write(ldrValue & 0xFF);
  Serial.print("[LIGHT]      Value: ");
  Serial.print(ldrValue);
  Serial.println(ldrValue < 400 ? "  Dark" : "  Bright");
}

void setup() {
  Wire.begin(MY_ADDR);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
  Serial.begin(9600);
  Serial.println("Slave ready on 0x08");
}

void loop() {
  delay(100);
}