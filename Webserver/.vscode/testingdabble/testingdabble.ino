/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/

// Code for dabble gamepad
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Will's Code

#define SERVO_STOP msToPulseLen(1.65) // This is the 'stop' pulse length count (out of 4096)
#define SERVO_FWD msToPulseLen(2.0)   // This is the 'forward' pulse length count (out of 4096)
#define SERVO_REV msToPulseLen(1.0)   // This is the 'reverse' pulse length count (out of 4096)
#define SOUND_SPEED 0.034
const int trigPins[] = {19, 23};
const int echoPins[] = {21, 22};

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x44);

Servo servo0;
// Servo servo1;
// Servo servo2;
// Servo servo3;
// Servo servos[] = {servo0, servo1, servo2, servo3};
Servo servos[] = {servo0};
// const int servoPins[] = {23, 19, 5, 18};
// const int servoPins[] = {23};

long duration;
float startingDistances[] = {0, 0, 0, 0};
float distances[] = {0, 0, 0, 0};
bool autostate = false;

uint16_t msToPulseLen(float ms)
{
  return (uint16_t)((ms * 1000) / 4.07 + 0.5);
}

void setup()
{
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz updates
  delay(10);
  // put your setup code here, to run once:
  Serial.begin(115200);       // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("BLUECHEESE"); // set bluetooth name of your device
  for (int i = 0; i < sizeof(trigPins) / sizeof(trigPins[0]); i++)
  {
    pinMode(trigPins[i], OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPins[i], INPUT);  // Sets the echoPin as an Input

    duration = pulseIn(echoPins[i], HIGH);

    startingDistances[i] = duration * SOUND_SPEED / 2;
  }
  // Initialises servos
  // for (int i = 0; i < sizeof(servos) / sizeof(servos[0]); i++)
  //   {
  //       Serial.print("Servo: ");
  //       Serial.print(i);
  //       Serial.println();
  //       servos[i].attach(servoPins[i]);
  // 1500 is no movement  of the servo
  // 2000 is anti-clockwise movement of the servo == winding
  // 1000 is clockwise movement of the servo == unwinding
  // }
}

void moveServo(uint8_t servonum, uint8_t servo_dir)
{
  if (servo_dir == 1)
  {
    pwm.setPWM(servonum, 0, SERVO_FWD);
    delay(200); // Wait for 2 seconds
    pwm.setPWM(servonum, 0, SERVO_STOP);
    delay(10); // Wait for 2 seconds
  }
  else if (servo_dir == 2)
  {
    pwm.setPWM(servonum, 0, SERVO_REV);
    delay(200); // Wait for 2 seconds
    pwm.setPWM(servonum, 0, SERVO_STOP);
    delay(10); // Wait for 2 seconds
  }
  else if (servo_dir == 3)
  {
    pwm.setPWM(servonum, 0, SERVO_STOP);
    delay(10); // Wait for 2 seconds
  }
}

float getDistance(int trigPin, int echoPin)
{
  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  return duration * SOUND_SPEED / 2;
}

void moveServoAUTO(uint8_t servonum, int distanceSensor, int backupSensor)
{
  float absolute = abs(abs(startingDistances[distanceSensor] - distances[distanceSensor]) - abs(distances[backupSensor] - startingDistances[backupSensor]));

  // If positive it is closer if negative it is further away
  float movement1 = startingDistances[distanceSensor] - distances[distanceSensor];

  float movement2 = startingDistances[backupSensor] - distances[backupSensor];

  // This checks that the position has moved 3cm from it's original position
  if (movement1 > 4)
  {

    if (movement2 < 3)
    {
      Serial.print("This is running on servo: ");
      Serial.print(servonum);
      Serial.println();
      moveServo(servonum, 1); // move forward
      delay(500);
    }
    else
    {
      moveServo(servonum, 3); // stop
      delay(500);
    }
  }

  else
  {
    moveServo(servonum, 3); // stop
    delay(10);
  }
}

void loop()
{
  Dabble.processInput(); // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  if (autostate == false)
  {
    Serial.print("KeyPressed: ");
    if (GamePad.isUpPressed())
    {
      Serial.print("Up");

      moveServo(0, 1);
      delay(100);
    }

    if (GamePad.isDownPressed())
    {
      Serial.print("Down");

      moveServo(2, 1);
      delay(100);
    }

    if (GamePad.isLeftPressed())
    {
      Serial.print("Left");

      moveServo(3, 1);
      delay(100);
    }

    if (GamePad.isRightPressed())
    {
      Serial.print("Right");

      moveServo(1, 1);
      delay(100);
    }

    if (GamePad.isSquarePressed())
    {
      Serial.print("Square");

      moveServo(3, 2);
      delay(100);
    }

    if (GamePad.isCirclePressed())
    {
      Serial.print("Circle");

      moveServo(1, 2);
      delay(100);
    }

    if (GamePad.isCrossPressed())
    {
      Serial.print("Cross");

      moveServo(2, 2);
      delay(100);
    }

    if (GamePad.isTrianglePressed())
    {
      Serial.print("Triangle");

      moveServo(0, 2);
      delay(100);
    }

    if (GamePad.isStartPressed())
    {
      Serial.print("Start");
    }

    if (GamePad.isSelectPressed())
    {
      Serial.print("Select");
      autostate = !autostate;
    }
    // formatting for the serial prints
    Serial.print('\t');
    Serial.println();
  }

  else if (autostate == true)
  {
    Serial.print("Entering Auto Mode");
    Serial.println();
    // code to change the autostate function, which should switch between servos's on/off <|:3
    if (GamePad.isStartPressed())
    {
      Serial.print("Activated Manual Mode");
      autostate = !autostate;
    }

    for (int i = 0; i < sizeof(trigPins) / sizeof(trigPins[0]); i++) // ngl i dunno wtf this code does but it works i guess
    {
      distances[i] = getDistance(trigPins[i], echoPins[i]);
    }
    // this should move the servos automatically. hopefully
    moveServoAUTO(0, 0, 1);
    moveServoAUTO(1, 1, 0);
    moveServoAUTO(2, 2, 3);
    moveServoAUTO(3, 3, 2);

    delay(10);
  }
}