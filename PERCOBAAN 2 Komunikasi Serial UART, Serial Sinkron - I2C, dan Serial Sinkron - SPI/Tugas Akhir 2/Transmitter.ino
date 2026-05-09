#include <Wire.h>

#define SLAVE_ADDR 0x08
#define TRIG 9
#define ECHO 10

long getDistance() {
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  long duration = pulseIN(ECHO, HIGH);
  return duration * 0.034 / 2; // CM
}

void setup()
{
  Wire.begin();
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  Serial.println("Master Ready");
}

void loop()
{
  long distance = getDistance();
  
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write((distance >> 8) & 0xFF);
  Wire.write(distance & 0xFF);
  byte err = Wire.endTransmission();
  
  if (err == 0) {
    Serial.print("[ULTRASONIC] Distance: ");
    Serial.print(distance);
    Serial.println(" CM");
  } else {
    Serial.print("[TX ERROR]");
    Serial.println(err);
    delay(1000);
    return;
  }
  
  delay(10);
  
  Wire.requestFrom(SLAVE_ADDR, 2, true);
  if (Wire.available() == 2) {
    int light = (Wire.read() << 8) | Wire.read();
    Serial.print("[LIGHT] Value: ");
    Serial.print(light);
  }
  
  delay(1000);
}