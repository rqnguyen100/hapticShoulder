// Define Pins
#define aPin 2 // interrupt pin
#define bPin 3 // interrupt pin

// Encoder Properties
const int CPR = 500; // counts per revolution
const int freq = 100; // hertz

// State Variables
bool aState = 1;
bool bState = 1;

// Relevant Outputs
static int encoderCount = 0;
static float position = 0;

//MOTOR1 PINS
int ena = 5;
int in1 = 6;
int in2 = 7;

void setup() {

  // Begin serial monitors
  Serial.begin(9600);

  pinMode(ena, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);

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
    in1 HIGH & in2 LOW = CW
    in1 LOW & in2 HIGH = CCW
    in1 LOW & in2 LOW = OFF

    analogWrite PWM = [0, 255]
  */

  // Prepare motor
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);

  // Position Control CW
  while (position < 90){
    
    // Move motor CW from vertical to right at 90 (unopposed by gravity so lower speed?)
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(ena, 50);

    // Calculate shaft position
    position = encoderCount * (360. / (CPR * 4)); 
  }

  // Pause
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  delay(2000);

  // Position Control CCW
  while (position > -90){
    
    // Move motor CCW from 90 to vertical at 0 (opposed by gravity so higher speed?)
    digitalWrite(in1,LOW);
    digitalWrite(in2,HIGH);
    analogWrite(ena, 50);

    // Calculate shaft position
    position = encoderCount * (360. / (CPR * 4));
  }
  
  // Pause
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
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