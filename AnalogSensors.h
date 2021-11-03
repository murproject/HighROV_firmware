#pragma once

class AnalogSensors {
public:
    static void init();
    static void update();

    static double getVoltage();
    static double getAmperage();

    AnalogSensors(const AnalogSensors&) = delete;

private:
    AnalogSensors();
    static AnalogSensors &inst();
    double m_voltage = 0.0;
    double m_amperage = 0.0;

};
