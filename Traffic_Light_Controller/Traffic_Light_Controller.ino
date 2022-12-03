int YL = 3;
int GL = 4;
int RL = 2;
bool allon = false;
int mode = 0; //1-5
void setup() {

  //Buttons:
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);

  //relays(lights)
  pinMode(GL, OUTPUT);
  pinMode(YL, OUTPUT);
  pinMode(RL, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(A0) == LOW) {
    if (allon == false) {
      allon = true;
      mode = 0;
      all_on();
    } else {
      allon = false;
      mode = 0;
      all_off();
    }
    delay(300);
  }

  if (digitalRead(A1) == LOW) { //Normal Mode (cycle normally)
    mode = 1;
  }
  if (digitalRead(A2) == LOW) { //Flash RED
    mode = 2;
  }
  if (digitalRead(A3) == LOW) { //Flash DOWN
    mode = 3;
  }
  if (digitalRead(A4) == LOW) { //random
    mode = 4;
  }
  if (digitalRead(A5) == LOW) { //
    mode = 5;
  }



  if (mode == 1) {//cycle mode
    digitalWrite(GL , HIGH);
    delay(5500);
    digitalWrite(GL , LOW);
    digitalWrite(YL , HIGH);
    delay(2500);
    digitalWrite(YL , LOW);
    digitalWrite(RL , HIGH);
    delay(6500);
    digitalWrite(RL , LOW);
  }
  if (mode == 2) {//Flash RED
    digitalWrite(RL , HIGH);
    delay(500);
    digitalWrite(RL , LOW);
    delay(500);
  }
  if (mode == 3) {//Flash DOWN
    digitalWrite(RL , HIGH);
    delay(100);
    digitalWrite(RL , LOW);
    digitalWrite(YL , HIGH);
    delay(100);
    digitalWrite(YL , LOW);
    digitalWrite(GL , HIGH);
    delay(100);
    digitalWrite(GL , LOW);
  }
  if (mode == 4) {//random
    int delayTime = random(500, 3000);
    int colorMode = random(1, 4);
    if (colorMode == 1) {
      digitalWrite(RL , HIGH);
      delay(delayTime);
      int delayTime = random(500, 3000);
      digitalWrite(RL , LOW);
      delay(delayTime);
    }
    if (colorMode == 2) {
      digitalWrite(YL , HIGH);
      delay(delayTime);
      int delayTime = random(500, 3000);
      digitalWrite(YL , LOW);
      delay(delayTime);
    }
    if (colorMode == 3) {
      digitalWrite(GL , HIGH);
      delay(delayTime);
      int delayTime = random(500, 3000);
      digitalWrite(GL , LOW);
      delay(delayTime);
    }
  }
  if (mode == 5) {

    digitalWrite(RL , HIGH);
    digitalWrite(YL , HIGH);
    digitalWrite(GL , HIGH);
    delay(500);
    digitalWrite(RL , LOW);
    digitalWrite(GL , LOW);
    digitalWrite(YL , LOW);
    delay(500);

  }
}









void all_on(void) {
  digitalWrite(GL, HIGH);
  digitalWrite(YL, HIGH);
  digitalWrite(RL, HIGH);
}

void all_off(void) {
  digitalWrite(GL, LOW);
  digitalWrite(YL, LOW);
  digitalWrite(RL, LOW);
}
