#pragma once

#ifndef FUNCTION_H
#define FUNCTION_H

#include "config.h"
#include <LiquidCrystal_I2C.h>

#define LCD_ADDRESS 0x27
#define LCD_COL 16
#define LCD_ROW 2

// extern
LiquidCrystal_I2C lcd(LCD_ADDRESS, LCD_COL, LCD_ROW);
class Display {
public:
  bool init() {
    lcd.init();
    lcd.backlight();
    return 0;
  }
  void bitMap(void) {
    lcd.setCursor(0, 0);
    lcd.print("Real:");

    lcd.setCursor(9, 0);
    lcd.print("Tim:");

    lcd.setCursor(0, 1);
    lcd.print("Set:");
  }
  // sendIP(WiFi.localIP())
  void printIP(int IP) {
    lcd.setCursor(7, 0);
    lcd.print("IP");
    lcd.setCursor(1, 1);
    lcd.print(IP);
    delay(5000);
    lcd.clear();
  }
  void printTemp(int temp) {
    lcd.setCursor(6, 0);
    lcd.print(temp);
  }
};


//design image on display
#endif  // FUNCTION_Hs