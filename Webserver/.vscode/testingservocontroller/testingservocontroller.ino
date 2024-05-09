#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SERVO_STOP  msToPulseLen(1.65) // This is the 'stop' pulse length count (out of 4096)
#define SERVO_FWD  msToPulseLen(2.0) // This is the 'forward' pulse length count (out of 4096)
#define SERVO_REV  msToPulseLen(1.0) // This is the 'reverse' pulse length count (out of 4096)

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x44);

uint16_t msToPulseLen(float ms) {
  return (uint16_t)((ms * 1000) / 4.07 + 0.5);
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  delay(10);
}

void moveServo(uint8_t servonum) {
  pwm.setPWM(servonum, 0, SERVO_FWD);
  delay(2000); // Wait for 2 seconds
  pwm.setPWM(servonum, 0, SERVO_STOP);
  delay(2000); // Wait for 2 seconds
  pwm.setPWM(servonum, 0, SERVO_REV);
  delay(2000); // Wait for 2 seconds
  pwm.setPWM(servonum, 0, SERVO_STOP);
  delay(2000); // Wait for 2 seconds
}

void moveServosSequentially() {
  for (uint8_t servonum = 0; servonum < 4; servonum++) {
    moveServo(servonum);
  }
}

void loop() {
  moveServosSequentially();
}