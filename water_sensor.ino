#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int textDelay = 1000;
int powerDelay = 10;

int powerPin = 2;
int sensorPin = A7;
int value = 0;

String text = "";

void setup() {
  LCDInit();

  pinMode(powerPin, OUTPUT);
  pinMode(sensorPin, INPUT);
}

void loop() {
  digitalWrite(powerPin, HIGH);
  delay(powerDelay);

  sensorProcess();
  delay(textDelay);

  lcd.clear();
}

void LCDInit() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void sensorProcess() {
  value = analogRead(sensorPin);
  digitalWrite(powerPin, LOW);
  text = "Sensor value: " + String(value);
  printToLCD(text, 0);
}

void printToLCD(String text, int row) {
  lcd.setCursor(0, row);
  lcd.print(text);
}