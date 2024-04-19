int E1 = 3;
int M1 = 4;

void setup() {
  Serial.begin(9600);
  
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);
}

void loop() {

  // ramp up forward
  digitalWrite(M1, LOW);
  for (int i=0; i<50; i++) {
    analogWrite(E1, i);
    delay(10);
  }

  // forward full speed for one second
  delay(1000);
  
  // ramp down forward
  for (int i=50; i>=0; i--) {
    analogWrite(E1, i);
    delay(10);
  }

  // ramp up backward
  digitalWrite(M1, HIGH);
  for (int i=0; i<50; i++) {
    analogWrite(E1, i);
    delay(10);
  }

  // backward full speed for one second
  delay(1000);

  // ramp down backward
  for (int i=50; i>=0; i--) {
    analogWrite(E1, i);
    delay(10);
  }
}