#include <Servo.h>

// =========================
// Pin Configuration
// =========================

// Motor Driver
#define ENA 5
#define IN1 7
#define IN2 8

#define ENB 6
#define IN3 9
#define IN4 10

// Ultrasonic Sensor
#define TRIG 12
#define ECHO 11

// Servo
#define SERVO_PIN 4

// =========================
// Configuration
// =========================

#define OBSTACLE_DISTANCE 20

#define FORWARD_SPEED 200
#define BACKWARD_SPEED 180
#define TURN_SPEED 200

#define SCAN_CENTER 90
#define SCAN_LEFT 150
#define SCAN_RIGHT 30

// =========================
// Global Variables
// =========================

Servo scanner;

long duration;
int distance;

// =========================
// Setup
// =========================

void setup() {

  Serial.begin(9600);

  // Motor pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Ultrasonic
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  // Servo
  scanner.attach(SERVO_PIN);
  scanner.write(SCAN_CENTER);

  stopCar();

  delay(1000);
}

// =========================
// Main Loop
// =========================

void loop() {

  scanner.write(SCAN_CENTER);
  delay(100);

  distance = getDistance();

  Serial.print("Front Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance > OBSTACLE_DISTANCE) {

    moveForward();

  } else {

    avoidObstacle();
  }
}

// =========================
// Obstacle Avoidance
// =========================

void avoidObstacle() {

  stopCar();
  delay(300);

  moveBackward();
  delay(300);

  stopCar();
  delay(300);

  // Scan left
  scanner.write(SCAN_LEFT);
  delay(500);

  int leftDistance = getDistance();

  // Scan right
  scanner.write(SCAN_RIGHT);
  delay(500);

  int rightDistance = getDistance();

  // Center scanner
  scanner.write(SCAN_CENTER);
  delay(300);

  Serial.print("Left: ");
  Serial.print(leftDistance);

  Serial.print(" cm | Right: ");
  Serial.print(rightDistance);

  Serial.println(" cm");

  if (leftDistance > rightDistance) {

    turnLeft();
    delay(500);

  } else {

    turnRight();
    delay(500);
  }

  stopCar();
  delay(100);
}

// =========================
// Ultrasonic
// =========================

int getDistance() {

  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0) {
    return 400;
  }

  return duration * 0.034 / 2;
}

// =========================
// Motor Control
// =========================

void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, FORWARD_SPEED);
  analogWrite(ENB, FORWARD_SPEED);
}

void moveBackward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, BACKWARD_SPEED);
  analogWrite(ENB, BACKWARD_SPEED);
}

void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
}

void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);
}

void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}
