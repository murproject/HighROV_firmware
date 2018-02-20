#ifndef ROV_AMPERMETERSENSOR_H
#define ROV_AMPERMETERSENSOR_H


#include "Sensor.h"
#include <stdint.h>
#include "RovDataTypes.h"

namespace rov {

class AmmeterSensor : public Sensor {
  public:
	 AmmeterSensor();

    ~AmmeterSensor();

    virtual void init();

    virtual void update();

    virtual void commit(RovTelimetry & tel_);


  private:
    uint8_t m_pin;

    int m_amp;

};

} // namespace rov
#endif
