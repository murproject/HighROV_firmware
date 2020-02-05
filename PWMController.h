#pragma once

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class PWMController
{
public:
    static void init();
    static void set_servo(int ch, int angle);
    static void set_thruster(int ch, int power);
    static void set_manipulator(int ch, int power);
    PWMController(const PWMController&) = delete;
private:
    static PWMController &inst();
    PWMController();
    Adafruit_PWMServoDriver m_pwm = Adafruit_PWMServoDriver();
};

