#include <SPI.h>

const uint8_t MOSI_PIN = 11;
const uint8_t MISO_PIN = 12;
const uint8_t SCK_PIN = 13;
const uint8_t SS_PIN = 10;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  pinMode(MOSI_PIN, OUTPUT);
  pinMode(MISO_PIN, INPUT);
  pinMode(SCK_PIN, OUTPUT);
  pinMode(SS_PIN, OUTPUT);

  SPI.begin();
  digitalWrite(SS_PIN, HIGH);
}

void loop() {
  uint8_t outByte = 0xA5;

  Serial.print("Master kirim: 0b");
  Serial.println(outByte, BIN);

  digitalWrite(SS_PIN, LOW);

  SPI.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  SPI.transfer(outByte);
  SPI.endTransaction();
  digitalWrite(SS_PIN, HIGH);

  delay(500);
}