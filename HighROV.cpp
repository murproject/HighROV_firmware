#include "HighROV.h"
#include "WiFiUpdater.h"
#include "PWMController.h"
#include "Networking.h"
#include "Data.h"
#include "Thrusters.h"
#include "RotaryCameras.h"
#include "DepthSensor.h"
#include "Manipulator.h"
#include "Config.h"

rov::RovControl control;
rov::RovTelimetry telimetry;


void HighROV::init() {
    Serial.println("HighROV init");
    WiFiUpdater::init();
    PWMController::init();
    Networking::init();
    Thrusters::init();
    RotaryCameras::init();
    DepthSensor::init();
    Manipulator::init();
    delay(7000);

}

void debug(rov::RovControl &ctrl) {
    using namespace config::pwm;
    PWMController::set_thruster(left_front_horizontal_ch, ctrl.thrusterPower[0]);
    PWMController::set_thruster(right_front_horizontal_ch, ctrl.thrusterPower[1]);
    PWMController::set_thruster(left_back_horizontal_ch, ctrl.thrusterPower[2]);
    PWMController::set_thruster(right_back_horizontal_ch, ctrl.thrusterPower[3]);
    PWMController::set_thruster(front_vertical_ch, ctrl.thrusterPower[4]);
    PWMController::set_thruster(back_vertical_ch, ctrl.thrusterPower[5]);
}


void HighROV::run() {  
    WiFiUpdater::check_updates();
    Networking::read_write_udp(telimetry, control);
    if (!control.debugFlag) {
        Thrusters::update_thrusters(control, telimetry);
        RotaryCameras::set_angle(0, constrain(control.cameraRotation[0], -1, 1));
        RotaryCameras::set_angle(1, constrain(control.cameraRotation[1], -1, 1));
        Manipulator::set_power(control.manipulatorRotation, control.manipulatorOpenClose);
    } else {
        debug(control);
    }

    telimetry.depth = DepthSensor::get_depth();
}
