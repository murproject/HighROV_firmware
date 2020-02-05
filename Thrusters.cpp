#include "Thrusters.h"
#include "PWMController.h"
#include "Config.h"


void Thrusters::init() {
    PWMController::set_thruster(config::pwm::left_front_horizontal_ch, 0);
    PWMController::set_thruster(config::pwm::right_front_horizontal_ch, 0);
    PWMController::set_thruster(config::pwm::left_back_horizontal_ch, 0);
    PWMController::set_thruster(config::pwm::right_back_horizontal_ch, 0);
    PWMController::set_thruster(config::pwm::front_vertical_ch, 0);
    PWMController::set_thruster(config::pwm::back_vertical_ch, 0);
}

void Thrusters::update_thrusters(rov::RovControl &ctrl, rov::RovTelimetry & tel) {
    {
        const int16_t y = ctrl.axisY;
        const int16_t x = ctrl.axisX;
        const int16_t w = ctrl.axisW;
        auto &data = inst();

        PWMController::set_thruster(config::pwm::left_front_horizontal_ch, data.directions[0] * constrain(y + x + w, -100, 100));
        PWMController::set_thruster(config::pwm::right_front_horizontal_ch, data.directions[1] * constrain(y - x - w, -100, 100));
        PWMController::set_thruster(config::pwm::left_back_horizontal_ch, data.directions[2] * constrain(y - x + w, -100, 100));
        PWMController::set_thruster(config::pwm::right_back_horizontal_ch, data.directions[3] * constrain(y + x - w, -100, 100));
    }

    {
        auto &data = inst();
        PWMController::set_thruster(config::pwm::front_vertical_ch, constrain(data.directions[4] * ctrl.axisZ,-100,100));
        PWMController::set_thruster(config::pwm::back_vertical_ch, constrain(data.directions[5] * ctrl.axisZ, -100, 100));
    }
}

Thrusters & Thrusters::inst() {
    static Thrusters th;
    return th;
}
