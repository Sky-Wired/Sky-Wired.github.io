#include <LowPower.h>
int motor = 9;
int sensor = 2;
int sensorPwr = 5;
void setup() {
  pinMode(motor, OUTPUT);
  pinMode(sensorPwr, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(sensor, INPUT);

  digitalWrite(motor, LOW);
}
void loop() {
  for (int i = 0; i <= 2; i++)
  {
    //LowPower.idle(SLEEP_500MS, ADC_OFF, TIMER2_OFF, TIMER1_OFF, TIMER0_OFF, SPI_OFF, USART0_OFF, TWI_OFF);
     LowPower.powerDown(SLEEP_500MS, ADC_OFF, BOD_OFF);  
  }

  digitalWrite(sensorPwr, HIGH);
  delay(8);
  if (digitalRead(sensor) == LOW) { //something detected
    digitalWrite(13, HIGH);
    digitalWrite(motor, HIGH);
    delay(500);
    digitalWrite(13, LOW);
    digitalWrite(motor, LOW);
    while (digitalRead(sensor) == LOW); //do nothing
  }
  digitalWrite(13, LOW);
  digitalWrite(motor, LOW);
  digitalWrite(sensorPwr, LOW);
}
