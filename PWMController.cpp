#include "PWMController.h"
#include "Config.h"

#include "src/SAMD_ISR_Servo/SAMD_ISR_Servo.h"

void PWMController::init() {
    using namespace config::pwm;
    using namespace config;

    auto &pwm = inst();

    SAMD_ISR_Servos.useTimer(TIMER_TCC);

    pwm.m_pins[thrusters::horizontal_front_left]  = th_horizontal_front_left_pin;
    pwm.m_pins[thrusters::horizontal_front_right] = th_horizontal_front_right_pin;
    pwm.m_pins[thrusters::horizontal_back_left]   = th_horizontal_back_left_pin;
    pwm.m_pins[thrusters::horizontal_back_right]  = th_horizontal_back_right_pin;
    pwm.m_pins[thrusters::vertical_front]         = th_vertical_front_pin;
    pwm.m_pins[thrusters::vertical_back]          = th_vertical_back_pin;
    pwm.m_pins[thrusters::servo_front]            = servo_front_pin;
    pwm.m_pins[thrusters::servo_back]             = servo_back_pin;
    pwm.m_pins[thrusters::pwm_0]                  = pwm_custom_0_pin;
    pwm.m_pins[thrusters::pwm_1]                  = pwm_custom_1_pin;
    pwm.m_pins[thrusters::pwm_2]                  = pwm_custom_2_pin;
    pwm.m_pins[thrusters::pwm_3]                  = pwm_custom_3_pin;


    for (int i = 0; i < 12; i++) {
        pwm.m_servos[i] = SAMD_ISR_Servos.setupServo(pwm.m_pins[i], pulse_min, pulse_max);
    }

    SAMD_ISR_Servos.setReadyToRun();

    for (int i = 0; i < 12; i++) {
        SAMD_ISR_Servos.setPulseWidth(pwm.m_servos[i], pulse_med);
    }

    if (pwm.m_pca.begin() == false) {
        SerialUSB.println("ERROR: PCA9536 not detected! Check I2C connection.");
    }

    for (int i = 0; i < 4; i++) {
        pwm.m_pca.pinMode(i, OUTPUT);
        pwm.m_pca.write(i, LOW);
    }

    pinMode(config::pwm::cam_select_pin, OUTPUT);

    delay(10);
}

void PWMController::set_servo(int idx, int angle) {
    int pulse = map(angle, 0, 180, 1010, 1990);
    pulse = constrain(pulse, 1010, 1990);
    SAMD_ISR_Servos.setPulseWidth(inst().m_servos[idx], pulse);
    // SAMD_ISR_Servos.setPulseWidth(inst().m_pins[idx], pulse);
    // inst().m_servos[idx].write(angle);
}

void PWMController::set_thruster(int idx, int power) {
    int pulse = map(power, -100, 100, 1010, 1990);
    pulse = constrain(pulse, 1010, 1990);
    // inst().m_thrusters[idx].writeMicroseconds(pulse);
    SAMD_ISR_Servos.setPulseWidth(inst().m_servos[idx], pulse);
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

