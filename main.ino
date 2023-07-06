#include <Servo.h>
#include <NewPing.h>

// Pin Definitions
const int LEFT_MOTOR_FORWARD = 7;
const int LEFT_MOTOR_BACKWARD = 6;
const int RIGHT_MOTOR_FORWARD = 4;
const int RIGHT_MOTOR_BACKWARD = 5;

const int TRIG_PIN = A1;
const int ECHO_PIN = A2;

const int MAXIMUM_DISTANCE = 200;

// Constants for servo motor positions
const int SERVO_CENTER = 115;
const int SERVO_RIGHT = 50;
const int SERVO_LEFT = 170;

// Variables
NewPing sonar(TRIG_PIN, ECHO_PIN, MAXIMUM_DISTANCE);
Servo servoMotor;

// Function Prototypes
void stop();
void moveForward();
void moveBackward();
void turnRight();
void turnLeft();
int getDistance();
void lookDirection(int angle);

void setup() {
  pinMode(LEFT_MOTOR_FORWARD, OUTPUT);
  pinMode(LEFT_MOTOR_BACKWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_FORWARD, OUTPUT);
  pinMode(RIGHT_MOTOR_BACKWARD, OUTPUT);
  
  servoMotor.attach(10);

  servoMotor.write(SERVO_CENTER);
  delay(2000);
  
  for (int i = 0; i < 4; i++) {
    getDistance();
    delay(100);
  }
}

void loop() {
  int distance = getDistance();

  if (distance <= 20) {
    stop();
    delay(300);
    moveBackward();
    delay(400);
    stop();
    delay(300);

    int distanceRight = getDistance();
    delay(300);

    int distanceLeft = getDistance();
    delay(300);

    if (distance >= distanceLeft) {
      turnRight();
      stop();
    } else {
      turnLeft();
      stop();
    }
  } else {
    moveForward();
  }
}

int getDistance() {
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void lookDirection(int angle) {
  servoMotor.write(angle);
  delay(500);
}

void stop() {
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void moveForward() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}

void moveBackward() {
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void turnRight() {
  digitalWrite(LEFT_MOTOR_FORWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_BACKWARD, HIGH);
  digitalWrite(LEFT_MOTOR_BACKWARD, LOW);
  digitalWrite(RIGHT_MOTOR_FORWARD, LOW);
}

void turnLeft() {
  digitalWrite(LEFT_MOTOR_BACKWARD, HIGH);
  digitalWrite(RIGHT_MOTOR_FORWARD, HIGH);
  digitalWrite(LEFT_MOTOR_FORWARD, LOW);
  digitalWrite(RIGHT_MOTOR_BACKWARD, LOW);
}
