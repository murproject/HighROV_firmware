#ifndef ROV_PAYLOADSYSTEM_H
#define ROV_PAYLOADSYSTEM_H


#include "RovMagics.h"
#include "PayloadTool.h"

namespace rov {

class PayloadSystem {
  public:
    PayloadSystem();

    void init();

    void update(const RovDataStore & store_);

    void commit(RovDataStore & store_);

    ~PayloadSystem();


  private:
    PayloadTool * m_tools[PAYLOAD_SIZE];

};

} // namespace rov
#endif
