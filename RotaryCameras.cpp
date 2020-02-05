#include "RotaryCameras.h"
#include "Config.h"
#include "PWMController.h"

void RotaryCameras::init() {
    auto &data = inst();
    PWMController::set_servo(config::pwm::servo_front_ch, data.angles[0]);
    PWMController::set_servo(config::pwm::servo_back_ch, data.angles[1]);
}

void RotaryCameras::set_angle(int idx, int angle) {
    int ch = (idx == 0) ? config::pwm::servo_front_ch : config::pwm::servo_back_ch;
    auto &data = inst();

    if ((millis() - data.times_update[idx]) > 17) {
        data.times_update[idx] = millis();
        data.angles[idx] += angle;
        data.angles[idx] = constrain(data.angles[idx], 0, 180);
        PWMController::set_servo(ch, data.angles[idx]);
    }
}

RotaryCameras & RotaryCameras::inst() {
    static RotaryCameras rc;
    return rc;
}
