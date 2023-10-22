#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int textDelay = 500;

String right = "( =^_^)=";
String left = "=(^_^= )";

bool isRightSideImage = true;


void setup() {
  lcd.init();
  lcd.backlight();
}

void loop() {
  printCatEmoji(isRightSideImage);
  printNyaNya(isRightSideImage);
  delay(textDelay);
  lcd.clear();
  isRightSideImage = toggleRightSideBool(isRightSideImage);
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
