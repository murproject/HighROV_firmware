#include "PWMController.h"

#include "Config.h"
void PWMController::init() {
    auto &pwm = inst();
    pwm.m_pwm.begin();
    pwm.m_pwm.setOscillatorFrequency(27000000);
    pwm.m_pwm.setPWMFreq(config::pwm::pwm_freq);  

    delay(10);
}

void PWMController::set_servo(int ch, int angle) {
    double pulse = map(angle, 0, 180, 1000, 2000);
    inst().m_pwm.writeMicroseconds(ch, pulse);
}

void PWMController::set_thruster(int ch, int power) {
    double pulse = map(power, -100, 100, 990, 1990);
    pulse = constrain(pulse, 1000, 2000);
    inst().m_pwm.writeMicroseconds(ch, pulse);
}

void PWMController::set_manipulator(int ch, int power) {
    int16_t pulse = map(abs(power), 0, 100, 0, 4096);
    inst().m_pwm.setPWM(ch, pulse, false);
}

PWMController & PWMController::inst() {
    static PWMController pwm;
    return pwm;
}

PWMController::PWMController() {
}

