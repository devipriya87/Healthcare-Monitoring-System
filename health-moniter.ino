#include <LiquidCrystal.h>

// RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int tempPin = A0;
const int heartPin = A1;

const int ledPin = 7;
const int buzzerPin = 8;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  lcd.begin(16, 2);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Health Monitor");
  delay(2000);
  lcd.clear();

  Serial.begin(9600);
}

void loop()
{
  // ---------- TEMPERATURE ----------
  int adcValue = analogRead(tempPin);
  float voltage = adcValue * (5.0 / 1023.0);
  float temperature = voltage * 100.0;

  // ---------- HEART RATE ----------
  int heartValue = analogRead(heartPin);

  // Convert simulation value → BPM (adjustable range)
  int heartRate = map(heartValue, 0, 1023, 60, 120);

  // ---------- LCD DISPLAY ----------
  lcd.setCursor(0, 0);
  lcd.print("T:");
  lcd.print(temperature, 1);
  lcd.print("C ");

  lcd.print("HR:");
  lcd.print(heartRate);

  lcd.setCursor(0, 1);

  // ---------- ALERT CONDITION ----------
  if (temperature >= 38.0 || heartRate > 100)
  {
    lcd.print("ALERT! HIGH   ");
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
  }
  else
  {
    lcd.print("NORMAL        ");
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }

  // Serial Monitor
  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" C | HR: ");
  Serial.println(heartRate);

  delay(1000);
}