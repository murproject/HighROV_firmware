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
#include "IMUSensor.h"
#include "USB/USBAPI.h"

Imu::IMUSensor imu;
rov::RovControl control;
rov::RovTelimetry telimetry;

void HighROV::init() {
    SerialUSB.println("HighROV init! (SerialUSB)");
    Serial.println("HighROV init");

    // WiFiUpdater::init();
    PWMController::init();
    Networking::init();
    Thrusters::init();
    RotaryCameras::init();
    DepthSensor::init();
    Manipulator::init();
    imu.init();

    // delay(5000);
}

void debug(rov::RovControl &ctrl) {
    using namespace config::thrusters;

    PWMController::set_thruster(horizontal_front_left, ctrl.thrusterPower[0]);
    PWMController::set_thruster(horizontal_front_right, ctrl.thrusterPower[1]);
    PWMController::set_thruster(horizontal_back_left, ctrl.thrusterPower[2]);
    PWMController::set_thruster(horizontal_back_right, ctrl.thrusterPower[3]);
    PWMController::set_thruster(vertical_front, ctrl.thrusterPower[4]);
    PWMController::set_thruster(vertical_back, ctrl.thrusterPower[5]);
}

void test_peripherals() {
    static uint64_t counter = 0;
    counter++;

    int p = (counter % 200) - 100;

    PWMController::set_thruster(config::thrusters::horizontal_front_left, p);
    PWMController::set_thruster(config::thrusters::horizontal_front_right, p);
    PWMController::set_thruster(config::thrusters::horizontal_back_left, p);
    PWMController::set_thruster(config::thrusters::horizontal_back_right, p);
    PWMController::set_thruster(config::thrusters::vertical_front, p);
    PWMController::set_thruster(config::thrusters::vertical_back, p);

    int angle = (counter % 200) > 100 ? 2 : -2;

    RotaryCameras::set_angle(config::servos::front, angle);
    RotaryCameras::set_angle(config::servos::back, angle);

    int manip_p = p >  50 ?  1 :
                  p < -50 ? -1 : 0;

    Manipulator::set_power(manip_p, manip_p);

    // if (counter % 10 == 0) {
    //     SerialUSB.print(p);
    //     SerialUSB.print("\t");
    //     SerialUSB.println(manip_p);
    // }

    // SerialUSB.println(p);

    // delay(30);
}

void HighROV::run() {
    test_peripherals();
    imu.update();

    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(10);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(10);

    SerialUSB.print("Depth: ");
    SerialUSB.println(DepthSensor::get_depth());

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

