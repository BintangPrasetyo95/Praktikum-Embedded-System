#include <SPI.h>

const uint8_t MOSI_PIN = 11;
const uint8_t MISO_PIN = 12;
const uint8_t SCK_PIN = 13;
const uint8_t SS_PIN = 10;

volatile uint8_t lastReceived = 0;
volatile uint32_t recvCount = 0;

void setup() {
  Serial.begin(9600);
  delay(10);

  pinMode(MOSI_PIN, INPUT);
  pinMode(MISO_PIN, OUTPUT);
  pinMode(SCK_PIN, INPUT);
  pinMode(SS_PIN, INPUT_PULLUP);

  SPCR = _BV(SPE) | _BV(SPIE);
}

ISR(SPI_STC_vect) {
  lastReceived = SPDR;
  recvCount++;
}

void loop() {
  static uint32_t lastCount = 0;
  if (recvCount != lastCount) {
    Serial.print(">> ISR terjadi #");
    Serial.print(recvCount);
    Serial.print(" , data diterima = 0b");
    Serial.println(lastReceived, BIN);
    lastCount = recvCount;
  }
}

