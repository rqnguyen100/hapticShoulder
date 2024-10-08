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
    const int invAPin;
    const int invBPin;
    volatile bool aState;
    volatile bool bState;
    volatile bool invAState;
    volatile bool invBState;
    volatile bool reconstructedA;
    volatile bool reconstructedB;
    volatile double encoderCount;
    volatile double position;     // DELETE
    volatile double theta;

    /*Attributes Relating to Motor*/
    const int dirPin; // M1 Pin
    const int pwmPin; // E1 Pin

    /*Attributes Relating to Haptics*/
    const int kSpring;
    const int bDamper;
    const int upperLim;
    const int lowerLim;
    volatile double kSpring_nL;      // non-linear spring equation

    /*Kinematic Variables*/
    const double rh = 0.0154;        // [meters] moment arm from joint center to force line of action

    // Translational space
    volatile double xh = 0;          // x position of handle
    volatile double lastXh = 0;      // last x position of the handle
    volatile double vh = 0;          // velocity of the handle
    volatile double lastVh = 0;      // last velocity of the handle
    volatile double lastLastVh = 0;  // last last velocity of the handle
    
    // Rotational space
    volatile double thetaE = 0;      // [radians] error angle position (angle over which tendon is stretched in end ROM) 
    volatile double lastThetaE = 0;  // last error angle position
    volatile double omegaE = 0;      // angular velocity of the handle (radians/s)
    volatile double lastOmegaE = 0;  // last angular velocity of the handle (radians/s)
    volatile double lastLastOmegaE = 0; // last last angular velocity of the handle (radians/s)

    volatile double Tm = 0;          // torque

    /*Haptic Variables*/
    volatile double forceP = 0;
    volatile double forceD = 0;
    volatile double duty = 0;
    volatile double torqueOutput = 0;

    /*Coupling Variables*/
    static bool medialBool;       // if true, changes joint limits in response to an inward humeral rotation 
    static bool externalBool;     // if true, changes joint limits in response to an outward humeral rotation

    /*Instance Handler*/
    static motor * instances [3];
    static void encoderAPulseExt0();
    static void encoderAPulseExt1();
    static void encoderAPulseExt2();
    static void encoderBPulseExt0();
    static void encoderBPulseExt1();
    static void encoderBPulseExt2();

public:
    /*Functions*/
    motor(int motorID, float gearRatio, int aPin, int bPin, int invAPin, int invBPin, int pwmPin, int dirPin, int upperLim, int lowerLim, int kSpring = 10, int bDamper = 0.35);

    void begin(const byte aPin, const byte bPin, const byte invAPin, const byte invBPin, const byte pwmPin, const byte dirPin);

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

    /*Motor Output*/
    const int pwmFactor = 255;
};

#endif
