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
    - pwmPin (E1 speed control)
    - dirPin (M1 direction control)
    - upperLimit in deg (for free ROM) [has to be positive]
    - lowerLimit in deg (for free ROM) [has to be negative]
    [optional]
      - spring constant (default = 10) 
      - damper ratio (default = 0.35)
*/

motor motor1(1, 1, 2, 6, 4, 5, 12, 11, 9, 8, 90, -90);
// motor motor2(2, 1, 18, 5, 7, 42, 20, -20);
// motor motor3(3, 1, 19, 6, 6, 43, 30, -30);


void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Change PWM pin frequency to 20kHz
    /*
    TCCR1B &= ~7;
    TCCR1B |= 1;
    TCCR2B &= ~7;
    TCCR2B |= 1;
    TCCR4B &= ~7;
    TCCR4B |= 1;
    */

    // Initialize Pins
    motor1.begin(motor1.aPin, motor1.bPin, motor1.invAPin, motor1.invBPin, motor1.upperLimitPin, motor1.lowerLimitPin, motor1.pwmPin, motor1.dirPin);

    // Calibrate Position
    motor1.calibratePosition();
}

void loop() {
    // Calculate position output
    motor1.calcPosition();

    // Do haptics
    motor1.calcTorqueOutput();

    // print position for logging purposes
    Serial.println(motor1.truePosition);
    delay(10);
}