#include "NewPing.h"

// Motor directions
#define FRONT_DIRECTION 0
#define LEFT_DIRECTION 1
#define RIGHT_DIRECTION 2
#define BACK_DIRECTION 3

#define MIN_DISTANCE 6

// Ultrasonic pins
#define LEFT_TRIGGER 8
#define LEFT_ECHO 9
#define FRONT_TRIGGER 10
#define FRONT_ECHO 11
#define RIGHT_TRIGGER 12
#define RIGHT_ECHO 13

NewPing front(FRONT_TRIGGER, FRONT_ECHO, MAX_SENSOR_DISTANCE);
NewPing left(LEFT_TRIGGER, LEFT_ECHO, MAX_SENSOR_DISTANCE);
NewPing right(RIGHT_TRIGGER, RIGHT_ECHO, MAX_SENSOR_DISTANCE);

// MOTOR 1
#define ENA 2
#define IN1 3
#define IN2 4
// MOTOR 2
#define IN3 5
#define IN4 6
#define ENB 7

void setup() {
  Serial.begin(115200);

  // Setup motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}

int oldDirection = -1;

void loop() {
  delay(50);
  const int frontDistance = front.ping_cm();
  delay(50);
  const int leftDistance = left.ping_cm();
  delay(50);
  const int rightDistance = right.ping_cm();

  int maxDistance = 0;
  int direction = BACK_DIRECTION;

  if (frontDistance > MIN_DISTANCE) {
    maxDistance = frontDistance;
    direction = FRONT_DIRECTION;
  }
  if (leftDistance > maxDistance && leftDistance > MIN_DISTANCE) {
    maxDistance = leftDistance;
    direction = LEFT_DIRECTION;
  }
  if (rightDistance > maxDistance && rightDistance > MIN_DISTANCE) {
    maxDistance = rightDistance;
    direction = RIGHT_DIRECTION;
  }

  if (oldDirection == direction) { // Avoid send the same signal
    return;
  }

  oldDirection = direction;
  switch(direction) {
    case FRONT_DIRECTION:
      frontMotor();
      break;
    case LEFT_DIRECTION:
      leftMotor();
      break;
    case RIGHT_DIRECTION:
      rightMotor();
      break;
    case BACK_DIRECTION:
      backMotor();
      break;
  }
}


void frontMotor(){
 // MOTOR 1
  analogWrite (ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // MOTOR 2
  analogWrite(ENB, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void backMotor(){
 // MOTOR 1
  digitalWrite(ENA, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  digitalWrite(ENB, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void rightMotor(){
 // MOTOR 1
  analogWrite (ENA, 255);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  analogWrite (ENB, 255);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void leftMotor(){
 // MOTOR 1
  analogWrite (ENA, 255);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // MOTOR 2
  analogWrite (ENB, 255);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void stopMotor(){
 // MOTOR 1
  digitalWrite(ENA, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // MOTOR 2
  digitalWrite(ENB, 0);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}