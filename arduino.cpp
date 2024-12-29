#include <DHT.h>
#include <LiquidCrystal.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

#define RELAY_PIN 3

#define BUZZER_PIN 4
LiquidCrystal lcd(12, 11, 5, 6, 7, 8); // LCD pin: RS, E, D4, D5, D6, D7

// Ambang batas suhu dan kelembapan
#define MAX_TEMP 30      // Batas suhu maksimum (°C)
#define MIN_TEMP 18      // Batas suhu minimum (°C)
#define MAX_HUMIDITY 80  // Batas kelembapan maksimum (%)
#define MIN_HUMIDITY 40  // Batas kelembapan minimum (%)

void setup() {
  dht.begin();
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  lcd.begin(16, 2);
  lcd.print("Smart Home");
  delay(2000);
}

void loop() {
  float temp = dht.readTemperature(); 
  float humidity = dht.readHumidity();
  if (isnan(temp) || isnan(humidity)) {
    lcd.clear();
    lcd.print("Sensor Error");
    return;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(temp);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Kelembapan: ");
  lcd.print(humidity);
  lcd.print(" %");

  if (temp > MAX_TEMP || humidity > MAX_HUMIDITY) {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("AC: ON");
    
    tone(BUZZER_PIN, 1000);
  } else if (temp < MIN_TEMP || humidity < MIN_HUMIDITY) {
    digitalWrite(RELAY_PIN, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("AC: ON");
    
    tone(BUZZER_PIN, 1000);
  } else {
    digitalWrite(RELAY_PIN, LOW);
    lcd.setCursor(0, 1);
    lcd.print("AC: OFF");

    noTone(BUZZER_PIN);
  }
  
  delay(2000);
}
