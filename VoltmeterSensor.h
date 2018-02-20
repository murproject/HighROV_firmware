#ifndef ROV_VOLTMETERSENSOR_H
#define ROV_VOLTMETERSENSOR_H


#include "Sensor.h"



namespace rov {

class VoltmeterSensor : public Sensor {
  public:
    VoltmeterSensor();

    ~VoltmeterSensor();

    virtual void init();

    virtual void update();

    virtual void commit(RovTelimetry & tel_);


  private:
    uint8_t m_pin;

    int m_voltage;

};

} // namespace rov
#endif
