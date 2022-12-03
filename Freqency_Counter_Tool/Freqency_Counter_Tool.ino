#include <FreqCount.h>

#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);// change this according to ur display!
int FREQUENCY = 00000;
bool abrev = false;
float kHz = 0.000;
void setup() {
  lcd.init();
  lcd.backlight();
  lcd.clear();

  lcd.clear();
  lcd.print("Freq. Measuring Tool");
  lcd.setCursor(0, 3);
  lcd.print("     B3-38-2022");
  delay(2500);
  lcd.clear();

  lcd.print("FREQUENCY:");
  // initialize freqCount library with time basis of 1000ms (1 second)
  // Arduino counts number of pulses during period of 1 second
  FreqCount.begin(1000);
  pinMode(9, INPUT_PULLUP);//switch
  pinMode(10, INPUT_PULLUP);//button

}
void loop() {

  if (FreqCount.available()) {
    unsigned long count = FreqCount.read();

    lcd.setCursor(0, 0);



    lcd.print("FREQUENCY:");
    lcd.setCursor(0, 2);
    if (abrev == true) {

      kHz = count / 1000;
      lcd.print(kHz);  // print frequency value in Hz
      lcd.print(" kHz      ");
    } else {
      lcd.print(count);  // print frequency value in Hz
      lcd.print(" Hz      ");
    }

  }



  if (digitalRead(9) == LOW) {
    lcd.backlight();
  } else {
    lcd.noBacklight();
  }


  if (digitalRead(10) == LOW) {
    if (abrev == true) {
      abrev = false;
      delay(300);
    } else {
      abrev = true;
      delay(300);
    }

  }


}
