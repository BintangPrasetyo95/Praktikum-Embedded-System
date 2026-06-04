#include <DHT.h>

// --- Pin Definitions ---
#define DHTPIN D1          // DHT22 Data pin
#define DHTTYPE DHT11      // Specify sensor type
DHT dht(DHTPIN, DHTTYPE);

#define FLAME_PIN D2       // Flame sensor digital output
#define BUZZER_PIN D5      // Buzzer positive pin
#define LED_RED D6         // Fire detected
#define LED_YELLOW D7      // High temperature warning
#define LED_GREEN D8       // Safe status

// --- Thresholds ---
const float TEMP_WARNING = 35.0; // Temperature in Celsius to trigger warning

void setup() {
  Serial.begin(115200);
  Serial.println("System Initializing...");
  
  dht.begin();
  
  // Set pin modes
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  
  // Start with all alarms off
  turnOffAlarms();
}

void loop() {
  // 1. Read the sensors
  // Note: Most flame sensors return LOW when fire is detected (Active LOW)
  int flameState = digitalRead(FLAME_PIN); 
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  // Check if DHT read failed
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(2000);
    return;
  }

  // Print data to Serial Monitor for debugging
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print("°C | Humidity: ");
  Serial.print(humidity);
  Serial.print("% | Flame State: ");
  Serial.println(flameState == LOW ? "FIRE DETECTED!" : "Clear");

  // 2. Logic & Alerts
  if (flameState == LOW) {
    // CRITICAL ALERT: Fire detected
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, LOW);
    
    // Pulse the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    delay(200);
    digitalWrite(BUZZER_PIN, LOW);
    delay(200);
    
  } else if (temperature > TEMP_WARNING) {
    // WARNING ALERT: High temperature
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(BUZZER_PIN, LOW); // Buzzer off
    delay(1000); // Wait a second before checking again
    
  } else {
    // NORMAL STATUS: All clear
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_YELLOW, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    delay(2000); // Read sensor every 2 seconds
  }
}

// Helper function to ensure everything is off at startup
void turnOffAlarms() {
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
}