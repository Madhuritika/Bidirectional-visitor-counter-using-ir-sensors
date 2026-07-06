#include <LiquidCrystal.h>

// LCD pins: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(8, 9, 2, 3, 4, 5);

int sensor1 = 7;
int sensor2 = 6;

int count = 0;
int state = 0;

void setup() {
  pinMode(sensor1, INPUT_PULLUP);
  pinMode(sensor2, INPUT_PULLUP);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Visitor Counter");
  delay(1500);
  lcd.clear();
}

void loop() {
  int s1 = digitalRead(sensor1);
  int s2 = digitalRead(sensor2);

  switch (state) {

    case 0: // idle
      if (s1 == LOW) state = 1;
      else if (s2 == LOW) state = 2;
      break;

    case 1: // possible entry
      if (s2 == LOW) {
        count++;
        updateLCD("Entered");
        delay(500);
        state = 0;
      }
      break;

    case 2: // possible exit
      if (s1 == LOW) {
        count--;
        if (count < 0) count = 0;
        updateLCD("Exited");
        delay(500);
        state = 0;
      }
      break;
  }
}

void updateLCD(String msg) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
  lcd.setCursor(0, 1);
  lcd.print("Count: ");
  lcd.print(count);
}