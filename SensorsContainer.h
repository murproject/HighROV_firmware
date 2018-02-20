#ifndef ROV_SENSORSCONTAINER_H
#define ROV_SENSORSCONTAINER_H

#include "RovDataTypes.h"
#include "Sensor.h"
#include "AllSensors.h"
#include "RovMagics.h"
namespace rov {

class SensorsContainer {
  public:
    SensorsContainer();

    ~SensorsContainer();

    void init();

    void sensorsUpdate();

    void dataCommit(RovTelimetry & tel_);


  private:
    Sensor * m_sensors[SENSORS_SIZE];

};

} // namespace rov
#endif
