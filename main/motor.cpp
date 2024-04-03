#include <Arduino.h>
#include ".\motor.h"

motor::motor(){
    // constructor
}

void motor::motorPinInit(){
}

/*----------------------------------------*/
int motor::encoderCount = 0;
bool motor::aState = 1;
bool motor::bState = 1;

void motor::encoderPinInit(){
    // Initialize encoder pins
    pinMode(ENCODER_A_PIN, INPUT);
    pinMode(ENCODER_B_PIN, INPUT);

    /*
      aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
      aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
      aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
    */
    attachInterrupt(digitalPinToInterrupt(ENCODER_A_PIN), encoderAPulse, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENCODER_B_PIN), encoderBPulse, CHANGE);
}

void motor::calcPosition(){
    motor::position = motor::encoderCount * (360. / (CPR * 4));
}

void motor::encoderAPulse(){
  // Read channels
  motor::aState = digitalRead(ENCODER_A_PIN);
  motor::bState = digitalRead(ENCODER_B_PIN);

  // Determine direction based on A and B state
  if (motor::aState){
    if (motor::bState){
      motor::encoderCount++;
    }
    else {
      motor::encoderCount--;
    }
  }
  else {
    if (motor::bState){
      motor::encoderCount--;
    }
    else {
      motor::encoderCount++;
    }
  }
}

void motor::encoderBPulse(){
  // Read channels
  motor::aState = digitalRead(ENCODER_A_PIN);
  motor::bState = digitalRead(ENCODER_B_PIN);

  // Determine direction based on A and B state
  if (motor::bState){
    if (motor::aState){
      motor::encoderCount--;
    }
    else {
      motor::encoderCount++;
    }
  }
  else {
    if (motor::aState){
      motor::encoderCount++;
    }
    else {
      motor::encoderCount--;
    }
  }
}