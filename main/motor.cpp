#include <Arduino.h>
#include "motor.h"

// Constructor for motor_instance
motor::motor(int motorID, float gearRatio, int aPin, int bPin, int invAPin, int invBPin, int upperLimitPin, int lowerLimitPin, int pwmPin, int dirPin, int upperLim, int lowerLim, int kSpring = 10, int bDamper = 0.35)
    : motorID(motorID), gearRatio(gearRatio), aPin(aPin), bPin(bPin), invAPin(invAPin), invBPin(invBPin), upperLimitPin(upperLimitPin), lowerLimitPin(lowerLimitPin), pwmPin(pwmPin), dirPin(dirPin), upperLim(upperLim), lowerLim(lowerLim), kSpring(kSpring), bDamper(bDamper) {
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

void motor::begin(const byte aPin, const byte bPin, const byte invAPin, const byte invBPin, const byte upperLimitPin, const byte lowerLimitPin, const byte pwmPin, const byte dirPin){
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);
  pinMode(invAPin, INPUT);
  pinMode(invBPin, INPUT);

  //pinMode(upperLimitPin, INPUT);
  //pinMode(lowerLimitPin, INPUT);

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
      // attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseExt0, CHANGE);
      instances[0] = this;
      break;
        
    case 18:
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt1, CHANGE);
      // attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseExt1, CHANGE);
      instances[1] = this;
      break;

    case 19: 
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt2, CHANGE);
      // attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseExt2, CHANGE);
      instances[2] = this;
      break;

  }
} 

// void motor::calibratePosition(){
//     bool upperSet = 1;
//     bool lowerSet = 1;

//     while (upperSet){
//       if (digitalRead(motor::upperLimitPin)) {
//         upperSet = 0;
//         motor::calibratedUpperLim = (motor::encoderCount / motor::gearRatio) * (360. / (CPR * resolution));
//         //Serial.println("Calibrated Upper Limit");
//         }
//       else {
//         //Serial.println("Move arm to upper limit switch...");
//         }

//       delay(10);
//     }

//     while (lowerSet){
//       if (digitalRead(motor::lowerLimitPin)) {
//         lowerSet = 0;
//         motor::calibratedLowerLim = (motor::encoderCount / motor::gearRatio) * (360. / (CPR * resolution));
//         //Serial.println("Calibrated Lower Limit");
//         }
//       else{
//         //Serial.println("Move arm to lower limit switch...");
//         }

//       delay(10);
//     }

//   // motor::thetaBias = (motor::calibratedUpperLim + motor::calibratedLowerLim) / 2;

//   delay(5000);
//   /*
//   while (true) {
//     Serial.println("Return arm to free range and press enter...");
//     delay(100);

//     if (Serial.available() > 0) {
//       char c = Serial.read();

//       // Check if the received character is newline (Enter key)
//       if (c == '\n') {
//         Serial.println("Enter pressed. Loading program...");
//         Serial.print("[");
//         for (int i = 0; i < 10; i++) {
//           Serial.print("█");
//           delay(250);
//           }
//         Serial.println("]");
//         delay(1000);
//         break;
//       }
//     }
//   }
//   */
// }

void motor::calcPosition() {
  motor::theta = (double)(motor::encoderCount / motor::gearRatio) * (360. / (CPR * resolution));
}

