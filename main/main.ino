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

motor motor1(1, 10./3,  2, 6, 4, 5, 0, 0, 9, 10, 20, -20); // big basket
motor motor2(2, 1,     18, 17, 16, 15, 0, 0, 11, 32, 45, -45); // humeral
motor motor3(3, 10./3, 19, 20, 21, 22, 0, 0, 12, 33, 20, -20); // small basket

unsigned long timestamp;

void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Velocity LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

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
    motor2.begin(motor2.aPin, motor2.bPin, motor2.invAPin, motor2.invBPin, motor2.upperLimitPin, motor2.lowerLimitPin, motor2.pwmPin, motor2.dirPin);
    motor3.begin(motor3.aPin, motor3.bPin, motor3.invAPin, motor3.invBPin, motor3.upperLimitPin, motor3.lowerLimitPin, motor3.pwmPin, motor3.dirPin);

    // Calibrate Position
    // motor1.calibratePosition();
}

void loop() {
    // Calculate position output
    motor1.calcPosition();
    motor2.calcPosition();
    motor3.calcPosition();

    // Do haptics
    // motor1.calcTorqueOutput();
    motor2.calcTorqueOutput();
    // motor3.calcTorqueOutput();

    // timestamp = millis();

    // // print position for logging purposes
    // Serial.print(motor1.truePosition);
    // Serial.print(", ");
    // Serial.println(timestamp);
        
    // delay(10);
}