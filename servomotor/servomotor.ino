#include <Servo.h>

Servo servoMotor;

void setup() {
  Serial.begin(9600);
  servoMotor.attach(5);
  Serial.println("Servo Motor Testi Basladi!");
  servoMotor.write(0);
  delay(1000);
}

void loop() {
  for (int pos = 0; pos <= 180; pos += 1) {
    servoMotor.write(pos);
    delay(15);
  }

  delay(1000);

  for (int pos = 180; pos >= 0; pos -= 1) {
    servoMotor.write(pos);
    delay(15);
  }

  delay(1000);
}
