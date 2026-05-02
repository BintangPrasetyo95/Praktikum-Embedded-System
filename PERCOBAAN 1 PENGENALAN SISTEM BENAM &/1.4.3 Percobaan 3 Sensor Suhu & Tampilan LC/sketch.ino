#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define DHTPIN 8
#define DHTTYPE DHT22 // Ganti DHT11 jika menggunakan DHT11
#define BUZZER_PIN 7
#define LED_PIN 6
#define SUHU_AMBANG 35.0 // Ambang batas suhu (°C)

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()
{
    Serial.begin(9600);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    lcd.backlight();
    lcd.init();
    dht.begin();

    // Tampilkan nama di LCD saat pertama menyala
    lcd.setCursor(0, 0);
    lcd.print("Nama: ............");
    lcd.setCursor(0, 1);
    lcd.print("NPM : ............");
    delay(3000);
    lcd.clear();
}

void loop()
{
    float suhu = dht.readTemperature();
    float kelembapan = dht.readHumidity();

    Serial.print("Suhu: ");
    Serial.print(suhu);
    Serial.println(" C");
    Serial.print("Kelembapan: ");
    Serial.print(kelembapan);
    Serial.println(" %");

    lcd.setCursor(0, 0);
    lcd.print("Suhu: ");
    lcd.print(suhu);
    lcd.print(" C ");
    lcd.setCursor(0, 1);
    lcd.print("RH: ");
    lcd.print(kelembapan);
    lcd.print(" % ");

    if (suhu >= SUHU_AMBANG)
    {
        digitalWrite(LED_PIN, HIGH);
        tone(BUZZER_PIN, 1000);
    }
    else
    {
        digitalWrite(LED_PIN, LOW);
        noTone(BUZZER_PIN);
    }
    delay(2000);
}