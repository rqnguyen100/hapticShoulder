  // Coast Mode -> Push CCW
  while (position < 90){
    // Coast Mode
    digitalWrite(m1Pin, LOW);
    digitalWrite(m2Pin, LOW);

    // Calculate shaft position
    position = encoderCount * (360. / (CPR * 4));
    Serial.println(position);
  }

  // Get position data in-between loops
  position = encoderCount * (360. / (CPR * 4));

  // "Brake" Mode
  while (position >= 90){
    // "Brake" Mode
    digitalWrite(m1Pin, LOW);
    analogWrite(m2Pin, 30);

    // Calculate shaft position
    position = encoderCount * (360. / (CPR * 4));
    Serial.println("Out of Range");
  }