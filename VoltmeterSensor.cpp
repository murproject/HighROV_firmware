
#include "VoltmeterSensor.h"
#include "RovDataTypes.h"
#include "RovMagics.h"
namespace rov {

VoltmeterSensor::VoltmeterSensor() :
		m_pin(CurrentConfig::VOLTMETER_PIN), m_voltage(0)
{


}

VoltmeterSensor::~VoltmeterSensor(){

}

void VoltmeterSensor::init() {
	
}

void VoltmeterSensor::update() {

	m_voltage = analogRead(m_pin);
}

void VoltmeterSensor::commit(RovTelimetry & tel_) {

	tel_.voltmeter = m_voltage;
}


} // namespace rov
