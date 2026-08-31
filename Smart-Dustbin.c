#include <Servo.h>

#define TRIG_PIN   9
#define ECHO_PIN  10
#define SERVO_PIN  6

#define OPEN_DISTANCE_CM 30   // hand closer than this -> lid opens
#define LID_CLOSED_ANGLE  0
#define LID_OPEN_ANGLE   90
#define OPEN_HOLD_MS   3000   // keep lid open this long

Servo lidServo;

long readDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // timeout 30 ms (~5 m) so the loop never blocks forever
  long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
  if (duration == 0) return -1;          // no echo
  return duration * 0.0343 / 2;          // speed of sound -> cm
}

void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  lidServo.attach(SERVO_PIN);
  lidServo.write(LID_CLOSED_ANGLE);
  delay(500);
}

void loop() {
  long distance = readDistanceCM();
  Serial.print("Distance: ");
  Serial.println(distance);

  if (distance > 0 && distance <= OPEN_DISTANCE_CM) {
    lidServo.write(LID_OPEN_ANGLE);   // open lid
    delay(OPEN_HOLD_MS);
    lidServo.write(LID_CLOSED_ANGLE); // close lid
    delay(500);
  }
  delay(100);
}
