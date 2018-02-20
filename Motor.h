#ifndef ROV_MOTOR_H
#define ROV_MOTOR_H


#include "MotorBase.h"
#include <stdint.h>
namespace rov {

class Motor : public MotorBase {
  public:
    Motor(uint8_t pin1, uint8_t pin2);

    void init();

    virtual void setPower(int8_t power);

    ~Motor();


  private:
    uint8_t m_left;

    uint8_t m_right;

    void setPin(int l, int r);

};

} // namespace rov
#endif
