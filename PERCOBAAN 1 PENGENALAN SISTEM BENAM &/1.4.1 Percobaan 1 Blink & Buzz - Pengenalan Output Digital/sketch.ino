#define led 8
#define buzzer 7

void setup()
{
    pinMode(led, OUTPUT);
    pinMode(buzzer, OUTPUT);
}

void loop()
{
    digitalWrite(led, HIGH);
    tone(buzzer, 2000);
    delay(1000);
    digitalWrite(led, LOW);
    noTone(buzzer);
    delay(1000);
}