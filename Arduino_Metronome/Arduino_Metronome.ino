#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int led = 13;
int ledHi = 12;// LED and Piezo
int sensorPin = A0;    // select the input pin for the potentiometer
int sensorValue = 0;
int metronomeBPM = 0;
int metronomePulse = 10;
int staticBPM = 60000;
int divisor  = 0;
int oldBPM = 0;
int beat = 1;
int timesig = 3;
void setup() {

  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(ledHi, OUTPUT);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(1000);
  display.clearDisplay();

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Arduino"); //Write custom text here
  display.println("Metronome V2.5");
  display.setTextSize(1);
  display.println("By Miles");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (digitalRead(2) == LOW) {
    timesig = 1;
    noTone(11);
    digitalWrite(ledHi, LOW);
    digitalWrite(led, LOW);
    setTimesig("1/4");

  }
  if (digitalRead(3) == LOW) {
    timesig = 2;
    noTone(11);
    digitalWrite(ledHi, LOW);
    digitalWrite(led, LOW);
    setTimesig("2/4");
  }
  if (digitalRead(4) == LOW) {
    timesig = 3;
    noTone(11);
    digitalWrite(ledHi, LOW);
    digitalWrite(led, LOW);
    setTimesig("3/4");
  }
  if (digitalRead(5) == LOW) {
    timesig = 4;
    noTone(11);
    digitalWrite(ledHi, LOW);
    digitalWrite(led, LOW);
    setTimesig("4/4");
  }


  sensorValue = analogRead(sensorPin);
  if (beat == 1 && timesig != 1) {
    //high bip
    digitalWrite(ledHi, HIGH);
    tone(11, 540);//hi
    delay(50);
    digitalWrite(ledHi, LOW);
    noTone(11);
    delay(sensorValue);      // Take potentiometer as the metronome interval (offset 10ms).
  } else {
    digitalWrite(led, HIGH);
    tone(11, 340);//lo
    delay(50);
    digitalWrite(led, LOW);
    noTone(11);
    delay(sensorValue);      // Take potentiometer as the metronome interval (offset 10ms).
  }
  beat++;

  if (timesig == 4 && beat == 5) {
    beat = 1;
  }
  if (timesig == 3 && beat == 4) {
    beat = 1;
  }
  if (timesig == 2 && beat == 3) {
    beat = 1;
  }
  if (timesig == 1 && beat == 2) {
    beat = 1;
  }

  divisor = sensorValue + metronomePulse;
  metronomeBPM = 60000 / divisor;
  if (metronomeBPM != oldBPM) {
    if (metronomeBPM == oldBPM + 1 || metronomeBPM == oldBPM - 1 || metronomeBPM == oldBPM + 2 || metronomeBPM == oldBPM - 2) {
      //dont update!
    } else {
      display.clearDisplay();
      display.display();
      //  Serial.println(metronomeBPM);

      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      // Display static text
      display.println("Arduino Metronome\n"); //Write custom text here
      display.setTextSize(2);
      display.print(metronomeBPM);
      display.print(" BPM");
      display.display();
      oldBPM = metronomeBPM;
    }
  }
}

void setTimesig(String sig) {
  display.clearDisplay();
  display.display();
  //  Serial.println(metronomeBPM);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Arduino Metronome\n"); //Write custom text here
  display.setTextSize(1);

  display.print("Time Signature: ");
  display.print(sig);
  display.display();
  delay(1000);

  display.clearDisplay();
  display.display();
  //  Serial.println(metronomeBPM);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("Arduino Metronome\n"); //Write custom text here
  display.setTextSize(2);
  display.print(metronomeBPM);
  display.print(" BPM");
  display.display();
}
