// Basic sketch for trying out the Adafruit DRV8871 Breakout

#define MOTOR_IN1 5
#define MOTOR_IN2 6

void setup() {
  Serial.begin(9600);
  
  pinMode(MOTOR_IN1, OUTPUT);
  pinMode(MOTOR_IN2, OUTPUT);
}

void loop() {

  Serial.println("DRV8871 test");

  // ramp up forward
  digitalWrite(MOTOR_IN1, LOW);
  for (int i=0; i<50; i++) {
    analogWrite(MOTOR_IN2, i);
    delay(10);
  }

  // forward full speed for one second
  delay(1000);
  
  // ramp down forward
  for (int i=50; i>=0; i--) {
    analogWrite(MOTOR_IN2, i);
    delay(10);
  }

  // ramp up backward
  digitalWrite(MOTOR_IN2, LOW);
  for (int i=0; i<50; i++) {
    analogWrite(MOTOR_IN1, i);
    delay(10);
  }

  // backward full speed for one second
  delay(1000);

  // ramp down backward
  for (int i=50; i>=0; i--) {
    analogWrite(MOTOR_IN1, i);
    delay(10);
  }
}