const int sensorCahayaPin = A0;
const int pwmLedPin = 3;
const int nonPwmLedPin = 2;
const float resistorValue = 10000.0;
const float voltageSupply = 5.0;
const float sensorVoltageDivider = 1023.0;

void setup()
{
    Serial.begin(9600);
    pinMode(pwmLedPin, OUTPUT);
    pinMode(nonPwmLedPin, OUTPUT);
    Serial.println("Praktikum Embedded Systems");
    Serial.println("LAB TEKNIK DIGITAL");
}

void loop()
{
    int ldrValue = analogRead(sensorCahayaPin);
    float voltage = (ldrValue / sensorVoltageDivider) * voltageSupply;
    float resistance = (voltageSupply / voltage - 1) * resistorValue;
    int lux = map(resistance, 0, resistorValue, 0, 255);

    Serial.print("Nilai ADC: ");
    Serial.println(ldrValue);
    Serial.print("Tegangan: ");
    Serial.print(voltage);
    Serial.println(" V");
    Serial.print("Resistansi LDR: ");
    Serial.print(resistance);
    Serial.println("Ohm");

    analogWrite(pwmLedPin, lux);
    analogWrite(nonPwmLedPin, lux);
    delay(1000);
}