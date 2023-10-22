#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int trigPin = 9;
const int echoPin = 10;

long duration;
int distance;
int textDelay = 500;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58;
  String text = "Distance: " + String(distance) + "cm";
  printToLCD(text);
  Serial.println(distance);
}

void printToLCD(String text) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(text);
  delay(textDelay);
}
