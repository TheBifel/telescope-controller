#include <Arduino.h>
#include <AccelStepper.h>

#define S1_PIN 12
#define S2_PIN 11
#define KEY_PIN 10
#define STEP_PIN 3
#define DIR_PIN 2
#define MS1_PIN 7
#define MS2_PIN 6

// Steps per revolution for the motor
const float stepsPerRevolution = 200;
int microstepSetting = 2;
float desiredRPM = 0;

AccelStepper stepper(AccelStepper::DRIVER, STEP_PIN, DIR_PIN);

int lastS1State = HIGH;
int encoderDirection = 0;  // 1 = CW, -1 = CCW
unsigned long lastTurnTime = 0;

void setup() {
  Serial.begin(115200);
  pinMode(S1_PIN, INPUT_PULLUP);
  pinMode(S2_PIN, INPUT_PULLUP);
  pinMode(KEY_PIN, INPUT_PULLUP);
  pinMode(MS1_PIN, OUTPUT);
  pinMode(MS2_PIN, OUTPUT);

  digitalWrite(MS1_PIN, HIGH);
  digitalWrite(MS2_PIN, LOW);

  float MaxRPM = 300;
  float Max_Speed_StepsPerSec = microstepSetting * stepsPerRevolution * MaxRPM / 60;
  stepper.setMaxSpeed(Max_Speed_StepsPerSec);
}

void loop() {
  int s1 = digitalRead(S1_PIN);
  int s2 = digitalRead(S2_PIN);
  int key = digitalRead(KEY_PIN);
  unsigned long currentTime = millis();

  int stepSize = (key == LOW) ? 10 : 1; // If button is pressed, change by 10 instead of 1

  if (currentTime - lastTurnTime > 5) {
    if (s1 != lastS1State) {
      lastTurnTime = currentTime;
      if (s1 == LOW) {
        encoderDirection = (s2 == HIGH) ? 1 : -1;
        desiredRPM += encoderDirection * stepSize;
        Serial.print("Speed: ");
        Serial.println(desiredRPM);
      }
    }
  }

  lastS1State = s1;

  if (desiredRPM == 0) {
    stepper.setSpeed(0);
  } else {
    float speedStepsPerSec = (microstepSetting * stepsPerRevolution * desiredRPM) / 60.0;
    stepper.setSpeed(speedStepsPerSec);
  }

  stepper.runSpeed();
}
