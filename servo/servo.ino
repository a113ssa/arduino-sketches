#include <Servo.h>

Servo servo;

int servoPos = 0;
int digitalState = 0;

int servoPin = 7;
int microphoneDigitalPin = 53;

int runForwardDelay = 30;
int runBackDelay = 10;

void setup() {
  servo.attach(servoPin);
  servo.write(0);

  pinMode(microphoneDigitalPin, INPUT);
}

void loop() {
  microPhoneProcess(servo);
}

void microPhoneProcess(Servo servo) {
  digitalState = digitalRead(microphoneDigitalPin);

  if (digitalState == HIGH) {
    runForward(servo);
    runBack(servo);
  }
}

void runForward(Servo servo) {
  servo.write(180);
  delay(runForwardDelay);
}


void runBack(Servo servo) {
  for (servoPos = 180; servoPos >= 0; servoPos -= 1) {
    servo.write(servoPos);
    delay(runBackDelay);
  }
}
