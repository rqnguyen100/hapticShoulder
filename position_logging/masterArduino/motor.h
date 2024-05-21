#ifndef _MOTOR_H // header guard
#define _MOTOR_H

#include <Arduino.h>

class motor {
public:
    /*Motor ID*/
    const int motorID;
    const float gearRatio;
    
    /*Attributes Relating to Encoder*/
    const int aPin;
    const int bPin;
    volatile bool aState;
    volatile bool bState;
    volatile double encoderCount;
    volatile double position;

    /*Attributes Relating to Motor*/
    const int dirPin; // M1 Pin
    const int pwmPin; // E1 Pin

    /*Attributes Relating to Haptics*/
    const int kSpring;
    const int bDamper;
    const int upperLim;
    const int lowerLim;

    /*Kinematic Variables*/
    const double rh = 0.05;          // [meters] length of lever arm
    volatile double xh = 0;          // x position of handle
    volatile double lastXh = 0;      // last x position of the handle
    volatile double vh = 0;          // velocity of the handle
    volatile double lastVh = 0;      // last velocity of the handle
    volatile double lastLastVh = 0;  // last last velocity of the handle
    volatile double Tm = 0;          // torque

    /*Haptic Variables*/
    volatile double forceP = 0;
    volatile double forceD = 0;
    volatile double duty = 0;
    volatile double torqueOutput = 0;

    /*Coupling Variables*/
    static bool coupleBool;

    /*Instance Handler*/
    static motor * instances [3];
    static void encoderAPulseExt0();
    static void encoderAPulseExt1();
    static void encoderAPulseExt2();
    // static void encoderBPulseExt0();

public:
    /*Functions*/
    motor(int motorID, float gearRatio, int aPin, int bPin, int pwmPin, int dirPin, int upperLim, int lowerLim, int kSpring = 10, int bDamper = 0.35);

    void begin(const byte aPin, const byte bPin);

    //, const byte pwmPin, const byte dirPin (re-insert into begin function)

    void encoderAPulse();
    void encoderBPulse();

    void calcPosition();
    void calcTorqueOutput();

private:
    /*Encoder Specs*/
    const float CPR = 500; // counts per revolution

    /*
      aPin Rising = 1x Resolution (B does not have to be connected to interrupt pin)
      aPin Change = 2x Resolution (B does not have to be connected to interrupt pin)
      aPin and bPin Change = 4x Resolution (B has to be connected to interrupt pin)
    */
    const float resolution = 2; // dependent on number of interrupt pins used
};

#endif