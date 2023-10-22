int ledPin = 7;
int microphoneDigitalPin = 53;
int digitalState = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
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
    delay(6000);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
