#include "HighROV.h"
// #include "WiFiUpdater.h"
#include "PWMController.h"
#include "Networking.h"
#include "Data.h"
#include "Thrusters.h"
#include "RotaryCameras.h"
#include "DepthSensor.h"
#include "Manipulator.h"
#include "Config.h"
#include "ImuSensor.h"
#include "USB/USBAPI.h"

ImuSensor imu;
rov::RovControl control;
rov::RovTelimetry telimetry;

void HighROV::init() {
    SerialUSB.println("HighROV init! (SerialUSB)");
    Serial.println("HighROV init");

    // WiFiUpdater::init();
    PWMController::init();
    // Networking::init();
    // Thrusters::init();
    RotaryCameras::init();
    // DepthSensor::init();
    Manipulator::init();
    // imu.init();
    // delay(3000);
}

void debug(rov::RovControl &ctrl) {
    // using namespace config::pwm;
    // PWMController::set_thruster(left_front_horizontal_ch, ctrl.thrusterPower[0]);
    // PWMController::set_thruster(right_front_horizontal_ch, ctrl.thrusterPower[1]);
    // PWMController::set_thruster(left_back_horizontal_ch, ctrl.thrusterPower[2]);
    // PWMController::set_thruster(right_back_horizontal_ch, ctrl.thrusterPower[3]);
    // PWMController::set_thruster(front_vertical_ch, ctrl.thrusterPower[4]);
    // PWMController::set_thruster(back_vertical_ch, ctrl.thrusterPower[5]);
}


void HighROV::run() {
    static uint64_t counter = 0;
    counter++;
    // SerialUSB.println(counter);
    // delay(200);

    int p = (counter % 200) - 100;

    PWMController::set_thruster(PWMController::Thrusters::horizontal_front_left, p);
    PWMController::set_thruster(PWMController::Thrusters::horizontal_front_right, p);
    PWMController::set_thruster(PWMController::Thrusters::horizontal_back_left, p);
    PWMController::set_thruster(PWMController::Thrusters::horizontal_back_right, p);
    PWMController::set_thruster(PWMController::Thrusters::vertical_front, p);
    PWMController::set_thruster(PWMController::Thrusters::vertical_back, p);

    int angle = (counter % 200) > 100 ? 2 : -2;

    RotaryCameras::set_angle(PWMController::CamServos::front, angle);
    RotaryCameras::set_angle(PWMController::CamServos::back, angle);

    int manip_p = p >  50 ?  1 :
                  p < -50 ? -1 : 0;

    Manipulator::set_power(manip_p, manip_p);

    SerialUSB.println(manip_p);

    delay(10);

    // SerialUSB.println(p);

    // WiFiUpdater::check_updates();

    // Networking::read_write_udp(telimetry, control);
    // if (!control.debugFlag) {
    //     Thrusters::update_thrusters(control, telimetry);
    //     RotaryCameras::set_angle(0, constrain(control.cameraRotation[0], -1, 1));
    //     RotaryCameras::set_angle(1, constrain(control.cameraRotation[1], -1, 1));
    //     Manipulator::set_power(control.manipulatorRotation, control.manipulatorOpenClose);
    // } else {
    //     debug(control);
    // }

    // telimetry.depth = DepthSensor::get_depth();

    // imu.processImu();
    // telimetry.yaw = imu.get_yaw();
    // telimetry.roll = imu.get_roll();
    // telimetry.pitch = imu.get_pitch();
}

