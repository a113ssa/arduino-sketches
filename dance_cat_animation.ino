#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int column = 0;
int textDelay = 500;
int increaseStep = 3;

String right = "( =^_^)=";
String left = "=(^_^= )";

bool isRightSideImage = true;


void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  column = normalizeColumn(column);
  printCatEmoji(isRightSideImage);
  printNyaNya(isRightSideImage);
  delay(textDelay);
  lcd.clear();
  column += increaseStep;
  isRightSideImage = toggleRightSideBool(isRightSideImage);
}

int normalizeColumn(int column) {
  if (column > 16) {
    return 0;
  } else {
    return column;
  }
}

void printCatEmoji(bool isRightSideImage) {
  lcd.setCursor(3, 0);
  String printText = (isRightSideImage) ? right : left;
  lcd.print(printText);
}

void printNyaNya(bool isRightSideImage) {
  int column = (isRightSideImage) ? 0 : 9;
  lcd.setCursor(column, 1);
  lcd.print("Nya Nya");
}

bool toggleRightSideBool(bool isRightSideImage) {
  return !isRightSideImage;
}
