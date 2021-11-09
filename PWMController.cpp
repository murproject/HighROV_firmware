#include "PWMController.h"
#include "Config.h"


void PWMController::init() {
    using namespace config::pwm;

    auto &pwm = inst();

    if (pwm.m_pca.begin() == false) {
        SerialUSB.println("ERROR: PCA9536 not detected! Check I2C connection.");
    }

    for (int i = 0; i < 4; i++) {
        pwm.m_pca.pinMode(i, OUTPUT);
        pwm.m_pca.write(i, LOW);
    }

    pwm.m_thrusters[config::thrusters::horizontal_front_left].attach(th_horizontal_front_left_pin);
    pwm.m_thrusters[config::thrusters::horizontal_front_right].attach(th_horizontal_front_right_pin);
    pwm.m_thrusters[config::thrusters::horizontal_back_left].attach(th_horizontal_back_left_pin);
    pwm.m_thrusters[config::thrusters::horizontal_back_right].attach(th_horizontal_back_right_pin);
    pwm.m_thrusters[config::thrusters::vertical_front].attach(th_vertical_front_pin);
    pwm.m_thrusters[config::thrusters::vertical_back].attach(th_vertical_back_pin);

    pwm.m_thrusters[config::thrusters::pwm_0].attach(pwm_custom_0_pin);
    pwm.m_thrusters[config::thrusters::pwm_1].attach(pwm_custom_1_pin);
    pwm.m_thrusters[config::thrusters::pwm_2].attach(pwm_custom_2_pin);
    pwm.m_thrusters[config::thrusters::pwm_3].attach(pwm_custom_3_pin);

    pwm.m_servos[config::servos::front].attach(servo_front_pin);
    pwm.m_servos[config::servos::back].attach(servo_back_pin);

    pinMode(config::pwm::cam_select_pin, OUTPUT);

    delay(10);
}

void PWMController::set_servo(int idx, int angle) {
    angle = constrain(angle, 0, 180);
    inst().m_servos[idx].write(angle);
}

void PWMController::set_thruster(int idx, int power) {
    int pulse = map(power, -100, 100, 1010, 1990);
    pulse = constrain(pulse, 1010, 1990);
    inst().m_thrusters[idx].writeMicroseconds(pulse);
}

void PWMController::set_manipulator(int ch, int power) {
    PinStatus state = LOW;

    if (abs(power) >= 50) {
        state = HIGH;
    }

    inst().m_pca.write(ch, state);

    /* TODO: try to emulate PWM on this chip to set manipulator power level */
    // int16_t pulse = map(abs(power), 0, 100, 0, 4096);
}

void PWMController::set_video_multiplexer(bool state) {
    digitalWrite(config::pwm::cam_select_pin, state);
}

PWMController & PWMController::inst() {
    static PWMController pwm;
    return pwm;
}

PWMController::PWMController() {

}

