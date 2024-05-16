#include <Wire.h>
#include "I2C_Anything.h"

const int SLAVE_ADDRESS = 9;
volatile boolean haveData = false;
volatile double motor1_pos; 
volatile double motor2_pos; 
volatile double motor3_pos;

unsigned long timestamp;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  
  Serial.print("Motor 1");
  Serial.print(", ");
  Serial.print("Motor 2");
  Serial.print(", ");
  Serial.print("Motor 3");
  Serial.print(", ");
  Serial.println("Timestamp");
}

void loop() {
  // put your main code here, to run repeatedly:
  if (haveData){
    Serial.print(motor1_pos);
    Serial.print(", ");
    Serial.print(motor2_pos);
    Serial.print(", ");
    Serial.print(motor3_pos);
    Serial.print(", ");
    Serial.println(timestamp);

    haveData = false;
  }
}

void receiveEvent (int howMany)
 {
 if (howMany >= (sizeof motor1_pos) + (sizeof motor2_pos) + (sizeof motor3_pos) + (sizeof timestamp))
   {
   I2C_readAnything(motor1_pos);
   I2C_readAnything(motor2_pos);
   I2C_readAnything(motor3_pos);
   I2C_readAnything(timestamp);
   haveData = true;
   }  // end if have enough data
 }  // end of receiveEvent


