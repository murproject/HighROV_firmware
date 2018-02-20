#ifndef ROV_SENSOR_H
#define ROV_SENSOR_H

#include "RovDataTypes.h"


namespace rov {

class Sensor {
  public:
    Sensor();

    virtual void init() = 0;

    virtual void update() = 0;

    virtual void commit(RovTelimetry & tel_) = 0;

    ~Sensor();

};

} // namespace rov
#endif
