int minimum = 20;
int maximum = 40;
////
int cnt = 0;
int randBeep;
int st;
bool emrgBeep = 0;
void setup() {
  pinMode(9, OUTPUT);//Bzr
  pinMode(7, INPUT_PULLUP);//TS
  pinMode(13, OUTPUT); //onbrd led
  st = digitalRead(7);
  randBeep = random(7000, 120000);//rand delay
  for (int i = 0; i < 3; i++) {
    digitalWrite(13, LOW);
    delay(300);
    digitalWrite(13, HIGH);
    delay(300);
  }
  Serial.begin(115200);
  int ana8 = analogRead(8);
  if (ana8 > minimum && ana8 < maximum) {//key
    emrgBeep = false;
    st = digitalRead(7);
  } else {
    while(true){
      emrgBeepFunc();
    }
  }
}

void loop() {
  int dig7 = digitalRead(7);
  if (dig7 != st && emrgBeep == false) {//mvd
    emrgBeep = true;
    delay(500);
  }
  if (emrgBeep == 1) {
    emrgBeepFunc();
  } else {
    if (cnt > randBeep) {//ms delay
      randBeep = random(15000, 120000);//rand delay
      nrBeepFunc();
      cnt = 0;
    } else {
      cnt += 1;
    }
  }

  //Serial.println(analogRead(8));
  int ana8 = analogRead(8);
  if (ana8 > minimum && ana8 < maximum) {//key
    emrgBeep = false;
    st = digitalRead(7);
  }



  delay(1);
}
void emrgBeepFunc() {//alrt
  digitalWrite(9, 1);
  delay(500);
  digitalWrite(9, 0);
  delay(500);
}
void nrBeepFunc() {
  digitalWrite(9, 1);
  delay(100);
  digitalWrite(9, 0);
}
