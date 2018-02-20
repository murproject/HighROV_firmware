#pragma once
#include "Sensor.h"
#include "MS5837.h"
namespace rov {
	class DepthSensor : public Sensor
	{
	public:
		DepthSensor();
		~DepthSensor();
		void init();
		void update();
		void commit(RovTelimetry &tel_);
		float getDepth() const;
	private:
		rovlibs::MS5837 m_sensor;
	};

}