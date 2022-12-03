#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
int S1 = A0;
int S2 = A1;
int S1_stat;
int S2_stat;
int threshold = 110;
int currentPos = 83; //Default servo position

Servo servo;  // create servo object to control a servo
int pos;
int x = 0;

void setup() {
  lcd.init();
  // Print a message to the LCD.
  lcd.clear();
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  lcd.print("Servo Pos: 83");
  lcd.setCursor(0, 1); 
  lcd.print("Waiting");
   Serial.begin(9600);
   Serial.println("Waiting..");
  int y=0;
  while(y<11) {
    y++;
    delay(1000);
    lcd.print(".");
    
  }
  servo.attach(9);  // attaches the servo on pin 9 to the servo object
  servo.write(currentPos);
  Serial.begin(9600);
  

  // initialize the lcd



}

void loop() {
  S1_stat = analogRead(S1);
  S2_stat = analogRead(S2);





  if (S1_stat > threshold && S2_stat > threshold) {
    //Don't move
    Serial.println("Stop moving");
  } else if (S1_stat > S2_stat) {
    while (S1_stat > S2_stat) {

      S1_stat = analogRead(S1);
      S2_stat = analogRead(S2);
      lcd.clear();
      lcd.print("Sensor 1: ");
      lcd.print(S1_stat);
      lcd.setCursor(0, 1);
      lcd.print("Sensor 2: ");
      lcd.print(S2_stat);

      if (currentPos < 54) {
        //Stopping at limit
        Serial.println("S1 limit reached!");
        currentPos = 54;
      } else {
        currentPos--;
        servo.write(currentPos);
        Serial.print("Rotating towards S1... Pos= ");
        Serial.println(currentPos);

        delay(300);
      }
    }
    Serial.println("--------DONE!---------");




  } else if (S2_stat > S1_stat) {
    while (S2_stat > S1_stat) {

      S1_stat = analogRead(S1);
      S2_stat = analogRead(S2);
      lcd.clear();
      lcd.print("Sensor 1: ");
      lcd.print(S1_stat);
      lcd.setCursor(0, 1);
      lcd.print("Sensor 2: ");
      lcd.print(S2_stat);
      if (currentPos > 112) {
        //Stopping at limit
        Serial.println("S1 limit reached!");
        currentPos = 112;
      } else {
        currentPos++;
        servo.write(currentPos);
        Serial.print("Rotating towards S1... Pos= ");
        Serial.println(currentPos);

        delay(300);
      }
    }
    Serial.println("--------DONE!---------");
  }


  updateDisp();

}

void updateDisp() {
  while (x < 120) {
    Serial.println();
    int S1_stat = analogRead(S1);
    int S2_stat = analogRead(S2);
    lcd.clear();
    lcd.print("Sensor 1: ");
    lcd.print(S1_stat);
    lcd.setCursor(0, 1);
    lcd.print("Sensor 2: ");
    lcd.print(S2_stat);

    Serial.print("Sensor 1: ");
    Serial.println(S1_stat);
    Serial.println();
    Serial.print("Sensor 2: ");
    Serial.println(S2_stat);
    x++;
    delay(1000);

  }
  x = 0;
}
