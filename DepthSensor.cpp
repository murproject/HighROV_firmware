#include "DepthSensor.h"
#include <Wire.h>
namespace rov {

	DepthSensor::DepthSensor()
	{
		
	}


	DepthSensor::~DepthSensor()
	{
	}

	void DepthSensor::init()
	{
		Wire.begin();
		m_sensor.init();
		m_sensor.setModel(rovlibs::MS5837::MS5837_30BA);
		m_sensor.setFluidDensity(997); // kg/m^3 (997 freshwater, 1029 for seawater)
	}

	void DepthSensor::update()
	{
		m_sensor.read();
	}

	void DepthSensor::commit(RovTelimetry & tel_)
	{
		tel_.depth = m_sensor.depth();
		//sSerial.println(tel_.depth);
	}

	float DepthSensor::getDepth() const
	{
		return 0;
	}

}