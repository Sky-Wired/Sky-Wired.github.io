#include <Wire.h> // Library for I2C communication
#include <LiquidCrystal_I2C.h> // Library for LCDv
// Wiring: SDA pin is connected to A4 and SCL pin to A5.
// Connect to LCD via I2C, default address 0x27 (A0-A2 not jumpered)
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2); // Change to (0x27,20,4) for 20x4 LCD.


#define echoPin 12 // attach pin D2 Arduino to pin Echo of HC-SR04
#define trigPin 8 //attach pin D3 Arduino to pin Trig of HC-SR04

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement

int b = 0;

float timeGone;
int lightButton = 4;
int resetButton = 7;
int timeGoneMins = 0;
int rotations = 0;
int x = 0;
int z = 0;
float input_volt = 0.0;


int timeMin = 59995;
int timeMax = 60005;
int lights = 13;
int lightsDelay = 0;
int leftBrake = 0;
int rightBrake = 0;
int IRstatus;
int reset;
int lightBtn;
bool y = false;
float distanceFeet = 0.0000;
float distanceMiles = 0.000000000000000000000000000000;

float oneRevolution = 6.8067783333;
//int batteryPin = A0;






int value = 0;

float R1 = 39000.0;
float R2 = 27000.0;











void setup() {
  Serial.begin(9600);
  //pinMode(A0, INPUT);
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  pinMode(2, INPUT_PULLUP); //LEFT BRAKE HANDLE
  pinMode(9, INPUT_PULLUP); //RIGHT BRAKE HANDLE
  pinMode(lightButton, INPUT_PULLUP);
  pinMode(resetButton, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  delay(300);
  digitalWrite(13, LOW);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("  Bikeometer  ");
  lcd.setCursor(0, 1);
  lcd.print("  Version 1.9  ");

  timeGoneMins = round(timeGone / 60000);
}

void loop() {






  if (digitalRead(9) == HIGH && digitalRead(2) == HIGH) {
    rightBrake++;
    leftBrake++;
    Serial.println(rightBrake);
    Serial.println(leftBrake);
    while (digitalRead(9) == HIGH && digitalRead(2) == HIGH) {
      delay(1);
      //Serial.println("BOTH!");
      check();

    }
  }
  if (digitalRead(9) == HIGH) {
    rightBrake++;
    updateSensor();
    Serial.println(rightBrake);
    while (digitalRead(9) == HIGH) {
      Serial.println("Front!");
      delay(1);
      updateSensor();
      check();

    }
  }

  if (digitalRead(2) == HIGH) {
    leftBrake++;
    updateSensor();
    Serial.println(leftBrake);
    while (digitalRead(2) == HIGH) {
      delay(1);
      Serial.println("Rear!");
      updateSensor();
      check();

    }
  }

  delay(1);
  check();

}

void check() {
  timeGone = millis();
  updateSensor();



  reset = digitalRead(resetButton);
  lightBtn = digitalRead(lightButton);
  updateSensor();
  // Serial.println(digitalRead(lights));
  if (lightBtn == LOW && y == false) {
    y = true;
    lcd.clear();
    updateSensor();
    lcd.print("Lights: ON");
    digitalWrite(lights, HIGH);
    updateSensor();
    delay(700);
    updateSensor();


  } else if (lightBtn == LOW && y == true) {
    y = false;
    lcd.clear();
    updateSensor();
    lcd.print("Lights: OFF");
    updateSensor();
    digitalWrite(lights, LOW);
    updateSensor();
    delay(700);
    updateSensor();

  }
  if (y == true) {
    if (lightsDelay == 9 || lightsDelay == 10 || lightsDelay == 11) {

      digitalWrite(lights, HIGH);
      updateSensor();


    }
    if (lightsDelay > 19) {
      digitalWrite(lights, LOW);
      updateSensor();
      lightsDelay = 0;
    }
    lightsDelay++;
  }




  if (reset == LOW) {
    updateSensor();
    rotations = 0;
    x = 0;
    distanceMiles = 0.0;
    updateSensor();
    distanceFeet = 0;
    timeGone = 0;
    timeGoneMins = 0;
    rightBrake = 0;
    updateSensor();
    leftBrake = 0;
    lcd.clear();
    lcd.print("Counters Reset");

  }
  if (z >= 19) {
    if (distance < 4) {//detected
      rotations++;
     distanceFeet = distanceFeet + oneRevolution;
      z = 0;
    }
  } else {
    z++;
  }
   updateSensor();
   distanceMiles = distanceFeet / 5280.0;
   
      
     

  if (x == 300 || x == 301) {//UPDATE DISPLAY
    updateSensor();
   
    lcd.clear();
   updateSensor();
    //lcd.setCursor(0, 0);
    lcd.print("Cycles: ");
    updateSensor();
    //Serial.println(distance);
    lcd.print(rotations);
    updateSensor();
    lcd.setCursor(0, 1);
    updateSensor();
    lcd.print("Time: ");

    timeGoneMins = timeGone / 60000;


    lcd.print(timeGoneMins);


    updateSensor();

    lcd.print(" mins");
    batteryUpdate();
    updateSensor();
  }


  if (x == 599 || x == 600) {
    // Clears the trigPin condition
    updateSensor();
    lcd.clear();
    updateSensor();
    //lcd.setCursor(0, 0);
    lcd.print("Dist: ");
    updateSensor();
    lcd.print(distanceFeet,1);

    updateSensor();
    lcd.print(" ft");
    updateSensor();

    lcd.setCursor(0, 1);
    updateSensor();
    lcd.print("Dist: ");
    updateSensor();
    lcd.print(distanceMiles,4);
    updateSensor();
    lcd.print(" mi");
    batteryUpdate();

  }


  if (x > 899) {
    updateSensor();
    lcd.clear();
    updateSensor();
    lcd.print("Brake Usage:");
    updateSensor();
    lcd.setCursor(0, 1);
    updateSensor();
    lcd.print("F: ");
    updateSensor();
    lcd.print(leftBrake);
    updateSensor();
    lcd.print("   R: ");
    updateSensor();
    lcd.print(rightBrake);
    updateSensor();
    batteryUpdate();
    updateSensor();
    x = 0;
    updateSensor();
  }
  x++;


  if (b == 50  || b == 51) {
    lowBattery();
    updateSensor();
  }
  if (b == 100 || b == 101) {
    lowBattery1();
    b = 0;
    updateSensor();
  }
  b++;
}


void batteryUpdate() {
  updateSensor();
  value = analogRead(A0);
  input_volt = value * (5.0 / 1024) * ((R1 + R2) / R2);

  // input_volt = input_volt * 2 - 0.41;
  if (input_volt < 0.1)
  {
    input_volt = 0.0;
  }

  if (input_volt > 6.10 && input_volt < 6.31) {
    byte Batt[] = {//1 bar
      B01110,
      B11111,
      B10001,
      B10001,
      B10001,
      B10001,
      B11111,
      B11111
    };
    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);
  }
  if (input_volt > 6.31 && input_volt < 6.71) {
    byte Batt[] = {// 2 bar
      B01110,
      B11111,
      B10001,
      B10001,
      B10001,
      B11111,
      B11111,
      B11111
    };
    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);
  }
  if (input_volt > 6.71 && input_volt < 7.20) {
    byte Batt[] = { //3 bars
      B01110,
      B11111,
      B10001,
      B10001,
      B11111,
      B11111,
      B11111,
      B11111
    };
    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);
  }
  if (input_volt > 7.20 && input_volt < 7.60) {
    byte Batt[] = {
      B01110,
      B11111,
      B10001,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111
    };
    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);
  }
  if (input_volt > 7.60) {
    byte Batt[] = {
      B01110,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111,
      B11111
    };
    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);
    //5 bars (full)
  }
}
void lowBattery() {
  value = analogRead(A0);
  input_volt = value * (5.0 / 1024) * ((R1 + R2) / R2);

  // input_volt = input_volt * 2 - 0.41;
  if (input_volt < 0.1)
  {
    input_volt = 0.0;
  }



  if (input_volt < 6.10) {

    byte Batt[] = {//0 bars
      B01110,
      B11111,
      B10001,
      B10101,
      B10101,
      B10001,
      B10101,
      B11111
    };

    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);



    //print LOW BATTERY (0 bars) EXCLAMATION POINT ADDED!


  }

}


void lowBattery1() {
  value = analogRead(A0);
  input_volt = value * (5.0 / 1024) * ((R1 + R2) / R2);

  // input_volt = input_volt * 2 - 0.41;
  if (input_volt < 0.1)
  {
    input_volt = 0.0;
  }
  if (input_volt < 6.10) {

    byte Batt[] = {//0 bars
      B01110,
      B11111,
      B10001,
      B10001,
      B10001,
      B10001,
      B10001,
      B11111
    };
    lcd.createChar(0, Batt);
    lcd.home();
    lcd.setCursor(15, 0); // top right
    lcd.write(0);


  }
}

void updateSensor() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  //Serial.println(distance);
}
