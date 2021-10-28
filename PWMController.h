#pragma once

#include <Wire.h>
#include <SparkFun_PCA9536_Arduino_Library.h>
#include <Servo.h>

class PWMController
{
public:
    enum Thrusters {
        horizontal_front_left = 0,
        horizontal_front_right,
        horizontal_back_left,
        horizontal_back_right,
        vertical_front,
        vertical_back,
    };

    enum CamServos {
        front = 0,
        back = 1,
    };

    static void init();
    static void set_servo(int idx, int angle);
    static void set_thruster(int idx, int power);
    static void set_manipulator(int ch, int power);
    PWMController(const PWMController&) = delete;
private:
    static PWMController &inst();
    PWMController();

    PCA9536 m_pca;

    Servo m_thrusters[6];
    Servo m_servos[2];
};

