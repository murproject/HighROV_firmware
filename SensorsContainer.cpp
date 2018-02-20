#include "SensorsContainer.h"
#include "RovMagics.h"

namespace rov {
	SensorsContainer::SensorsContainer()
	{
		m_sensors[0] = new IMUSensor();
		m_sensors[1] = new VoltmeterSensor();
		m_sensors[2] = new AmmeterSensor();
		m_sensors[3] = new DepthSensor();
	}

	SensorsContainer::~SensorsContainer()
	{
		for (int i = 0; i < SENSORS_SIZE; ++i) {
			delete m_sensors[i];
		}
	}

	void SensorsContainer::init()
	{
		for (int i = 0; i < SENSORS_SIZE; ++i) {
			m_sensors[i]->init();
		}
	}

	void SensorsContainer::sensorsUpdate()
	{
		for (int i = 0; i < SENSORS_SIZE; ++i) {
			m_sensors[i]->update();
		}
	}

	void SensorsContainer::dataCommit(RovTelimetry & tel_)
	{
		for (int i = 0; i < SENSORS_SIZE; ++i) {
			m_sensors[i]->commit(tel_);
		}
	}

}