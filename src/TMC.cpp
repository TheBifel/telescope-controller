#include "TMC.h"

TMC::TMC(int stepPin, int directionPin, int ms1Pin, int ms2Pin)
    : stepper(AccelStepper::DRIVER, stepPin, directionPin),
      ms1Pin(ms1Pin), ms2Pin(ms2Pin) {

    pinMode(ms1Pin, OUTPUT);
    pinMode(ms2Pin, OUTPUT);

    setMaxRPM(400);
}

void TMC::setMaxRPM(int maxRPM) {
    stepper.setMaxSpeed(microstepMultiplier * 200 * maxRPM / 60);
    this->maxRPM = maxRPM;
}
int TMC::getMaxRPM() {
    return maxRPM;
}

void TMC::configureMicrostepping(int microstep) {
    microstepMultiplier = microstep;

    switch (microstep) {
        case 2: digitalWrite(ms1Pin, HIGH); digitalWrite(ms2Pin, LOW); break;//10
        case 4: digitalWrite(ms1Pin, LOW); digitalWrite(ms2Pin, HIGH); break;//20sec
        case 8: digitalWrite(ms1Pin, LOW); digitalWrite(ms2Pin, LOW); break;//20
        case 16: digitalWrite(ms1Pin, HIGH); digitalWrite(ms2Pin, HIGH); break;//80
        default: digitalWrite(ms1Pin, HIGH); digitalWrite(ms2Pin, LOW); microstepMultiplier = 2; break;
    }
}

void TMC::setSpeed(float desiredRPM) {
    if (desiredRPM == 0) {
        stepper.setSpeed(0);
    } else {
        float speedStepsPerSec = (microstepMultiplier * 200 * desiredRPM) / 60.0;
        stepper.setSpeed(speedStepsPerSec);
    }
    
    stepper.runSpeed();
}

