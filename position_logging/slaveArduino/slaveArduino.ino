#include <Wire.h>
#include "I2C_Anything.h"

const int SLAVE_ADDRESS = 9;
volatile boolean haveData = false;
volatile double data;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (haveData){
    Serial.print("Motor 1: ");
    Serial.print(", ");
    Serial.println(data);
    haveData = false;
  }
}

void receiveEvent (int howMany)
 {
 if (howMany >= (sizeof data))
   {
   I2C_readAnything (data);
   haveData = true;
   }  // end if have enough data
 }  // end of receiveEvent


