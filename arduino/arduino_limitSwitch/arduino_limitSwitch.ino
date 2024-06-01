// Wiring found here: https://psc.byu.edu/00000179-d3ea-d26e-a37b-fffaa40b0001/limit-switch-wiring

#define lsPin 7
bool lsState;

double upperLim = 0;
bool upperSet = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(lsPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (upperSet){
    lsState = digitalRead(lsPin);

    if (lsState) {
      upperLim = 90;
      upperSet = 0;
      Serial.println("Calibrated");
    }
    else{
      Serial.println("Calibrating...");
    }

    delay(100);
  }

  Serial.println("Ready to Go");
  delay(100);
}
