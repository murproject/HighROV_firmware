#include "AnalogSensors.h"
#include "Config.h"
#include "Arduino.h"

void AnalogSensors::init() {
    using namespace config::analog;
    auto &sensors = inst();

    pinMode(voltmeter_pin, INPUT);
    pinMode(ammeter_pin, INPUT);
}

void AnalogSensors::update() {
    using namespace config::analog;

    int rawVoltage = analogRead(voltmeter_pin);
    int rawAmperage = analogRead(ammeter_pin);

    inst().m_voltage = round(rawVoltage / 0.6225) / 100.0; // TODO
    inst().m_amperage = rawAmperage; // TODO
}

double AnalogSensors::getVoltage() {
    return inst().m_voltage;
}

double AnalogSensors::getAmperage() {
    return inst().m_amperage;
}

AnalogSensors & AnalogSensors::inst() {
    static AnalogSensors controller;
    return controller;
}

AnalogSensors::AnalogSensors() {

}
