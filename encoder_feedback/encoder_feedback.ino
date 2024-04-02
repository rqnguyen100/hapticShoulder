// Define Pins
#define aPin 2 // interrupt pin
#define bPin 3 // interrupt pin
#define invAPin 4
#define invBPin 5

// Encoder Properties
const int CPR = 500; // counts per revolution
const int freq = 100; // hertz

// State Variables
bool aState = 1;
bool bState = 1;
bool invAState = 1;
bool invBState = 1;

// Relevant Outputs
static int encoderCount = 0;
static float position = 0;

void setup() {
  // Begin serial monitors
  Serial.begin(9600);

  // Initialize pin mode
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(invAPin, INPUT);
  pinMode(invBPin, INPUT);
  
  /*
    aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
    aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
    aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
  */
  attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulse, CHANGE);
  attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulse, CHANGE);
}

void loop() {
  // Calculate shaft position
  position = encoderCount * (360. / (CPR * 4));
  Serial.println(position);
  delay(freq);
}

void encoderAPulse() {
  // Read channels
  aState = digitalRead(aPin);
  bState = digitalRead(bPin);
  invAState = digitalRead(invAPin);
  invBState = digitalRead(invBPin);

  // Reconstruct signal to reduce noise
  bool reconstructedA = aState && !invAState;
  bool reconstructedB = bState && !invBState;

  // Determine direction based on A and B state
  if (reconstructedA){
    if (reconstructedB){
      encoderCount--;
    }
    else {
      encoderCount++;
    }
  }
  else {
    if (reconstructedB){
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
  invAState = digitalRead(invAPin);
  invBState = digitalRead(invBPin);

  // Reconstruct signal to reduce noise
  bool reconstructedA = aState && !invAState;
  bool reconstructedB = bState && !invBState;

  // Determine direction based on A and B state
  if (reconstructedB){
    if (reconstructedA){
      encoderCount++;
    }
    else {
      encoderCount--;
    }
  }
  else {
    if (reconstructedA){
      encoderCount--;
    }
    else {
      encoderCount++;
    }
  }
}
