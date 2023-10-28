#include <IRremote.hpp>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

uint8_t irPin = 53;
const String button_2 = "e718ff00";
const String button_4 = "f708ff00";
const String button_6 = "a55aff00";
const String button_8 = "ad52ff00";

String tale = "O";
String snake = "";
String head = ">";
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
boolean isRowChanged = false;

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
    if (decodedCode == button_2 && snakePositionRow == 1) {
      snakePositionRow += 1;
      isRight = NULL;
      isRowChanged = true;

    } else if (decodedCode == button_4 && (!isRight || isRight == NULL)) {
      if (!isRowChanged) { snakePositionColumn -= 1; }

      headPositionColumn = snakePositionColumn;
      isRight = false;
      isRowChanged = false;

    } else if (decodedCode == button_6 && (isRight || isRight == NULL)) {
      if (!isRowChanged) {
        snakePositionColumn += 1;
        headPositionColumn = String(tale + head).length() + snakePositionColumn - 1;
      } else {
        headPositionColumn = String(tale).length() + snakePositionColumn - 1;
      }

      isRight = true;
      isRowChanged = false;

    } else if (decodedCode == button_8 && snakePositionRow == 0) {
      if (isRight) { headPositionColumn = String(tale).length() + snakePositionColumn - 1; }
      snakePositionRow -= 1;
      isRight = NULL;
      isRowChanged = true;
    }

    normalizeSnakePositions();
    checkCollision();
    lcd.clear();
    printSnake();
    printToLCD(target, targetPositionRow, targetPositionColumn);
    IrReceiver.resume();
  }
}

void checkCollision() {
  if (snakePositionRow == targetPositionRow && headPositionColumn == targetPositionColumn) {
    targetPositionRow = setTargetRow();
    targetPositionColumn = setTargetColumn();
    tale += "O";
    score += 1;
  }
}

void printSnake() {
  if (isRowChanged) {
    printToLCD(setSnakeHead(), snakePositionRow, headPositionColumn);
    uint8_t taleRow = snakePositionRow == 0 ? 1 : 0;
    printToLCD(tale, taleRow, snakePositionColumn);
  } else {
    printToLCD(snakeText(), snakePositionRow, snakePositionColumn);
  }
}

String setSnakeHead() {
  if (isRowChanged) {
    if (snakePositionRow == 0) { return "^"; }
    if (snakePositionRow == 1) { return "v"; }
  }

  if (!isRowChanged) {
    if (isRight) { return ">"; }
    if (!isRight) { return "<"; }
  }
}


String snakeText() {
  head = setSnakeHead();
  return (isRight == true) ? tale + head : head + tale;
}
