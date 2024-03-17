// Define Pins
#define aPin 2 // interrupt pin
#define bPin 3 // interrupt pin
#define m1Pin 10
#define m2Pin 11

// Encoder Properties
const int CPR = 500; // counts per revolution
const int freq = 100; // hertz

// State Variables
bool aState = 1;
bool bState = 1;

// Relevant Outputs
static int encoderCount = 0;
static float position = 0;

void setup() {
  // Begin serial monitors
  Serial.begin(9600);

  // Initialize motor pins
  pinMode(m1Pin, OUTPUT);
  pinMode(m2Pin, OUTPUT);

  // Initialize encoder pins
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  
  /*
    aPin Rising = 1x Resolution
    aPin Change = 2x Resolution
    aPin and bPin Change = 4x Resolution
  */
  attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulse, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulse, CHANGE);
}

void loop() {
  /* MOTOR INPUTS
    M1 HIGH & M2 LOW = CCW
    M1 LOW & M2 HIGH = CW
    M1 LOW & M2 Low = Brake *(coasted at 9V)
    M1 HIGH & M2 HIGH = Coast *(coasted at 9V)

    analogWrite PWM = [0, 255]
  */

  // Calculate shaft position
  position = encoderCount * (360. / (CPR * 4));

  // Position Control
  while (position < 90){
    // Move motor CCW
    digitalWrite(m2Pin, LOW);
    analogWrite(m1Pin, 20);

    // Calculate shaft position
    position = encoderCount * (360. / (CPR * 4));
    Serial.println(position);
  }

  delay(2000);

  while (position > -90){
    // Move motor CW
    digitalWrite(m1Pin, LOW);
    analogWrite(m2Pin, 10);

    // Calculate shaft position
    position = encoderCount * (360. / (CPR * 4));
    Serial.println(position);
  }

  delay(2000);
}

void encoderAPulse() {
  // Read channels
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);

  // Determine direction based on A and B state
  if (aState){
    if (bState){
      encoderCount--;
    }
    else {
      encoderCount++;
    }
  }
  else {
    if (bState){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
}

void encoderBPulse() {
  // Read channels
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);

  // Determine direction based on A and B state
  if (bState){
    if (aState){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
  else {
    if (aState){
      encoderCount--;
    }
    else {
      encoderCount++;
    }
  }
}