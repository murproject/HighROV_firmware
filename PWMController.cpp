#include "PWMController.h"
#include "Config.h"

/*

for (int i = 0; i < 4; i++) {
    m_pca.digitalWrite(i, HIGH);
}

digitalWrite(LED_BUILTIN, HIGH);
delay(200);

for (int i = 0; i < 4; i++) {
    m_pca.digitalWrite(i, LOW);
}

digitalWrite(LED_BUILTIN, LOW);
delay(200);
SerialUSB.println("loop!");

*/

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

    pwm.m_servos[config::servos::front].attach(servo_front_pin);
    pwm.m_servos[config::servos::back].attach(servo_back_pin);

    delay(10);
}

void PWMController::set_servo(int idx, int angle) {
    int pulse = map(angle, 0, 180, 1000, 2000);
    inst().m_servos[idx].writeMicroseconds(pulse);
}

void PWMController::set_thruster(int idx, int power) {
    int pulse = map(power, -100, 100, 1000, 2000);
    pulse = constrain(pulse, 1000, 2000);

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

PWMController & PWMController::inst() {
    static PWMController pwm;
    return pwm;
}

PWMController::PWMController() {

}

