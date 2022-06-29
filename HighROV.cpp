#include "HighROV.h"
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

rov::RovControl control;
rov::RovTelemetry Telemetry;
int manip_pos = -20;
long long t_lm = 0;
bool link_dead_notification = false;
bool link_up_notification = false;

void HighROV::init() {
    SerialUSB.println("HighROV init!");

    pinMode(LED_BUILTIN, OUTPUT);
    analogWrite(LED_BUILTIN, 100);

    PWMController::init();
    Networking::init();
    Thrusters::init();
    RotaryCameras::init();
    DepthSensor::init();
    Manipulator::init();
    IMUSensor::init();
    AnalogSensors::init();

    delay(3000);
}

void debug(rov::RovControl &ctrl) {
    using namespace config;

    PWMController::set_thruster(thrusters::horizontal_front_left,  ctrl.thrusterPower[0]);
    PWMController::set_thruster(thrusters::horizontal_front_right, ctrl.thrusterPower[1]);
    PWMController::set_thruster(thrusters::horizontal_back_left,   ctrl.thrusterPower[2]);
    PWMController::set_thruster(thrusters::horizontal_back_right,  ctrl.thrusterPower[3]);
    PWMController::set_thruster(thrusters::vertical_front,         ctrl.thrusterPower[4]);
    PWMController::set_thruster(thrusters::vertical_back,          ctrl.thrusterPower[5]);

    PWMController::set_servo_power(servos::front,  ctrl.thrusterPower[6]);
    PWMController::set_servo_power(servos::back,   ctrl.thrusterPower[7]);
    PWMController::set_servo_power(servos::pwm_a2, ctrl.thrusterPower[8]);
    PWMController::set_servo_power(servos::pwm_a3, ctrl.thrusterPower[9]);
}

void gracefulReset(){
  SerialUSB.end();
  Wire.end();
  IMUSensor::end();
  NVIC_SystemReset();
}

void serialHandler(){
  if(SerialUSB.available()){
    String msg = SerialUSB.readString();
    msg.trim();
    SerialUSB.print(msg=="reset" ? "Resetting the controller, it will explode in 3 seconds" : "");
    if(msg=="reset")
      gracefulReset();
  }
}

void HighROV::run() {
    using namespace config;
    using namespace pwm;
    serialHandler();
    AnalogSensors::update();
    if (Ethernet.linkStatus() == LinkON && !link_up_notification) {
      SerialUSB.println("Link status: On");
      link_up_notification = true;
      link_dead_notification = false;
    }
    else if (Ethernet.linkStatus() == LinkOFF && !link_dead_notification) {
      SerialUSB.println("Link status: Off. This usually indicates problems w/cable");
      link_dead_notification = true;
      link_up_notification = false;
    }
    if (millis() >= t_lm + 500){
      byte status = Ethernet.maintain();
      switch(status){
        case 0:
          break;
        case 1:
          SerialUSB.println("DHCP lease renew failed, check the configuration of your DHCP server");
          break;
        case 2:
          SerialUSB.println("DHCP lease renew success");
          break;
        case 3:
          SerialUSB.println("DHCP rebind failed, check the configuration of your DHCP server");
          break;
        case 4:
          SerialUSB.println("DHCP rebind detected, this may break things");
          break;
        default:
          break;
      }
      t_lm = millis();
    }
//    SerialUSB.println(String(millis()));
    

    Telemetry.yaw = IMUSensor::getYaw();
    Telemetry.roll = IMUSensor::getRoll();
    Telemetry.pitch = IMUSensor::getPitch();
    Telemetry.depth = DepthSensor::getDepth();
    Telemetry.temperature = DepthSensor::getTemp();
    Telemetry.ammeter = AnalogSensors::getAmperage();
    Telemetry.voltmeter = AnalogSensors::getVoltage();
    Telemetry.cameraIndex = RotaryCameras::get_cam_index();

    // SerialUSB.print("\tDepth: "); SerialUSB.print(Telemetry.depth);
    // SerialUSB.print("\tTemp: "); SerialUSB.print(Telemetry.temperature);
    // delay(50);

    // // SerialUSB.print("\tYaw: "); SerialUSB.print(Telemetry.yaw);
    // // SerialUSB.print("\tRoll: "); SerialUSB.print(Telemetry.roll);
    // // SerialUSB.print("\tPitch: "); SerialUSB.print(Telemetry.pitch);
    // SerialUSB.println();

    Networking::read_write_udp(Telemetry, control);
    if (!control.debugFlag) {
        Thrusters::update_thrusters(control, Telemetry);

        RotaryCameras::set_angle(config::servos::front, constrain(control.cameraRotation[0], -1, 1) * 3.0);
        RotaryCameras::set_angle(config::servos::back,  constrain(control.cameraRotation[1], -1, 1) * 3.0);
        RotaryCameras::select_cam(control.cameraIndex == 1 ? true : false);

        int manip_speed = 100;
        manip_pos += control.manipulatorOpenClose*10;
        manip_pos = constrain(manip_pos, -100, 100);
                
        PWMController::set_thruster(7, manip_pos);

//        Manipulator::set_power(control.manipulatorRotation, control.manipulatorOpenClose);
    } else {
        debug(control);
    }

    if (DepthSensor::getUpdateStatus() == true) {
        analogWrite(LED_BUILTIN, sin(millis() * 0.01) * 127 + 127);
    } else {
        analogWrite(LED_BUILTIN, 255);
    }

    delay(20);
}
