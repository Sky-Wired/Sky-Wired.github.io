//Define Variables
int ServoL1 = 6;
int ServoL2 = 7;
int ServoLEn = 8;

int ServoR1 = 4;
int ServoR2 = 5;
int ServoREn = 3;

int trigPin = 10;
int echoPin = 11;
// defines variables
long duration; // variable for the duration of sound wave travel
int distance = 105; // variable for the distance measurement

int tableSnsrR = A5;
int tableSnsrL = A3;


void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(trigPin, OUTPUT);
  // configure the echo pin to input mode
  pinMode(echoPin, INPUT);
  pinMode(ServoLEn, OUTPUT);
  pinMode(ServoREn, OUTPUT);

  pinMode(ServoL1, OUTPUT);
  pinMode(ServoL2, OUTPUT);

  pinMode(ServoR1, OUTPUT);
  pinMode(ServoR2, OUTPUT);

  analogWrite(ServoLEn, 255);
  analogWrite(ServoREn, 255);

  pinMode(tableSnsrR, INPUT);
   pinMode(tableSnsrL, INPUT);

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
  Serial.println(distance);
  delay(1000);


}

void loop() {
  

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
  Serial.println(distance);
  if (digitalRead(tableSnsrR) == HIGH || digitalRead(tableSnsrL) == HIGH) {
    stopAll();

    delay(300);
    backward();
    delay(300);
    stopAll();
    delay(300);
    int numA = random(1, 3);
    if (numA == 1) {

      left();
      delay(600);
      stopAll();

    } else if (numA == 2) {

      right();
      delay(600);
      stopAll();

    }
    delay(300);
    
  } else if (distance < 9) {//Turn left or right

    stopAll();
    delay(300);
    int num = random(1, 3);
    if (num == 1) {

      while (distance < 9) {
        left();
        delay(600);
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
        Serial.println(distance);
      }
      stopAll();
      delay(300);

    } else if (num == 2) {

      while (distance < 9) {
        right();
        delay(600);
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
        Serial.println(distance);
      }
      stopAll();
      delay(300);

    }
  } else {

    forward();

  }
}





void left() {
  digitalWrite(ServoL2, HIGH);
  digitalWrite(ServoL1, LOW);

  digitalWrite(ServoR2, LOW);
  digitalWrite(ServoR1, HIGH);
}
void right() {
  digitalWrite(ServoL2, LOW);
  digitalWrite(ServoL1, HIGH);

  digitalWrite(ServoR2, HIGH);
  digitalWrite(ServoR1, LOW);
}
void forward() {
  digitalWrite(ServoL2, HIGH);
  digitalWrite(ServoL1, LOW);

  digitalWrite(ServoR2, HIGH);
  digitalWrite(ServoR1, LOW);
}
void backward() {
  digitalWrite(ServoL2, LOW);
  digitalWrite(ServoL1, HIGH);

  digitalWrite(ServoR2, LOW);
  digitalWrite(ServoR1, HIGH);
}
void stopAll() {
  digitalWrite(ServoL1, LOW);
  digitalWrite(ServoL2, LOW);
  digitalWrite(ServoR1, LOW);
  digitalWrite(ServoR2, LOW);
}
