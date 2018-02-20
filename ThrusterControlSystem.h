#ifndef ROV_THRUSTERCONTROLSYSTEM_H
#define ROV_THRUSTERCONTROLSYSTEM_H


#include "Thruster.h"
#include "RovMagics.h"

#include "RovDataStore.h"

namespace rov {

class ThrusterControlSystem {
  public:
    ThrusterControlSystem();

    void init();

    virtual void update(const RovDataStore & store_);

    void commit(RovDataStore & store_);

    ~ThrusterControlSystem();

    Thruster * getHorizontal();

    Thruster * getVertical();


  private:
    Thruster m_horizontal[HORIZONTAL_THRUSTER_SIZE];

    Thruster m_vertical[VERTICAL_THRUSTER_SIZE];
	void debug_thruster(const RovControl &ctrl);
};

} // namespace rov
#endif
