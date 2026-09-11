# Obstacle Avoidance RC Car

An Arduino-based autonomous RC car that detects obstacles
using an HC-SR04 ultrasonic sensor and automatically changes
direction using a servo-mounted sensor.

## Features

- Autonomous obstacle detection
- Ultrasonic distance measurement
- Servo-based left/right scanning
- Automatic obstacle avoidance
- Forward and backward movement
- Left and right turning
- Serial Monitor debugging

## Hardware

- Arduino Uno
- L298N Motor Driver
- HC-SR04 Ultrasonic Sensor
- SG90 Servo Motor
- 2 × DC Motors
- RC Car Chassis
- Battery Pack

## Architecture

```text
              ┌─────────────────┐
              │   HC-SR04       │
              │ Ultrasonic      │
              └────────┬────────┘
                       │
                       ▼
              ┌─────────────────┐
              │   Arduino Uno   │
              │                 │
              │ Decision Logic  │
              └───────┬─────────┘
                      │
          ┌───────────┴───────────┐
          ▼                       ▼
 ┌─────────────────┐     ┌─────────────────┐
 │ Servo Scanner   │     │  L298N Driver   │
 └─────────────────┘     └────────┬────────┘
                                  │
                         ┌────────┴────────┐
                         ▼                 ▼
                    Left Motor       Right Motor
