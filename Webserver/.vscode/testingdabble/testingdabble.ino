/*
   Gamepad module provides three different mode namely Digital, JoyStick and Accerleometer.

   You can reduce the size of library compiled by enabling only those modules that you want to
   use. For this first define CUSTOM_SETTINGS followed by defining INCLUDE_modulename.

   Explore more on: https://thestempedia.com/docs/dabble/game-pad-module/
*/

//Code for dabble gamepad
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>
#include <ESP32Servo.h>
// Will's Code

#define SOUND_SPEED 0.034
const int trigPins[] = {19, 23};
const int echoPins[] = {21, 22};

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servos[] = {servo0, servo1, servo2, servo3};
const int servoPins[] = {18, 17, , };

long duration;
float startingDistances[] = {0, 0, 0, 0};
float distances[] = {0, 0, 0, 0};
auto = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      // make sure your Serial Monitor is also set at this baud rate.
  Dabble.begin("BLUECHEESE");       //set bluetooth name of your device
  
  //Initialises servos
  for (int i = 0; i < sizeof(servos) / sizeof(servos[0]); i++)
    {
        Serial.print("Servo: ");
        Serial.print(i);
        Serial.println();
        servos[i].attach(servoPins[i]);
    // 1500 is no movement  of the servo
    // 2000 is anti-clockwise movement of the servo == winding
    // 1000 is clockwise movement of the servo == unwinding
}
}

void loop() {
  if auto == false {
  Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
  Serial.print("KeyPressed: ");
  if (GamePad.isUpPressed())
  {
    Serial.print("Up");

    servos[0].writeMicroseconds(2000);
    delay(500);
  }

  if (GamePad.isDownPressed())
  {
    Serial.print("Down");
    
    servos[2].writeMicroseconds(2000);
    delay(500);
  }

  if (GamePad.isLeftPressed())
  {
    Serial.print("Left");

    servos[3].writeMicroseconds(2000);
    delay(500);
  }

  if (GamePad.isRightPressed())
  {
    Serial.print("Right");

    servos[1].writeMicroseconds(2000);
    delay(500);
  }

  if (GamePad.isSquarePressed())
  {
    Serial.print("Square");
  
    servos[3].writeMicroseconds(1000);
    delay(500);
  }

  if (GamePad.isCirclePressed())
  {
    Serial.print("Circle");

    servos[1].writeMicroseconds(1000);
    delay(500);
  }

  if (GamePad.isCrossPressed())
  {
    Serial.print("Cross");

    servos[2].writeMicroseconds(1000);
    delay(500);
  }

  if (GamePad.isTrianglePressed())
  {
    Serial.print("Triangle");

    servos[0].writeMicroseconds(1000);
    delay(500);
  }

  if (GamePad.isStartPressed())
  {
    Serial.print("Start");


  }

  if (GamePad.isSelectPressed())
  {
    Serial.print("Select");
    auto = !auto;


  }
  Serial.print('\t');

  int a = GamePad.getAngle();
  Serial.print("Angle: ");
  Serial.print(a);
  Serial.print('\t');
  int b = GamePad.getRadius();
  Serial.print("Radius: ");
  Serial.print(b);
  Serial.print('\t');
  float c = GamePad.getx_axis();
  Serial.print("x_axis: ");
  Serial.print(c);
  Serial.print('\t');
  float d = GamePad.gety_axis();
  Serial.print("y_axis: ");
  Serial.println(d);
  Serial.println();
}

if auto == true {

  for (int i = 0; i < sizeof(trigPins) / sizeof(trigPins[0]); i++)
    {
        distances[i] = getDistance(trigPins[i], echoPins[i]);

    }
    moveServo(0, 0, 1);
    moveServo(1, 1, 0);
    moveServo(2, 2, 3);
    moveServo(3, 3, 2);

    delay(10);

  
}

}
//
void moveServo(int servo, int distanceSensor, int backupSensor)
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
            Serial.print(servo);
            Serial.println();
            servos[servo].writeMicroseconds(2000);
            delay(500);
        }
        else
        {
            servos[servo].writeMicroseconds(1500);
            delay(500);
        }
    }

    else
    {
        servos[servo].writeMicroseconds(1500);
        delay(10);
    }
}

// this code is very shit dunno what im doing with it
// void move_servo_manual() {
//   Dabble.processInput();             //this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.
//   // Code to wind the servos manually
//   if (GamePad.isUpPressed())
//   {
//     servos[0].writeMicroseconds(2000);
//     delay(500);
//   }
//   if (GamePad.isRightPressed())
//   {
//     servos[1].writeMicroseconds(2000);
//     delay(500);
//   }
//   if (GamePad.isDownPressed())
//   {
//     servos[2].writeMicroseconds(2000);
//     delay(500);
//   }
//   if (GamePad.isLeftPressed())
//   {
//     servos[3].writeMicroseconds(2000);
//     delay(500);
//   }
//   // Code to unwind the servos manually
//   if (GamePad.isTrianglePressed())
//   {
//     servos[0].writeMicroseconds(1000);
//     delay(500);
//   }
//   if (GamePad.isCirclePressed())
//   {
//     servos[1].writeMicroseconds(1000);
//     delay(500);
//   }
//   if (GamePad.isCrossPressed())
//   {
//     servos[2].writeMicroseconds(1000);
//     delay(500);
//   }
//   if (GamePad.isSquarePressed())
//   {
//     servos[3].writeMicroseconds(1000);
//     delay(500);
//   }
// }