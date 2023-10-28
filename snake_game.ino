#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t irPin = 53;
const String button_2 = "e718ff00";
const String button_4 = "f708ff00";
const String button_6 = "a55aff00";
const String button_8 = "ad52ff00";

String snake = "=";
String target = "+";
uint8_t snakePositionRow = 0;
uint8_t snakePositionColumn = 0;

uint8_t headPositionColumn = 0;

uint8_t taleRows[30];
uint8_t taleColumns[30];

uint8_t targetPositionRow = 0;
uint8_t targetPositionColumn = 0;

uint8_t rowCount = 2;
uint8_t columnCount = 16;

uint8_t textDelay = 100;

uint8_t score = 0;

boolean isRight = true;

void setup() {
  initLCD();
  printToLCD(snakeText(), snakePositionRow, snakePositionColumn);
  printToLCD(target, setTargetRow(), setTargetColumn());
  IrReceiver.begin(irPin, ENABLE_LED_FEEDBACK);
}

void loop() {
  normalizeSnakePositions();
  detectSnakeMovement();
}

void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
}

void printToLCD(String text, uint8_t row, uint8_t column) {
  lcd.setCursor(column, row);
  lcd.print(text);
  delay(textDelay);
}

uint8_t setTargetRow() {
  targetPositionRow = rand() % rowCount;
  return targetPositionRow;
}

uint8_t setTargetColumn() {
  targetPositionColumn = rand() % columnCount;
  return targetPositionColumn;
}

void normalizeSnakePositions() {
  snakePositionRow = normalizeRow(snakePositionRow);
  snakePositionColumn = normalizeColumn(snakePositionColumn);
}

uint8_t normalizeRow(uint8_t row) {
  return row % rowCount;
}

uint8_t normalizeColumn(uint8_t column) {
  return column % columnCount;
}

void detectSnakeMovement() {
  if (IrReceiver.decode()) {
    String decodedCode = String(IrReceiver.decodedIRData.decodedRawData, HEX);
    if (decodedCode == button_2) {
      snakePositionRow += 1;
    } else if (decodedCode == button_4) {
      snakePositionColumn -= 1;
      headPositionColumn = snakePositionColumn;
      if (isRight) {
        toggleIsRight();
      }
    } else if (decodedCode == button_6) {
      snakePositionColumn += 1;
      headPositionColumn = snakeText().length() + snakePositionColumn + 1;
      if (!isRight) {
        toggleIsRight();
      }

    } else if (decodedCode == button_8) {
      snakePositionRow -= 1;
    }

    normalizeSnakePositions();
    checkCollision();
    lcd.clear();
    printToLCD(snakeText(), snakePositionRow, snakePositionColumn);
    printToLCD(target, targetPositionRow, targetPositionColumn);
    IrReceiver.resume();
  }
}

void toggleIsRight() {
  isRight = !isRight;
}


void checkCollision() {
  if (snakePositionRow == targetPositionRow && headPositionColumn == targetPositionColumn) {
    targetPositionRow = setTargetRow();
    targetPositionColumn = setTargetColumn();
    snake += "=";
  }
}

String snakeText() {
  return (isRight) ? snake + ">" : "<" + snake;
}
