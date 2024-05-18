// Define Pins
#define aPin 2 // interrupt pin
#define bPin 3 // interrupt pin
#define E1 9 // PWM pin
#define M1 8 // direction pin

// Encoder Properties
const int CPR = 500; // counts per revolution

// State Variables
bool aState = 1;
bool bState = 1;

// Relevant Outputs
static int encoderCount = 0;
static float angle_deg = 0;

// Kinematics variables
double rh = 0.05;      // [meters] length of lever arm
double xh = 0;         // x position of handle
double lastXh = 0;     // last x position of the handle
double vh = 0;         // velocity of the handle
double lastVh = 0;     // last velocity of the handle
double lastLastVh = 0; // last last velocity of the handle
double Tm = 0;  

// Haptic variables
double k_spring = 10; // [N/m]
double force = 0;
  
double b_damper = 0.35; // [Ns/m]
double forceD = 0;

// Output data
double duty = 0;
double output = 0;

void setup() {

  // Begin serial monitors
  Serial.begin(9600);

  // Initialize motor pinss
  pinMode(E1, OUTPUT);
  pinMode(M1, OUTPUT);

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
  // Calculate shaft angle
  angle_deg = encoderCount * (360. / (CPR * 4)); 

  // Compute position of handle tip in meters
  xh = rh*angle_deg*(3.14/180);

  // compute handle velocity
  vh = -(.95*.95)*lastLastVh + 2*.95*lastVh + (1-.95)*(1-.95)*(xh-lastXh)/.0001;  // filtered velocity (2nd-order filter)
  lastXh = xh;
  lastLastVh = lastVh;
  lastVh = vh;

  // Render a virtual spring
  force = -k_spring*xh; // Resistive spring force
  
  // Render a damper
  forceD = -b_damper*vh;

  // calculate motor torque needed to produce desired resistive force 
  Tm = rh*(force - forceD);  

  // Compute the duty cycle required to generate Tp (torque at the motor pulley)
  duty = sqrt(abs(Tm)/0.03);
  
  // Make sure the duty cycle is between 0 and 100%
  if (duty > 1) {            
    duty = 1;
  } 
  else if (duty < 0) { 
    duty = 0;
  }  

  output = (int)(duty*100);   // convert duty cycle to output signal
  
  // Check direction to oppose force
  if(force < 0) { 
    digitalWrite(M1, HIGH);
    analogWrite(E1, output);
  } 
  else {
    digitalWrite(M1, LOW);
    analogWrite(E1, output);
  }
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