#include "motor.h"

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
    - upperLimitPin [calibrate upper limit]
    - lowerLimitPin [calibrate lower limit]
    - pwmPin (EN speed control)
    - dirPin1 (IN1 direction control)
    - dirPin2 (IN2 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/
motor oneDOF(1, 1, 2, 3, 4, 5, 0, 0, 9, 10, 11, 30, -30, 10);
 
unsigned long timestamp;

void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Serial.print("1 DOF Position (deg)");
    // Serial.print(", ");
    // Serial.println("Time after start-up (ms)");

    // Velocity LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Change PWM pin frequency to 20kHz
    /*
    TCCR0B &= ~7;
    TCCR0B |= 1;
    TCCR1B &= ~7;
    TCCR1B |= 1;
    TCCR2B &= ~7;
    TCCR2B |= 1;
    */

    // Initialize Pins
    oneDOF.begin(oneDOF.aPin, oneDOF.bPin, oneDOF.invAPin, oneDOF.invBPin, oneDOF.upperLimitPin, oneDOF.lowerLimitPin, oneDOF.pwmPin, oneDOF.dir1Pin, oneDOF.dir2Pin);
}

void loop() {
    // Calculate position output
    oneDOF.calcPosition();

    // Do haptics
    oneDOF.calcTorqueOutput();

    // // Serial.println(separateJ.position);

    // // // print position for logging purposes
    // Serial.print(oneDOF.position);
    // Serial.print(", ");
    
    // Serial.print("Angle: ");
    // Serial.print(oneDOF.position);
    // Serial.print(", ");
    // Serial.print("x_h: ");
    // Serial.print(oneDOF.xh);
    // Serial.print(", ");
    // Serial.print("Torque output: ");
    // Serial.print(oneDOF.torqueOutput);
    // Serial.print(", ");
    // Serial.print("Velocity: ");
    // Serial.print(oneDOF.vh);
    // Serial.print(", ");
    // // Serial.print("forceP: ");
    // // Serial.print(oneDOF.forceP);
    // // Serial.print(", ");
    // Serial.print("forceD: ");
    // Serial.println(oneDOF.forceD);

    // Serial.println(oneDOF.torqueOutput);
        
    // delay(10);
}