#include <Arduino.h>
#include "motor.h"

// Constructor for motor_instance
motor::motor(int motorID, float gearRatio, int aPin, int bPin, int pwmPin, int dirPin, int upperLim, int lowerLim, int kSpring = 10, int bDamper = 0.35)
    : motorID(motorID), gearRatio(gearRatio), aPin(aPin), bPin(bPin), pwmPin(pwmPin), dirPin(dirPin), upperLim(upperLim), lowerLim(lowerLim), kSpring(kSpring), bDamper(bDamper) {
}

motor* motor::instances[3] = {NULL, NULL, NULL};

void motor::encoderAPulseExt0(){
  if (motor::instances[0] != NULL){
    motor::instances[0]->encoderAPulse();
  }
}

void motor::encoderAPulseExt1(){
  if (motor::instances[1] != NULL){
    motor::instances[1]->encoderAPulse();
  }
} 

void motor::encoderAPulseExt2(){
  if (motor::instances[2] != NULL){
    motor::instances[2]->encoderAPulse();
  }
} 

void motor::encoderBPulseExt0(){
  if (motor::instances[0] != NULL){
    motor::instances[0]->encoderBPulse();
  }
}

void motor::encoderBPulseExt1(){
  if (motor::instances[1] != NULL){
    motor::instances[1]->encoderBPulse();
  }
}

void motor::encoderBPulseExt2(){
  if (motor::instances[2] != NULL){
    motor::instances[2]->encoderBPulse();
  }
}

void motor::begin(const byte aPin, const byte bPin, const byte pwmPin, const byte dirPin){
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);

  pinMode(pwmPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  /*
    aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
    aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
    aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
  */
  switch (aPin){
    case 2: 
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt0, CHANGE);
      attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseExt0, CHANGE);
      instances[0] = this;
      break;
        
    case 18:
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt1, CHANGE);
      attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseExt1, CHANGE);
      instances[1] = this;
      break;

    case 19: 
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt2, CHANGE);
      attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseExt2, CHANGE);
      instances[2] = this;
      break;

  }
} 

void motor::calcPosition() {
    motor::position = (double)(motor::encoderCount / motor::gearRatio) * (360. / (CPR * resolution));
}

void motor::encoderAPulse() {
    // Read channels
    motor::aState = digitalRead(motor::aPin);
    motor::bState = digitalRead(motor::bPin);

    // Determine direction based on A and B state
    if (motor::aState) {
        if (motor::bState) {
            motor::encoderCount--;
        }
        else {
            motor::encoderCount++;
        }
    }
    else {
        if (motor::bState) {
            motor::encoderCount++;
        }
        else {
            motor::encoderCount--;
        }
    }
}

void motor::encoderBPulse(){
  // Read channels
  motor::aState = digitalRead(motor::aPin);
  motor::bState = digitalRead(motor::bPin);

  // Determine direction based on A and B state
  if (motor::bState){
    if (motor::aState){
      motor::encoderCount++;
    }
    else {
      motor::encoderCount--;
    }
  }
  else {
    if (motor::aState){
      motor::encoderCount--;
    }
    else {
      motor::encoderCount++;
    }
  }
}

/* ====================================================================== */
bool motor::coupleBool = 0;

void motor::calcTorqueOutput(){
  // initialize limits
  int upperLimit = motor::upperLim;
  int lowerLimit = motor::lowerLim;

  /*
  // check for coupling
  if (motor::motorID == 1 && abs(motor::position) > 45){
    motor::coupleBool = 1;
  }
  else if (motor::motorID == 1){
    motor::coupleBool = 0;
  }

  // perform coupling on motor 2
  if (motor::motorID == 2 && motor::coupleBool){
    upperLimit = 90;
    lowerLimit = -90;
  }
  else if (motor::motorID == 2){
    upperLimit = 45;
    lowerLimit = -45;
  }
  */

  // calculate handle position
  if (motor::position < lowerLimit){
    motor::xh = rh*(motor::position - lowerLimit)*(3.14/180);
  }
  else if (motor::position > upperLimit){
    motor::xh = rh*(motor::position - upperLimit)*(3.14/180);
  }
  else{
    motor::position = (double)(motor::encoderCount / motor::gearRatio) * (360. / (CPR * resolution));
    return; // break function if in free ROM to save computational time
  }

  // Compute handle velocity -> filtered velocity (2nd-order filter)
  motor::vh = -(.95*.95)*motor::lastLastVh + 2*.95*motor::lastVh + (1-.95)*(1-.95)*(motor::xh-motor::lastXh)/.0001; 
  motor::lastXh = motor::xh;
  motor::lastLastVh = motor::lastVh;
  motor::lastVh = motor::vh;

  // Render a virtual spring
  motor::forceP = -motor::kSpring*motor::xh; // Resistive spring force
  
  // Render a damper
  motor::forceD = -motor::bDamper*motor::vh;

  // Calculate motor torque needed to produce desired resistive force 
  motor::Tm = rh*(motor::forceP - motor::forceD);  

  // Compute the duty cycle required to generate Tp (torque at the motor pulley)
  motor::duty = sqrt(abs(motor::Tm)/0.03);
  
  // Make sure the duty cycle is between 0 and 100%
  if (motor::duty > 1) {            
    motor::duty = 1;
  } 
  else if (motor::duty < 0) { 
    motor::duty = 0;
  }   

  motor::torqueOutput = (int)(motor::duty*150);   // convert duty cycle to output signal

  // Check direction to oppose force
  if(motor::forceP < 0) { 
    digitalWrite(motor::dirPin, HIGH);
    analogWrite(motor::pwmPin, motor::torqueOutput);
  } 
  else {
    digitalWrite(motor::dirPin, LOW);
    analogWrite(motor::pwmPin, motor::torqueOutput);
  }
}