// PathFinder-Bot: Autonomous Line Following Robot using PID Control
// Author: Fenil Finava
// Description: This code controls an autonomous robot that follows a line using a
// 6-sensor IR array, an L298N motor driver, and PID logic.

// --- PID Configuration ---
float Kp = 4.0;
float Ki = 0.001;
float Kd = 2.0;

// Motor speeds
int baseSpeed = 65;
int maxSpeed = 150; // Maximum speed for motors

// --- Pin Assignments ---
// Motor A (Right)
const int ENA = 5;
const int IN1 = 8;
const int IN2 = 9;

// Motor B (Left)
const int ENB = 10;
const int IN3 = 7;
const int IN4 = 6;

// Sensor pins (from left to right)
const int sensorPins[6] = {13, 12, 11, 4, 3, 2};
int sensorValues[6];

// PID Variables
float error = 0, lastError = 0;
float P = 0, I = 0, D = 0, PIDvalue = 0;
bool lineDetected = false;

void setup() {
  Serial.begin(9600);

  // Initialize motor pins
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Initialize sensor pins
  for (int i = 0; i < 6; i++) {
    pinMode(sensorPins[i], INPUT);
  }

  // Pre-startup delay for stability
  delay(1000);
}

void loop() {
  readSensors();

  if (lineDetected) {
    calculatePID();
    motorControl();
  } else {
    // If no line is detected, stop the motors
    // You can also add logic here to search for the line
    stopMotors();
  }
}

void readSensors() {
  lineDetected = false;
  int activeSensors = 0;
  float weightedSum = 0;

  // Read sensors and calculate error based on their positions
  // Assuming a black line on a white background (sensor reads 1 on black)
  for (int i = 0; i < 6; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
    if (sensorValues[i] == HIGH) { // Change to LOW if white line on black
      lineDetected = true;
      activeSensors++;
      // Assign weights to sensors: e.g., -5, -3, -1, 1, 3, 5
      float weight = (i - 2.5) * 2; 
      weightedSum += weight;
    }
  }

  if (activeSensors > 0) {
    error = weightedSum / activeSensors;
  }
}

void calculatePID() {
  P = error;
  I = I + error;
  D = error - lastError;

  // Anti-windup for integral term
  if (I > 50) I = 50;
  if (I < -50) I = -50;

  PIDvalue = (Kp * P) + (Ki * I) + (Kd * D);
  lastError = error;
}

void motorControl() {
  int leftMotorSpeed = baseSpeed + PIDvalue;
  int rightMotorSpeed = baseSpeed - PIDvalue;

  // Constrain speeds to allowable ranges
  leftMotorSpeed = constrain(leftMotorSpeed, 0, maxSpeed);
  rightMotorSpeed = constrain(rightMotorSpeed, 0, maxSpeed);

  // Move forward with adjusted speeds
  analogWrite(ENA, rightMotorSpeed);
  analogWrite(ENB, leftMotorSpeed);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void stopMotors() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
