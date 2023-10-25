#include <IRremote.hpp>
#include <Servo.h>

Servo servo;

int servoPos = 0;
int servoPin = 7;
int irPin = 53;

int runForwardDelay = 30;
int runBackDelay = 30;

void setup() {
  servo.attach(servoPin);
  servo.write(servoPos);
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
}

void loop() {
  if (IrReceiver.decode()) {
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
