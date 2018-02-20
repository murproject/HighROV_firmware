#ifndef ROV_THRUSTER_H
#define ROV_THRUSTER_H


#include "MotorBase.h"
#include <Servo.h>

namespace rov {

class Thruster : public MotorBase {
  public:
    Thruster();

    void init(int control_pin_);

    ~Thruster();

    virtual void setPower(int8_t power);


  private:
    int m_control_pin;

    Servo m_out;

};

} // namespace rov
#endif
