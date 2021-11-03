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
    /* TODO: delete? */
}

double AnalogSensors::getVoltage() {
    using namespace config::analog;
    int rawVoltage = analogRead(voltmeter_pin);
    inst().m_voltage = round(rawVoltage / 0.6225) / 100.0; // TODO
    return inst().m_voltage;
}

double AnalogSensors::getAmperage() {
    /* TODO: Ammeter → should support different ACS725 sensors (CTR-20, CTR-30, CTR-40…) */
    using namespace config::analog;
    int rawAmperage = analogRead(ammeter_pin);
    inst().m_amperage = rawAmperage; // TODO
    return inst().m_amperage;
}

AnalogSensors & AnalogSensors::inst() {
    static AnalogSensors controller;
    return controller;
}

AnalogSensors::AnalogSensors() {

}
