#include "RotaryCameras.h"
#include "Config.h"
#include "PWMController.h"

void RotaryCameras::init() {
    auto &data = inst();
    PWMController::set_servo(config::servos::front, data.angles[0]);
    PWMController::set_servo(config::servos::back, data.angles[1]);
}

void RotaryCameras::set_angle(int idx, int angle) {
    int servo_idx = (idx == 0) ? config::servos::front : config::servos::back;
    auto &data = inst();

    if ((millis() - data.times_update[idx]) > 17) {
        data.times_update[idx] = millis();
        data.angles[idx] += angle;
        data.angles[idx] = constrain(data.angles[idx], 0, 180);
        PWMController::set_servo(servo_idx, data.angles[servo_idx]);
    }
}

RotaryCameras & RotaryCameras::inst() {
    static RotaryCameras rc;
    return rc;
}
