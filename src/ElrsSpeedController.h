#ifndef ELRS_SPEED_CONTROLLER_H
#define ELRS_SPEED_CONTROLLER_H

#include <Arduino.h>
#include <AlfredoCRSF.h>
#include <HardwareSerial.h>

class ElrsSpeedController {
public:
    ElrsSpeedController(int rxPin, int txPin);
    void refresh();
    float getRpmForChannel(int channel, int maxRPM);

private:
    AlfredoCRSF crsf;
    HardwareSerial crsfSerial;
};

#endif
