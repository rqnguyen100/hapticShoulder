#include <Wire.h>

double data = 0; 
void setup() {
  // put your setup code here, to run once:
  Wire.begin(9);
  Wire.onReceive(receiveEvent);

}

void receiveEvent(int bytes) {
  data = Wire.read();
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(data);
}
