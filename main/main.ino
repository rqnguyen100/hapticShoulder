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

// motor test(1, 1, 8, 9, 10, 11, 12, 7, 3, 4, 5, 45, -45);
// motor mujBig(   1, 10./3,  2,  4,  5,  6, 0, 0,  8, 31, 43, 20, -20); 
// motor separateJ(2,     1, 18, 17, 16, 15, 0, 0, 10, 35, 41, 45, -45);   
// motor mujSmall( 3, 10./3, 19, 20, 21, 22, 0, 0,  9, 33, 39, 20, -20);  

motor oneDOF(   1,     1,  2,  3,  4,  5, 0, 0,  9, 10, 11, 45, -45);
 
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
    TCCR1B &= ~7;
    TCCR1B |= 1;
    TCCR2B &= ~7;
    TCCR2B |= 1;
    TCCR4B &= ~7;
    TCCR4B |= 1;
    */

    // Initialize Pins
    // test.begin(test.aPin, test.bPin, test.invAPin, test.invBPin, test.upperLimitPin, test.lowerLimitPin, test.pwmPin, test.dir1Pin, test.dir2Pin);
    // mujBig.begin(mujBig.aPin, mujBig.bPin, mujBig.invAPin, mujBig.invBPin, mujBig.upperLimitPin, mujBig.lowerLimitPin, mujBig.pwmPin, mujBig.dir1Pin, mujBig.dir2Pin);
    // separateJ.begin(separateJ.aPin, separateJ.bPin, separateJ.invAPin, separateJ.invBPin, separateJ.upperLimitPin, separateJ.lowerLimitPin, separateJ.pwmPin, separateJ.dir1Pin, separateJ.dir2Pin);
    // mujSmall.begin(mujSmall.aPin, mujSmall.bPin, mujSmall.invAPin, mujSmall.invBPin, mujSmall.upperLimitPin, mujSmall.lowerLimitPin, mujSmall.pwmPin, mujSmall.dir1Pin, mujSmall.dir2Pin);
    oneDOF.begin(oneDOF.aPin, oneDOF.bPin, oneDOF.invAPin, oneDOF.invBPin, oneDOF.upperLimitPin, oneDOF.lowerLimitPin, oneDOF.pwmPin, oneDOF.dir1Pin, oneDOF.dir2Pin);

    // Calibrate Position
    // mujBig.calibratePosition();
}

void loop() {
    // Calculate position output
    // test.calcPosition();
    // mujBig.calcPosition();
    // separateJ.calcPosition();
    // mujSmall.calcPosition();
    oneDOF.calcPosition();

    // Do haptics
    // test.calcTorqueOutput();
    // mujBig.calcTorqueOutput();
    // separateJ.calcTorqueOutput();
    // mujSmall.calcTorqueOutput();
    oneDOF.calcTorqueOutput();

    // timestamp = millis();

    // // Serial.println(separateJ.position);

    // // // print position for logging purposes
    Serial.print(oneDOF.position);
    Serial.print(", ");
    Serial.print(oneDOF.forceP);
    Serial.print(", ");
    Serial.println(timestamp);
        
    // delay(10);
}