void motor::encoderAPulse() {
    // Read channels
  motor::aState = digitalRead(motor::aPin);
  motor::bState = digitalRead(motor::bPin);
  motor::invAState = digitalRead(motor::invAPin);
  motor::invBState = digitalRead(motor::invBPin);

  // Reconstruct signal to reduce noise
  motor::reconstructedA = motor::aState && !motor::invAState;
  motor::reconstructedB = motor::bState && !motor::invBState;

    // Determine direction based on A and B state
  if (motor::reconstructedA) {
    if (motor::reconstructedB) {
      motor::encoderCount--;
    }
    else {
      motor::encoderCount++;
    }
  }
  else {
    if (motor::reconstructedB) {
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
  motor::invAState = digitalRead(motor::invAPin);
  motor::invBState = digitalRead(motor::invBPin);

  // Reconstruct signal to reduce noise
  motor::reconstructedA = motor::aState && !motor::invAState;
  motor::reconstructedB = motor::bState && !motor::invBState;

    // Determine direction based on A and B state
  if (motor::reconstructedB) {
    if (motor::reconstructedA) {
      motor::encoderCount++;
    }
    else {
      motor::encoderCount--;
    }
  }
  else {
    if (motor::reconstructedA) {
      motor::encoderCount--;
    }
    else {
      motor::encoderCount++;
    }
  }
}

/* ====================================================================== */
bool motor::coupleBool = 0;
bool motor::medialBool = 0;
bool motor::externalBool = 0;

void motor::calcTorqueOutput(){
  // initialize limits
  int upperLimit = motor::upperLim;
  int lowerLimit = motor::lowerLim;

  // check for coupling on separateJ
  if (motor::motorID == 2 && motor::theta <= -50){  // CHANGE 90 TO MINIMUM DESIRED HUMERAL ROTATION TO UNLOCK LARGER ROM
    // motor::coupleBool = 1;
    motor::medialBool = 1;
  }
  else if (motor::motorID == 2 && motor::theta >= 85){
    motor::externalBool = 1;
  }
  else if (motor::motorID == 2){
    motor::medialBool = 0;
    motor::externalBool = 0;
  }

  // perform coupling on motor 3
  if (motor::motorID == 3 && motor::medialBool){
    upperLimit = 90; // new upper limit of free ROM for medial humeral rotation (-50 degrees)
    lowerLimit = -15;
  }
  else if (motor::motorID == 3 && motor::externalBool){
    upperLimit = 165; // new upper limit of free ROM for external humeral rotation (85 degrees)
    lowerLimit = -15;
  }
  else if (motor::motorID == 3){
    upperLimit = 135; // default upper limit of free ROM for no humeral rotation (0 degrees)
    lowerLimit = -15;
  }

  // calculate handle position
  if (motor::theta < lowerLimit){
    // motor::xh = rh*(motor::theta - lowerLimit)*(3.14/180);
    motor::thetaE = (motor::theta - lowerLimit)*(3.14/180);
  }
  else if (motor::theta > upperLimit){
    // motor::xh = rh*(motor::theta - upperLimit)*(3.14/180);
    motor::thetaE = (motor::theta - upperLimit)*(3.14/180);  // angle error in radians 
  }
  else{
    // motor::xh = 0;
    motor::thetaE = 0;


    // motor::truePosition = motor::theta - motor::thetaBias;
  }

  // // Position Limit
  // if (motor::theta > 270){
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   analogWrite(motor::pwmPin, 0);
  // }
  // else if (motor::theta < -270){
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   analogWrite(motor::pwmPin, 0);
  // }

  // Compute tendon stretching velocity -> filtered velocity (2nd-order filter)

  // translational space
  // motor::vh = -(.95*.95)*motor::lastLastVh + 2*.95*motor::lastVh + (1-.95)*(1-.95)*(motor::xh-motor::lastXh)/.0001; 
  // motor::lastXh = motor::xh;
  // motor::lastLastVh = motor::lastVh;
  // motor::lastVh = motor::vh;

  // rotational space
  motor::omegaE = rh*(-(.95*.95)*motor::lastLastOmegaE + 2*.95*motor::lastOmegaE + (1-.95)*(1-.95)*(rh*motor::thetaE-motor::lastThetaE)/.0001);
  motor::lastThetaE = motor::thetaE;
  motor::lastLastOmegaE = motor::lastOmegaE;
  motor::lastOmegaE = motor::omegaE;



  // Velocity Limit
  // if (motor::vh > 5){
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   analogWrite(motor::pwmPin, 0);
  // }

  // Render a virtual spring
  // motor::forceP = -motor::kSpring*motor::xh; // Resistive spring force [N]

  // Render a virtual spring (non-linear spring)
  Kp = 0.25*(0.12*pow((rh*1000)*motor::thetaE, 2) + 0.194*((rh*1000)*motor::thetaE) - 0.051); // [N/mm]
  motor::forceP = -Kp*((rh*1000)*motor::thetaE); // Resistive spring force [N] 

  // Render a damper
  // motor::forceD = -motor::bDamper*motor::vh; // translational space
  motor::forceD = -motor::bDamper*motor::omegaE; // rotational space

  // Calculate motor torque needed to produce desired resistive force 
  motor::Tm = rh*(motor::forceP - motor::forceD);  

  // Compute the duty cycle required to generate Tp (torque at the motor pulley)
  motor::duty = sqrt(abs(motor::Tm)/0.0566);
  
  // Make sure the duty cycle is between 0 and 100%
  if (motor::duty > 1) {            
    motor::duty = 1;
  } 
  else if (motor::duty < 0) { 
    motor::duty = 0;
  }   

  motor::torqueOutput = (int)(motor::duty*tarunFactor);   // convert duty cycle to output signal

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