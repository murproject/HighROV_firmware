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
#include "AnalogSensors.h"

// IMUSensor imu;
rov::RovControl control;
rov::RovTelimetry telimetry;

void HighROV::init() {
    SerialUSB.println("HighROV init! (SerialUSB)");
    Serial.println("HighROV init");

    // pinMode(PIN_PA13, OUTPUT);

    // while (true) {
    //     digitalWrite(PIN_PA13, HIGH);
    //     delay(1);
    //     digitalWrite(PIN_PA13, LOW);
    //     delay(1);
    // }

    // WiFiUpdater::init();
    PWMController::init();
    Networking::init();
    Thrusters::init();
    RotaryCameras::init();
    DepthSensor::init();
    Manipulator::init();
    IMUSensor::init();
    AnalogSensors::init();

    // delay(5000);
}

void debug(rov::RovControl &ctrl) {
    using namespace config::thrusters;

    PWMController::set_thruster(horizontal_front_left,  ctrl.thrusterPower[0]);
    PWMController::set_thruster(horizontal_front_right, ctrl.thrusterPower[1]);
    PWMController::set_thruster(horizontal_back_left,   ctrl.thrusterPower[2]);
    PWMController::set_thruster(horizontal_back_right,  ctrl.thrusterPower[3]);
    PWMController::set_thruster(vertical_front,         ctrl.thrusterPower[4]);
    PWMController::set_thruster(vertical_back,          ctrl.thrusterPower[5]);

    PWMController::set_thruster(pwm_0, ctrl.thrusterPower[6]);
    PWMController::set_thruster(pwm_1, ctrl.thrusterPower[7]);
    PWMController::set_thruster(pwm_2, ctrl.thrusterPower[8]);
    PWMController::set_thruster(pwm_3, ctrl.thrusterPower[9]);
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

    PWMController::set_thruster(config::thrusters::pwm_0, p);
    PWMController::set_thruster(config::thrusters::pwm_1, p);
    PWMController::set_thruster(config::thrusters::pwm_2, p);
    PWMController::set_thruster(config::thrusters::pwm_3, p);

    int angle = (counter % 200) > 100 ? 2 : -2;

    RotaryCameras::set_angle(config::servos::front, angle);
    RotaryCameras::set_angle(config::servos::back, angle);

    int manip_p = p / 5 >  10 ?  1 :
                  p / 5 < -10 ? -1 : 0;

    Manipulator::set_power(manip_p, manip_p);

    // if (counter % 10 == 0) {
    //     SerialUSB.print(p);
    //     SerialUSB.print("\t");
    //     SerialUSB.println(manip_p);/
    // }

    // SerialUSB.println(p);

    // PIN_PA13;

    // delay(30);
}

void HighROV::run() {

    /* TODO: A2, A3 - thrusters */


    // test_peripherals();
    // imu.update();

    // SerialUSB.print("Yaw: ");
    // SerialUSB.print(IMUSensor::inst().getYaw());
    // SerialUSB.print("\tPitch: ");
    // SerialUSB.print(IMUSensor::inst().getRoll());
    // SerialUSB.print("\tRoll: ");
    // SerialUSB.print(IMUSensor::inst().getPitch());

    // // digitalWrite(LED_BUILTIN, HIGH);
    // // delay(5);
    // // digitalWrite(LED_BUILTIN, LOW);
    // // delay(5);

    // SerialUSB.print("\tDepth: ");
    // SerialUSB.println(DepthSensor::get_depth());



    // SerialUSB.println(p);

    // WiFiUpdater::check_updates();

    telimetry.yaw = IMUSensor::getYaw();
    telimetry.roll = IMUSensor::getRoll();
    telimetry.pitch = IMUSensor::getPitch();
    telimetry.depth = DepthSensor::get_depth();
    telimetry.voltmeter = AnalogSensors::getVoltage();
    telimetry.cameraIndex = RotaryCameras::get_cam_index();

    Networking::read_write_udp(telimetry, control);
    if (!control.debugFlag) {
        Thrusters::update_thrusters(control, telimetry);
        RotaryCameras::set_angle(0, constrain(control.cameraRotation[0], -1, 1));
        RotaryCameras::set_angle(1, constrain(control.cameraRotation[1], -1, 1));
        RotaryCameras::select_cam(control.cameraIndex == 1 ? true : false);
        Manipulator::set_power(control.manipulatorRotation, control.manipulatorOpenClose);
        SerialUSB.print(control.manipulatorOpenClose); SerialUSB.print("\t");\
        SerialUSB.print(control.regulators); SerialUSB.print("\t");
        SerialUSB.print(control.desiredDepth); SerialUSB.print("\t");
        SerialUSB.print(control.cameraIndex); SerialUSB.print("\t");
        SerialUSB.println(" ");
    } else {
        // SerialUSB.println("debugging!");
        debug(control);
    }

    delay(20);


    // imu.processImu();
    // telimetry.yaw = imu.get_yaw();
    // telimetry.roll = imu.get_roll();
    // telimetry.pitch = imu.get_pitch();
}

