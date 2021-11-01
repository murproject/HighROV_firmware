#include "Thrusters.h"
#include "PWMController.h"
#include "Config.h"


void Thrusters::init() {
    using namespace config::thrusters;

    PWMController::set_thruster(horizontal_front_left, 0);
    PWMController::set_thruster(horizontal_front_right, 0);
    PWMController::set_thruster(horizontal_back_left, 0);
    PWMController::set_thruster(horizontal_back_right, 0);
    PWMController::set_thruster(vertical_front, 0);
    PWMController::set_thruster(vertical_back, 0);

    PWMController::set_thruster(custom_1, 0);
    PWMController::set_thruster(custom_2, 0);
}

void Thrusters::update_thrusters(rov::RovControl &ctrl, rov::RovTelimetry & tel) {
    using namespace config::thrusters;

    {
        const int16_t y = ctrl.axisY;
        const int16_t x = ctrl.axisX;
        const int16_t w = ctrl.axisW;
        auto &data = inst();

        PWMController::set_thruster(horizontal_front_left, data.directions[0] * constrain(y + x + w, -100, 100));
        PWMController::set_thruster(horizontal_front_right, data.directions[1] * constrain(y - x - w, -100, 100));
        PWMController::set_thruster(horizontal_back_left, data.directions[2] * constrain(y - x + w, -100, 100));
        PWMController::set_thruster(horizontal_back_right, data.directions[3] * constrain(y + x - w, -100, 100));
    }

    {
        auto &data = inst();
        PWMController::set_thruster(vertical_front, constrain(data.directions[4] * ctrl.axisZ,-100,100));
        PWMController::set_thruster(vertical_back, constrain(data.directions[5] * ctrl.axisZ, -100, 100));
    }
}

Thrusters & Thrusters::inst() {
    static Thrusters th;
    return th;
}
