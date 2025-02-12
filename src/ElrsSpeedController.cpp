#include "ElrsSpeedController.h"


ElrsSpeedController::ElrsSpeedController(int rxPin, int txPin)
    : crsfSerial(1) {
    crsfSerial.begin(CRSF_BAUDRATE, SERIAL_8N1, rxPin, txPin);
    if (!crsfSerial) {
        while (1) Serial.println("Invalid CRSF serial configuration");
    }

    crsf.begin(crsfSerial);
}

void ElrsSpeedController::refresh() {
    crsf.update();
}

float ElrsSpeedController::getRpmForChannel(int channel, int maxRPM) {
    int pulse = crsf.getChannel(channel);

    // Noise Filtering: Ignore small fluctuations around 1500
    if (pulse >= 1499 && pulse <= 1501) {
        pulse = 1500;
    } else if (pulse > 2000) {
        pulse = 2000;
    } else if (pulse < 1000) {
        pulse = 1000;
    }

    if (!crsf.isLinkUp()) {
        pulse = 1500;
    }

    int pwmCenter = 1500;
    int pwmRange = 500;
    int pwmValue = pulse - pwmCenter;

    // Apply a parabolic response curve
    float normalized = (float)pwmValue / pwmRange;  // Normalize to -1.0 to 1.0
    return maxRPM * (normalized * abs(normalized)); // Quadratic scaling
}
