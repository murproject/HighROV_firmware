#pragma once

#include <Wire.h>
#include <SparkFun_PCA9536_Arduino_Library.h>
#include <Servo.h>

class PWMController
{
public:

    static void init();
    static void set_servo(int idx, int angle);
    static void set_thruster(int idx, int power);
    static void set_manipulator(int ch, int power);
    static void set_video_multiplexer(bool state);
    PWMController(const PWMController&) = delete;
private:
    static PWMController &inst();
    PWMController();

    PCA9536 m_pca;

    Servo m_thrusters[10];
    Servo m_servos[2];
};

