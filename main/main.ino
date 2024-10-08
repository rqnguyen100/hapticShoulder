#include "motor.h"

unsigned long timestamp;

/*
  intialize motor class with inputs
    - motorID
    - gear ratio
      - Disclaimer: must be float or natural number
    - aPin (encoder A channel)
      - Disclaimer: must verify begin() switch statement is consistent with pins
    - bPin (encoder B channel)
    - invAPin (encoder inverse A channel)
    - invBPin (encoder inverse B channel)
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10)
      - damper ratio (default = 0.35)
*/

motor mujBig(  1, 10./3,  2,  4,  5,  6, 12, 11,  7, -187); // big basket
motor mujSmall(3, 10./3, 19, 20, 21, 22, 9,  8,  135, -15, 10); // small baske1
motor separJ(  2,     1, 18, 17, 16, 15, 32, 33, 20, -20); // humeral

void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Print Headers
    Serial.print("Humeral Angle (deg)");
    Serial.print(", ");
    Serial.print("Abduction Angle (deg)");
    Serial.print(", ");
    Serial.print("PWM Torque");
    Serial.print(", ");
    Serial.println("Elapsed Time (ms)");


    // Velocity LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Change PWM pin frequency to 20kHz
    
    
    // TCCR1B &= ~7;
    // TCCR1B |= 1;
    // TCCR2B &= ~7;
    // TCCR2B |= 1;
    // TCCR4B &= ~7;
    // TCCR4B |= 1;
    
  

    // Initialize Pins
    mujBig.begin(mujBig.aPin, mujBig.bPin, mujBig.invAPin, mujBig.invBPin, mujBig.upperLimitPin, mujBig.lowerLimitPin, mujBig.pwmPin, mujBig.dirPin);
    separJ.begin(separJ.aPin, separJ.bPin, separJ.invAPin, separJ.invBPin, separJ.upperLimitPin, separJ.lowerLimitPin, separJ.pwmPin, separJ.dirPin);
    mujSmall.begin(mujSmall.aPin, mujSmall.bPin, mujSmall.invAPin, mujSmall.invBPin, mujSmall.upperLimitPin, mujSmall.lowerLimitPin, mujSmall.pwmPin, mujSmall.dirPin);

}

void loop() {
    // Position Output
    mujBig.calcPosition();
    separJ.calcPosition();
    mujSmall.calcPosition();

    // Haptic Feedback
    mujBig.calcTorqueOutput();
    separJ.calcTorqueOutput();
    mujSmall.calcTorqueOutput();

    // Data logging
    timestamp = millis();
    Serial.print(separJ.theta);
    Serial.print(", ");
    Serial.print(mujSmall.theta);
    Serial.print(", ");
    Serial.print(mujSmall.torqueOutput);
    Serial.print(", ");
    Serial.println(timestamp);

    delay(50);
}