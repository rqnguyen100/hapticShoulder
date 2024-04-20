#include <Arduino.h>
#include "motor.h"

// Global instance of the motor class
motor motor_instance(0, 0, false, false, 0, 0);

// Constructor for motor_instance
motor::motor(int aPin, int bPin, bool aState, bool bState, double encoderCount, double position)
    : aPin(aPin), bPin(bPin), aState(aState), bState(bState), encoderCount(encoderCount), position(position) {
}

void motor::encoderPinInit() {
    // Initialize encoder pins
    pinMode(aPin, INPUT);
    pinMode(bPin, INPUT);

    /*
      aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
      aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
      aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
    */
    attachInterrupt(digitalPinToInterrupt(aPin), encoderAPulseISR, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(bPin), encoderBPulseISR, CHANGE);
}

void motor::calcPosition() {
    position = encoderCount * (360. / (CPR * 4));
}

// Static member function for A pulse ISR
void motor::encoderAPulseISR() {
    // Retrieve the instance from the global scope
    motor* instance = &motor_instance;
    // Call the member function
    encoderAPulse(instance);
}

// Static member function for handling A pulse
void motor::encoderAPulse(motor* instance) {
    // Read channels
    instance->aState = digitalRead(instance->aPin);
    instance->bState = digitalRead(instance->bPin);

    // Determine direction based on A and B state
    if (instance->aState) {
        if (instance->bState) {
            instance->encoderCount++;
        }
        else {
            instance->encoderCount--;
        }
    }
    else {
        if (instance->bState) {
            instance->encoderCount--;
        }
        else {
            instance->encoderCount++;
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