#include "AmpermeterSensor.h"
#include "RovMagics.h"
#include <Arduino.h>
#include "RovDataTypes.h"

namespace rov {
	AmmeterSensor::AmmeterSensor() :
		m_pin(CurrentConfig::AMPERMETER_PIN),
		m_amp(0)
	{
	}


	AmmeterSensor::~AmmeterSensor()
	{

	}

	void AmmeterSensor::init()
	{

	}

	void AmmeterSensor::update()
	{
		m_amp = analogRead(m_pin);
	}

	void AmmeterSensor::commit(RovTelimetry & tel_)
	{
		tel_.ammeter = m_amp;
	}
}