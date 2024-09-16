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

//   motor::thetaBias = (motor::calibratedUpperLim + motor::calibratedLowerLim) / 2;

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
  motor::theta = (double)(motor::encoderCount / motor::gearRatio) * (360. / (CPR * resolution)); // angular position of motor in degrees
  // motor::truePosition = motor::theta - motor::thetaBias;
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

void motor::calcTorqueOutput(){
  // initialize limits
  int upperLimit = motor::upperLim; // end ROM in positive direction (degrees)
  int lowerLimit = motor::lowerLim; // end ROM in negative direction (degrees)

  // check for coupling on separateJ
  // if (motor::motorID == 2 && abs(motor::theta) >= 85){
  //   motor::coupleBool = 1;
  // }
  // else if (motor::motorID == 2){
  //   motor::coupleBool = 0;
  // }

  // // perform coupling on motor 3
  // if (motor::motorID == 3 && motor::coupleBool){
  //   upperLimit = 165;
  //   lowerLimit = -15;
  // }
  // else if (motor::motorID == 3){
  //   upperLimit = 90;
  //   lowerLimit = -15;
  // }

  // calculate handle position
  if (motor::theta < lowerLimit){
    // motor::xh = rh*(motor::position - lowerLimit)*(3.14/180);
    motor::thetaE = (motor::theta - lowerLimit)*(3.14/180);  // angle error in radians
    // Serial.print("position in left end ROM");
  }
  else if (motor::theta > upperLimit){
    // motor::xh = rh*(motor::theta - upperLimit)*(3.14/180);
    motor::thetaE = (motor::theta - upperLimit)*(3.14/180);  // angle error in radians 
    // Serial.print("position in right end ROM");
  }
  else{
    // motor::xh = 0;
    motor::thetaE = 0;
    // return; // break function if in free ROM to save computational time
  }

  // Position Limit
  // if (motor::theta > 90){
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   while (true){
  //     analogWrite(motor::pwmPin, 0);
  //   }
  // }
  // else if (motor::theta < -90){
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   while (true){
  //     analogWrite(motor::pwmPin, 0);
  //   }
  // }

  // Compute handle velocity -> filtered velocity (2nd-order filter)

  // motor::vh = -(.95*.95)*motor::lastLastVh + 2*.95*motor::lastVh + (1-.95)*(1-.95)*(motor::xh-motor::lastXh)/.0001; 
  motor::omegaE = rh*(-(.95*.95)*motor::lastLastOmegaE + 2*.95*motor::lastOmegaE + (1-.95)*(1-.95)*(rh*motor::thetaE-motor::lastThetaE)/.0001);
  // motor::lastXh = motor::xh;
  motor::lastThetaE = motor::thetaE;
  // motor::lastLastVh = motor::lastVh;
  motor::lastLastOmegaE = motor::lastOmegaE;
  // motor::lastVh = motor::vh;
  motor::lastOmegaE = motor::omegaE;

  // Velocity Limit
  // if (motor::vh > 5){
  //   digitalWrite(LED_BUILTIN, HIGH);
  //   while (true){
  //     analogWrite(motor::pwmPin, 0);
  //   }
  // }


  // Render a virtual spring (linear spring)
  // motor::forceP = -motor::kSpring*motor::xh; // Resistive spring force
  // motor::forceP = -motor::kSpring*(rh*motor::thetaE);  // Resistive spring force [Newtons], kSpring = [N/m]
  
  // REPLACE WITH NEW EQUATION FROM CALVIN
  // Kp = 36*pow(motor::xh*1000, 2) + 58.2*(motor::xh*1000) - 15.3;
  // Kp = 36*pow(rh*motor::thetaE*1000, 2) + 58.2*(rh*motor::thetaE*1000) - 15.3; // Non-linear spring equation [N/mm]
  // Kp = 0.036*pow(rh*motor::thetaE, 2) + 0.058*(rh*motor::thetaE) - 0.015; // SCALED Non-linear spring equation [N/mm]
  Kp = 0.12*pow((rh*1000)*motor::thetaE, 2) + 0.194*((rh*1000)*motor::thetaE) - 0.051;

  
  // Render a virtual spring (non-linear spring)
  // motor::forceP = -Kp*(motor::xh*1000); // Resistive spring force [N]
  // motor::forceP = -Kp*((rh*1000)*motor::thetaE); // Resistive spring force [N] 
  // To compensate for Kp having units N/mm and rh being in m, rh is multiplied by 1000
  if (motor::thetaE > 0) {
    motor::forceP = -(0.04*pow(rh*1000*motor::thetaE, 3) + 0.097*pow(rh*1000*motor::thetaE, 2) - 0.051*(rh*1000*motor::thetaE) + 0.0054);
  }
  else{
    motor::forceP = 0;
  }

  
  // Render a damper
  // motor::forceD = -motor::bDamper*motor::vh;
  motor::forceD = -motor::bDamper*motor::omegaE;

  // Calculate motor torque needed to produce desired resistive force 
  motor::Tm = rh*(motor::forceP - motor::forceD); // Resistive TORQUE [N*m]   

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
  else{
    digitalWrite(motor::dirPin, LOW);
    analogWrite(motor::pwmPin, motor::torqueOutput);
  }
}