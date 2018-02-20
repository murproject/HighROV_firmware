#ifndef ROV_REGULATOR_H
#define ROV_REGULATOR_H

#include <stdint.h>
#include "RovDataStore.h"

namespace rov {

class Regulator {
  public:
    Regulator();

    virtual void setParams(float disaredParms_);

    virtual void calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_) = 0;

    ~Regulator();


  protected:
    float m_disaredParams;

};
class HPilotRegulator : public Regulator {
  public:
    HPilotRegulator();

    virtual void calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_);

    ~HPilotRegulator();

};
class VPilotRegulator : public Regulator {
  public:
    VPilotRegulator();

    virtual void calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_);

    ~VPilotRegulator();

};
class AutoDepthRegulator : public Regulator {
  public:
    AutoDepthRegulator();

    virtual void calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_);

    ~AutoDepthRegulator();


  private:
    float m_previos_depth;

};

} // namespace rov
#endif
