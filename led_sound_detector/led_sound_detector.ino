int ledPin = 7;
int microphoneDigitalPin = 53;
int digitalState = 0;
int ledDelay = 6000;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(microphoneDigitalPin, INPUT);
}

void loop() {
  microPhoneProcess();
}

void microPhoneProcess() {
  digitalState = digitalRead(microphoneDigitalPin);

  if (digitalState == HIGH) {
    digitalWrite(ledPin, HIGH);
    delay(ledDelay);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
