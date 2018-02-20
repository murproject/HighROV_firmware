#ifndef ROV_MANIPULATORPAYLOAD_H
#define ROV_MANIPULATORPAYLOAD_H


#include "PayloadTool.h"
#include "Motor.h"
#include <stdint.h>
#include "RovDataStore.h"

namespace rov {

class ManipulatorPayload : public PayloadTool {
  public:
    ManipulatorPayload();

    virtual void init();

    virtual void update(const RovDataStore & store_);

    virtual void commit(RovDataStore & store_);

    ~ManipulatorPayload();


  private:
    Motor m_axisX;

    Motor m_axisY;

    int8_t m_valX;

    int8_t m_valY;

};

} // namespace rov
#endif
