#include "Arduino.h"
#include "TMC.h"
#include "ElrsSpeedController.h"

#define PIN_RX 16
#define PIN_TX 18

TMC stepper1(5, 3, 9, 7); // stepPin, directionPin, ms1Pin, ms2Pin, microstep
TMC stepper2(39, 37, 33, 35); // stepPin, directionPin, ms1Pin, ms2Pin, microstep
ElrsSpeedController elrs(PIN_RX, PIN_TX);

void setup() {
    Serial.begin(115200);
    stepper1.setMaxRPM(300);
    stepper2.setMaxRPM(300);
    stepper1.configureMicrostepping(2);
    stepper2.configureMicrostepping(2);
}

void loop() {
    elrs.refresh();
    float desiredRPM1 = elrs.getRpmForChannel(1, stepper1.getMaxRPM());
    float desiredRPM2 = elrs.getRpmForChannel(2, stepper2.getMaxRPM());

    Serial.print("Ch1 PWM to RPM: ");
    Serial.print(desiredRPM1);
    Serial.print(" Ch2 PWM to RPM: ");
    Serial.println(desiredRPM2);

    stepper1.setSpeed(desiredRPM1);
    stepper2.setSpeed(desiredRPM2);
}
