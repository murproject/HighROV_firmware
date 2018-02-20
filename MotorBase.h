#ifndef ROV_MOTORBASE_H
#define ROV_MOTORBASE_H

#include <stdint.h>
namespace rov {

class MotorBase {
  public:
    MotorBase();

    ~MotorBase();

    virtual void setPower(int8_t power) = 0;

    void setProportionalCoeff(float coef);


  protected:
    float m_coef;

};

} // namespace rov
#endif
