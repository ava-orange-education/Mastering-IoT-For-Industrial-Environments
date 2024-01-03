#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Set the LCD address (usually 0x27 or 0x3F)
LiquidCrystal_I2C lcd(0x27, 16, 2); // Change to your display's address and size

void setup() {
  // Initialize the LCD
  lcd.init();
  // Turn on the backlight (if available)
  lcd.backlight();

  // Print "Hello, World!" on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Hello, World!");
}

void loop() {
  // Your main code can go here
}
