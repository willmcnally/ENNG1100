#include <ESP32Servo.h>

#define SOUND_SPEED 0.034
const int trigPins[] = {19, 23};
const int echoPins[] = {21, 22};

Servo servo1;
Servo servo2;
Servo servos[] = {servo1, servo2};
const int servoPins[] = {18, 17};

long duration;
float startingDistances[] = {0, 0, 0, 0};
float distances[] = {0, 0, 0, 0};

void setup()
{
    Serial.begin(115200); // Starts the serial communication

    // Initialize ultra sonic sensor and establish starting distance
    for (int i = 0; i < sizeof(trigPins) / sizeof(trigPins[0]); i++)
    {
        pinMode(trigPins[i], OUTPUT); // Sets the trigPin as an Output
        pinMode(echoPins[i], INPUT);  // Sets the echoPin as an Input

        duration = pulseIn(echoPins[i], HIGH);

        startingDistances[i] = duration * SOUND_SPEED / 2;
    }

    for (int i = 0; i < sizeof(servos) / sizeof(servos[0]); i++)
    {
          Serial.print("Servo: ");
        Serial.print(i);
        // Serial.print(" cm");
        Serial.println();
        servos[i].attach(servoPins[i]);
        //    servos[i].writeMicroseconds(2000);
        //    delay(1000);
    }
    // 1500 is no movement  of the servo
    // 2000 is anti-clockwise movement of the servo
    // 1000 is clockwise movement of the servo
}

void loop()
{

    for (int i = 0; i < sizeof(trigPins)/sizeof(trigPins[0]); i++)
    {
        distances[i] = getDistance(trigPins[i], echoPins[i]);
        // Serial.print("Distance: ");
        // Serial.print(distances[i]);
        // Serial.print(" cm");
        // Serial.println();
    }
    moveServo(0, 0, 1);
    moveServo(1, 1, 0);
    // moveServo(2, 2, 3);
    // moveServo(3, 3, 2);

    delay(10);
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

void moveServo(int servo, int distanceSensor, int backupSensor)
{
        float absolute = abs(abs(startingDistances[distanceSensor] - distances[distanceSensor]) - abs(distances[backupSensor] - startingDistances[backupSensor]));
        
        //If positive it is closer if negative it is further away
        float movement1 = startingDistances[distanceSensor] - distances[distanceSensor];
        
        float movement2 = startingDistances[backupSensor] - distances[backupSensor];
       
       //This checks that the position has moved 3cm from it's original position
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