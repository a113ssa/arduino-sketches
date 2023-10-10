int RED = 2;
int YELLOW = 5;
int GREEN = 7;

int lightDelayNumber = 2000;
int blinkDelayNumber = 200;

int blinkCount = 5;

int trafficLeds[3] = { RED, YELLOW, GREEN };

void setup() {
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);

  digitalWrite(RED, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(GREEN, LOW);
}

void loop() {
  for (int i : trafficLeds) {
    light(i);
    blink(i);
  }
}

void light(int led) {
  digitalWrite(led, HIGH);
  lightDelay();
}

void blink(int led) {
  for (int i = 0; i <= blinkCount; i++) {
    digitalWrite(led, HIGH);
    blinkDelay();
    digitalWrite(led, LOW);
    blinkDelay();
  }
}

void lightDelay() {
  delay(lightDelayNumber);
}

void blinkDelay() {
  delay(blinkDelayNumber);
}
