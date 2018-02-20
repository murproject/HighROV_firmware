
#include "ManipulatorPayload.h"
#include "RovDataStore.h"
#include "RovMagics.h"

namespace rov {

ManipulatorPayload::ManipulatorPayload() :
		m_axisX(ManipulatorConfig::AXISX_PIN1, ManipulatorConfig::AXISX_PIN2),
		m_axisY(ManipulatorConfig::AXISY_PIN1, ManipulatorConfig::AXISY_PIN2),
		m_valX(0), m_valY(0)
	{

}

void ManipulatorPayload::init() {

		m_axisX.init();
		m_axisY.init();
}

void ManipulatorPayload::update(const RovDataStore & store_) {

		int valX = store_.getControl().manipulatorOpenClose;
		int valY = store_.getControl().manipulatorRotation;
		
		m_axisX.setPower(valX);
		m_axisY.setPower(valY);
}

void ManipulatorPayload::commit(RovDataStore & store_) {

		store_.getTelimetry().manipulatorAngle = m_valY;
		store_.getTelimetry().manipulatorState = m_valX;
}

ManipulatorPayload::~ManipulatorPayload(){

}


} // namespace rov
