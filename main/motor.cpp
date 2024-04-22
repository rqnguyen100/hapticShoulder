#include <Arduino.h>
#include "motor.h"

// Constructor for motor_instance
motor::motor(int aPin, int bPin, bool aState, bool bState, double encoderCount, double position)
    : aPin(aPin), bPin(bPin), aState(aState), bState(bState), encoderCount(encoderCount), position(position) {
}

motor* motor::instances[2] = {NULL, NULL};

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

void motor::begin(const byte aPin, const byte bPin){
  pinMode(aPin, INPUT);
  pinMode(bPin, INPUT);

  /*
    aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
    aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
    aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
  */
  switch (aPin){
    case 2: 
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt0, CHANGE);
      instances[0] = this;
      break;
        
    case 3: 
      attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseExt1, CHANGE);
      instances[1] = this;
      break;
  }
} 

void motor::calcPosition() {
    motor::position = motor::encoderCount * (360. / (CPR * resolution));
}

void motor::encoderAPulse() {
    // Read channels
    motor::aState = digitalRead(motor::aPin);
    motor::bState = digitalRead(motor::bPin);

    // Determine direction based on A and B state
    if (motor::aState) {
        if (motor::bState) {
            motor::encoderCount++;
        }
        else {
            motor::encoderCount--;
        }
    }
    else {
        if (motor::bState) {
            motor::encoderCount--;
        }
        else {
            motor::encoderCount++;
        }
    }
}

// void motor::encoderBPulse(){
//   // Read channels
//   motor::aState = digitalRead(ENCODER_A_PIN);
//   motor::bState = digitalRead(ENCODER_B_PIN);

//   // Determine direction based on A and B state
//   if (motor::bState){
//     if (motor::aState){
//       motor::encoderCount--;
//     }
//     else {
//       motor::encoderCount++;
//     }
//   }
//   else {
//     if (motor::aState){
//       motor::encoderCount++;
//     }
//     else {
//       motor::encoderCount--;
//     }
//   }
// }