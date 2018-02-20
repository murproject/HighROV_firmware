#ifndef ROV_PAYLOADTOOL_H
#define ROV_PAYLOADTOOL_H


#include "RovDataStore.h"

namespace rov {

class PayloadTool {
  public:
    PayloadTool();

    virtual void init() = 0;

    virtual void update(const RovDataStore & store_) = 0;

    virtual void commit(RovDataStore & store_) = 0;

    ~PayloadTool();

};

} // namespace rov
#endif
