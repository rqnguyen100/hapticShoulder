// Wiring found here: https://psc.byu.edu/00000179-d3ea-d26e-a37b-fffaa40b0001/limit-switch-wiring

#define LIMIT_SWITCH_PIN 7

void setup() {
  // put your setup code here, to run once:
  pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(LIMIT_SWITCH_PIN) == HIGH) {
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(13, LOW);
  }

  delay(100);
}
