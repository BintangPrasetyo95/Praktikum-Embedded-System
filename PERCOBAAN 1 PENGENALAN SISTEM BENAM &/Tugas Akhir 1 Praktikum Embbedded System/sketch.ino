#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define TEMP_PIN A0
#define BUZZER_PIN 8
#define LED_PIN 9

#define DIST_THRESHOLD 20   // cm  → buzzer aktif jika jarak < 20 cm
#define TEMP_THRESHOLD 35.0 // °C  → LED aktif jika suhu > 30 °C

LiquidCrystal_I2C lcd(0x27, 16, 2);

void runningTextDouble(String text0, String text1, int delayMs)
{
    String pad = "                "; // 16 spasi
    String s0 = pad + text0 + pad;
    String s1 = pad + text1 + pad;

    int steps = max(s0.length(), s1.length()) - 16;

    for (int i = 0; i <= steps; i++)
    {
        lcd.setCursor(0, 0);
        lcd.print(s0.substring(i, i + 16));

        lcd.setCursor(0, 1);
        lcd.print(s1.substring(i, i + 16));

        delay(delayMs);
    }
}

float readDistance()
{
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    long duration = pulseIn(ECHO_PIN, HIGH, 30000);
    if (duration == 0)
        return -1;
    return duration * 0.034 / 2.0;
}

float readTemperature()
{
    int raw = analogRead(TEMP_PIN);
    float voltage = raw * (5.0 / 1023.0);
    // NTC Wokwi: 0V = -55°C, 5V = 125°C (range 180°C)
    float tempC = (voltage / 5.0) * 180.0 - 55.0;
    return tempC;
}

void setup()
{
    Serial.begin(9600);

    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);

    lcd.init();
    lcd.backlight();

    lcd.clear();
    runningTextDouble("Bintang Prastyo", "NPM: 2455061007", 100);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Bintang Prastyo");
    Serial.println("Bintang Prastyo");
    lcd.setCursor(0, 1);
    lcd.print("NPM: 2455061007");
    Serial.println("NPM: 2455061007");
    delay(2000);

    lcd.clear();
}

void loop()
{
    float tempC = readTemperature();
    float distance = readDistance();

    digitalWrite(LED_PIN, tempC > TEMP_THRESHOLD ? HIGH : LOW);

    if (distance >= 0 && distance < DIST_THRESHOLD)
    {
        tone(BUZZER_PIN, 1000);
    }
    else
    {
        noTone(BUZZER_PIN);
    }

    lcd.setCursor(0, 0);
    lcd.print("Suhu: ");
    lcd.print(tempC, 1);
    lcd.print((char)223); // karakter °
    lcd.print("C");
    // Tanda ! di kolom 15 jika melewati ambang
    lcd.setCursor(14, 0);
    lcd.print(tempC > TEMP_THRESHOLD ? " !" : "  ");

    lcd.setCursor(0, 1);
    lcd.print("Jarak: ");
    if (distance < 0)
    {
        lcd.print("---  ");
    }
    else
    {
        lcd.print(distance, 1);
        lcd.print("cm ");
    }
    lcd.setCursor(14, 1);
    lcd.print((distance >= 0 && distance < DIST_THRESHOLD) ? " !" : "  ");

    Serial.print("Suhu: ");
    Serial.print(tempC, 1);
    Serial.print(" C  |  Jarak: ");
    if (distance < 0)
        Serial.println("timeout");
    else
    {
        Serial.print(distance, 1);
        Serial.println(" cm");
    }

    delay(300);
}