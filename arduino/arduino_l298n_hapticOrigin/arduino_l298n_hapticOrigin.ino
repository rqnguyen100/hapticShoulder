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
static float angle_deg = 0;

//MOTOR1 PINS
int ena = 5;
int in1 = 6;
int in2 = 7;

// Kinematics variables
double lastXh = 0;     //last x position of the handle
double vh = 0;         //velocity of the handle
double lastVh = 0;     //last velocity of the handle
double lastLastVh = 0; //last last velocity of the handle

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
    
  // Calculate shaft angle
  angle_deg = encoderCount * (360. / (CPR * 4)); 

  // Compute position of handle tip in meters
  double rh = 0.05; // [meters] length of lever arm
  double xh = rh*angle_deg*(3.14/180);

  // compute handle velocity
  vh = -(.95*.95)*lastLastVh + 2*.95*lastVh + (1-.95)*(1-.95)*(xh-lastXh)/.0001;  // filtered velocity (2nd-order filter)
  lastXh = xh;
  lastLastVh = lastVh;
  lastVh = vh;

  // Render a virtual spring
  double k_spring = 10; // [N/m]
  double force = -k_spring*xh; // Resistive spring force
  
  // Render a damper
  double b_damper = 0.35; 
  double forceD = -b_damper*vh;

  // calculate motor torque needed to produce desired resistive force 
  double Tm = rh*(force - forceD);  

  // check direction to oppose force
  if(force < 0) { 
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
  } 
  else {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
  }

  // Compute the duty cycle required to generate Tp (torque at the motor pulley)
  double duty = sqrt(abs(Tm)/0.03);
  
  // Make sure the duty cycle is between 0 and 100%
  if (duty > 1) {            
    duty = 1;
  } else if (duty < 0) { 
    duty = 0;
  }  

  int output = (int)(duty*50);   // convert duty cycle to output signal
  analogWrite(ena,output);
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

// --------------------------------------------------------------
// Function to set PWM Freq -- DO NOT EDIT
// --------------------------------------------------------------
void setPwmFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}