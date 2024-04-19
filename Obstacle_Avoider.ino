#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h>

#define TRIG_PIN A0
#define ECHO_PIN A5
#define MAX_DISTANCE 200
#define MAX_SPEED 180 // sets speed of DC motors
#define MAX_SPEED_OFFSET 20

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

AF_DCMotor right(4, MOTOR12_1KHZ);
AF_DCMotor left(1, MOTOR12_1KHZ);

Servo servo;

boolean goesForward = false;
int distance = 100;
int speedSet = 0;

void setup() {
  servo.attach(10);
  servo.write(115);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop() {
  int distanceR = 0;
  int distanceL = 0;
  delay(40);

  if(distance <= 15) {
    moveStop();
    delay(100);
    moveBackward();
    delay(300);
    moveStop();
    delay(200);
    distanceR = lookRight();
    delay(200);
    distanceL = lookLeft();
    delay(200);
    
    if(distanceR >= distanceL) {
      turnRight();
      moveStop();      } 
    else {
      turnLeft();
      moveStop();
    }
  } else {
    moveForward();
  }
  distance = readPing();
}

int lookRight() {
  servo.write(50);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(115);
  return distance;
}

int lookLeft() {
  servo.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo.write(115);
  return distance;
  delay(100);
}

int readPing() {
  delay(70);
  int cm = sonar.ping_cm();
  if(cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  right.run(RELEASE);
  left.run(RELEASE);
}

void moveForward() {
  if(!goesForward) {
    goesForward = true;
    right.run(FORWARD);
    left.run(FORWARD);
    for(speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
      right.setSpeed(speedSet);
      left.setSpeed(speedSet);
      delay(5);
    }
  }
}

void moveBackward() {
  goesForward = false;
  right.run(BACKWARD);
  left.run(BACKWARD);
  for(speedSet = 0; speedSet < MAX_SPEED; speedSet += 2) {
    right.setSpeed(speedSet);
    left.setSpeed(speedSet);
    delay(5);
  }
}

void turnRight() {
  right.run(BACKWARD);
  left.run(FORWARD);
  delay(500);
  right.run(FORWARD);
  left.run(FORWARD);
}

void turnLeft() {
  right.run(FORWARD);
  left.run(BACKWARD);
  delay(500);
  right.run(FORWARD);
  left.run(FORWARD);
}