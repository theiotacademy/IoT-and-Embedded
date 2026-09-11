# Hardware Overview

The project uses an Arduino Uno to control a two-wheel
drive RC car.

## System

HC-SR04
   │
   ▼
Arduino Uno
   │
   ├── Servo
   │
   └── L298N
         │
         ├── Left Motor
         └── Right Motor

The ultrasonic sensor measures the distance in front of
the vehicle.

When an obstacle is detected:

1. The car stops.
2. The car moves backward.
3. The servo scans left.
4. The servo scans right.
5. The Arduino compares both distances.
6. The car turns toward the side with more free space.
7. The car continues forward.
