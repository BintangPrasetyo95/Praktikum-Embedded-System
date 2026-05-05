void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    String pesan = Serial.readStringUntil("\n");
    Serial.print("Pesan yang diterima: ");
    Serial.println(pesan);
  }
}