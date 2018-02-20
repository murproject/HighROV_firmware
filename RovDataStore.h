#ifndef ROV_ROVDATASTORE_H
#define ROV_ROVDATASTORE_H


#include "RovDataTypes.h"

namespace rov {

class RovDataStore {
  public:
    RovDataStore();

    ~RovDataStore();

    void setTelimetry(const RovTelimetry & tel_);

    RovTelimetry & getTelimetry();

    const RovTelimetry & getTelimetry() const;

    void setControl(const RovControl & control_);

    RovControl & getControl();

    const RovControl & getControl() const;


  private:
    RovTelimetry m_telimetry;

    RovControl m_control;

};

} // namespace rov
#endif
