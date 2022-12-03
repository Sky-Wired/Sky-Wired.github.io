/* I2C LCD with Arduino example code. More info: https://www.makerguides.com */

// Include the libraries:
// LiquidCrystal_I2C.h: https://github.com/johnrickman/LiquidCrystal_I2C
#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCD
// Make custom characters:
byte Heart[] = {
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte Bell[] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B00000,
  B00100,
  B00000
};

byte Alien[] = {
  B11111,
  B10101,
  B11111,
  B10001,
  B11111,
  B01010,
  B01010,
  B11011
};

byte Check[] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

byte Speaker[] = {
  B00001,
  B00011,
  B01111,
  B01111,
  B01111,
  B00011,
  B00001,
  B00000
};

byte Sound[] = {
  B00001,
  B00011,
  B00101,
  B01001,
  B01001,
  B01011,
  B11011,
  B11000
};

byte Skull[] = {
  B00000,
  B01110,
  B10101,
  B11011,
  B01110,
  B01110,
  B00000,
  B00000
};

byte Lock[] = {
  B01110,
  B10001,
  B10001,
  B11111,
  B11011,
  B11011,
  B11111,
  B00000
};

// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.

void setup() {
  // Initiate the LCD:
  lcd.init();
  lcd.backlight();


  // Create new characters:
  lcd.createChar(0, Heart);
  lcd.createChar(1, Bell);
  lcd.createChar(2, Alien);
  lcd.createChar(3, Check);
  lcd.createChar(4, Speaker);
  lcd.createChar(5, Sound);
  lcd.createChar(6, Skull);
  lcd.createChar(7, Lock);

  // Clear the LCD screen:
  lcd.clear();

  // Print a message to the lcd:


}

void loop() {
  // Print 'Hello World!' on the first line of the LCD:
  lcd.setCursor(2, 0); // Set the cursor on the third column and first row.
  lcd.print("Hello World!"); // Print the string "Hello World!"
  delay(1000);
  lcd.setCursor(2, 1); //Set the cursor on the third column and the second row (counting starts at 0!).
  lcd.print("LCD tutorial");
  delay(3000);
  lcd.clear();
  lcd.print("Custom Character");
  delay(500);
  lcd.setCursor(0, 1);
  lcd.write(0);
  delay(300);
  lcd.setCursor(2, 1);
  lcd.write(1);
  delay(300);
  lcd.setCursor(4, 1);
  lcd.write(2);
  delay(300);
  lcd.setCursor(6, 1);
  lcd.write(3);
  delay(300);
  lcd.setCursor(8, 1);
  lcd.write(4);
  delay(300);
  lcd.setCursor(10, 1);
  lcd.write(5);
  delay(300);
  lcd.setCursor(12, 1);
  lcd.write(6);
  delay(300);
  lcd.setCursor(14, 1);
  lcd.write(7);
  delay(3000);
  lcd.clear();
  delay(1000);
}
