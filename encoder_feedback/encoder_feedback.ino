const int aPin = 2; // interrupt pin
const int bPin = 3; // interrupt pin
const int aiPin = 4;
const int CPR = 500;

volatile long encoderCount = 0;
volatile float position = 0;

bool bState = 1;
bool aiState = 1;

void setup() {
  // Begin serial monitors
  Serial.begin(9600);

  // Initialize pin mode
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(aiState, INPUT);

  // Initialize interrupt pins
  attachInterrupt(digitalPinToInterrupt(aPin), encoderPulse, RISING);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void encoderPulse() {
  // Read AI and B state
  aiState = digitalRead(aiPin);
  bState = digitalRead(bPin);

  // Determine direction based on B state
  if (aiState == false){
    if (bState == false){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
  else {
    if (bState == true){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
  // Calculate shaft position
  position = encoderCount * (360. / CPR);
  Serial.println(position);
}
