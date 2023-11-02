#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo;

const uint8_t trigPin = 9;
const uint8_t echoPin = 10;
const uint8_t irPin = 53;
const uint8_t servoPin = 7;

uint8_t servoPos = 0;
uint8_t digitalState = 0;
uint8_t servoRepeatTimes = 4;
uint8_t runDelay = 100;
uint8_t runForwardDelay = 30;
uint8_t runBackDelay = 30;

long duration;
uint8_t distance;
uint8_t edgeDistance = 10;

String text;
uint8_t textDelay = 500;

void setup() {
  initLCD();
  initSensor();
  initServo();
  initRemote();
}

void loop() {
  lcd.clear();
  distance = detectDistance();
  runByRemote();
  runServo(distance);
}

void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void initSensor() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void initServo() {
  servo.attach(servoPin);
  servo.write(0);
}

void initRemote() {
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
}

uint8_t detectDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration / 58;
}

void runServo(uint8_t distance) {
  if (distance < edgeDistance) {
    for (uint8_t i = 0; i <= servoRepeatTimes; i++) {
      i % 2 == 0 ? servo.write(180) : servo.write(0);
      printToLCD("WALL!!!");
      delay(runDelay);
    }
  }
}

void runByRemote() {
  if (IrReceiver.decode()) {
    Serial.println("fjkfwjwkwj");
    Serial.println(String(IrReceiver.decodedIRData.decodedRawData, HEX));
    delay(100);
    if (String(IrReceiver.decodedIRData.decodedRawData, HEX) == "bb44ff00") {
      runForward(servo);
    } else if (String(IrReceiver.decodedIRData.decodedRawData, HEX) == "bf40ff00") {
      runBack(servo);
    }

    IrReceiver.resume();
  }
}

void runForward(Servo servo) {
  servo.write(180);
  delay(runForwardDelay);
}

void runBack(Servo servo) {
  servo.write(servoPos);
  delay(runBackDelay);
}

void printToLCD(String text) {
  lcd.setCursor(0, 0);
  lcd.print(text);
  delay(textDelay);
}
