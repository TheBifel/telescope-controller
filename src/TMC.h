#ifndef TMC_H
#define TMC_H

#include <Arduino.h>
#include <AccelStepper.h>

class TMC {
public:
    TMC(int stepPin, int directionPin, int ms1Pin, int ms2Pin, int microstep);
    void setSpeed(float desiredRPM);
    void configureMicrostepping(int microstep); //2, 4, 8, 16
    void setMaxRPM(int maxRPM);
    int getMaxRPM();

private:
    int ms1Pin, ms2Pin;
    int microstepMultiplier;
    int maxRPM;
    AccelStepper stepper;
};

#endif // TMC_H
