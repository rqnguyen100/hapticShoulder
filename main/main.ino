#include "motor.h"

unsigned long previousMillis = 0;  // Store the last time the data was sent
const long interval = 100;          // Interval at which to send data (15 ms)

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

// motor mujBig(  1, 10./3,  2,  4,  5,  6, 0, 0, 12, 11, 20, -20); // big basket
// motor mujSmall(3, 10./3, 19, 20, 21, 22, 0, 0,  9,  8, 20, -20); // small baske1
// motor separJ(  2,     1, 18, 17, 16, 15, 0, 0, 32, 33, 20, -20); // humeral

motor oneDOF(  1,     1, 18, 17, 16, 15, 0, 0,  9,  8, 10, -10, 5); 

void setup() {
    // Begin serial monitor
    Serial.begin(9600);

    // Print Headers
    // Serial.print("MUJ big basket position (deg)");
    // Serial.print(", ");
    // Serial.print("MUJ small basket position (deg)");
    // Serial.print(", ");
    // Serial.print("Separate joint position (deg)");
    // Serial.print(", ");
    // Serial.println("Time after start-up (ms)");

    // Velocity LED
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Change PWM pin frequency to 20kHz
    TCCR1B &= ~7;
    TCCR1B |= 1;
    TCCR2B &= ~7;
    TCCR2B |= 1;
    TCCR4B &= ~7;
    TCCR4B |= 1;
    

    // Initialize Pins 
    // mujBig.begin(mujBig.aPin, mujBig.bPin, mujBig.invAPin, mujBig.invBPin, mujBig.upperLimitPin, mujBig.lowerLimitPin, mujBig.pwmPin, mujBig.dirPin);
    // separJ.begin(separJ.aPin, separJ.bPin, separJ.invAPin, separJ.invBPin, separJ.upperLimitPin, separJ.lowerLimitPin, separJ.pwmPin, separJ.dirPin);
    // mujSmall.begin(mujSmall.aPin, mujSmall.bPin, mujSmall.invAPin, mujSmall.invBPin, mujSmall.upperLimitPin, mujSmall.lowerLimitPin, mujSmall.pwmPin, mujSmall.dirPin);

    oneDOF.begin(oneDOF.aPin, oneDOF.bPin, oneDOF.invAPin, oneDOF.invBPin, oneDOF.upperLimitPin, oneDOF.lowerLimitPin, oneDOF.pwmPin, oneDOF.dirPin);

    Serial.print("Time since startup (ms)");
    Serial.print(", ");
    Serial.println("Angle (deg)");
    // Calibrate Position
    // mujBig.calibratePosition();
}

void loop() {
    // Position Output
    // mujBig.calcPosition();
    // separJ.calcPosition();
    // mujSmall.calcPosition();

    oneDOF.calcPosition();

    // Haptic Feedback
    // mujBig.calcTorqueOutput();
    // separJ.calcTorqueOutput();
    // mujSmall.calcTorqueOutput();

    oneDOF.calcTorqueOutput();

    // Position Logging
    unsigned long currentMillis = millis();  // Get the current time

    if (currentMillis - previousMillis >= interval){
      // Save the last time data was sent
      previousMillis = currentMillis;

      Serial.print(currentMillis);
      Serial.print(", ");
      Serial.println(oneDOF.position);
    }
   



    

    // delay(50);
}