#include ".\motor.h"
#include ".\display.h"

motor myMotor;
display myDisplay;

void setup() {
  // Begin serial monitors
  Serial.begin(9600);

  // Initialize
  myMotor.encoderPinInit();
  myDisplay.displayInit();

  Serial.println("Hello");
}

void loop() {
  // Calculate shaft position
  myMotor.calcPosition();
  myDisplay.displayWrite(myMotor.position);
}
