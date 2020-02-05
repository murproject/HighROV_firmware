#include "DepthSensor.h"

void DepthSensor::init() {
    auto &ds = inst();
    ds.sensor.init();
    
    ds.sensor.setModel(MS5837::MS5837_30BA);
    ds.sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
}

float DepthSensor::get_depth() {
    auto &ds = inst();
    if ((millis() - ds.time_update) > 100) {
        ds.sensor.read();
        ds.time_update = millis();
        if (abs(ds.sensor.depth() - ds.depth) < 1) {
            ds.depth = ds.sensor.depth();
        }
    }
    return ds.depth;
}

DepthSensor & DepthSensor::inst() {
    static DepthSensor ds;
    return ds;
}
