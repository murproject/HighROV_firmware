#include "Arduino.h"
#include "DepthSensor.h"
#include "Wire.h"

void DepthSensor::init() {
    auto &ds = inst();
    bool ok = ds.sensor.init();

    if (!ok) {
        SerialUSB.println("Depth sensor init failed!"); // TODO //
        return;
    }

    ds.sensor.setModel(MS5837::MS5837_30BA);
    ds.sensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
}

float DepthSensor::get_depth() {
    auto &ds = inst();
    if ((millis() - ds.time_update) > 200) {
        ds.sensor.read();
        ds.time_update = millis();
        if (abs(ds.sensor.depth()) < 150) {
            ds.depth = ds.sensor.depth();
        } else { // don't accept value if value is too big (probably corrupted data)
            SerialUSB.println("\n\nDepth sensor fatality.\n\n"); // TODO //
            Wire.end();
            Wire.begin(); // TODO?
            Wire.setTimeout(1000);
            Wire.setClock(10000);

            init();
        }
    }

    if ((millis() - ds.time_update) > 5000) {
        // init(); // TODO; delete?
    }
    return ds.depth;
}

DepthSensor & DepthSensor::inst() {
    static DepthSensor ds;
    return ds;
}
