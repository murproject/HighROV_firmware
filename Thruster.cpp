
#include "Thruster.h"
#include <Arduino.h>

namespace rov {

Thruster::Thruster(){

}

void Thruster::init(int control_pin_) {

		m_control_pin = control_pin_;
		m_out.attach(m_control_pin);
		setPower(0);
}

Thruster::~Thruster(){

		m_out.detach();
}

void Thruster::setPower(int8_t power) {

		power = constrain(power, -100, 100);
	//	Serial.println(power);
		uint16_t pulse = 1500 + (power * 5) * m_coef;
		pulse = constrain(pulse, 1000, 2000);
		m_out.writeMicroseconds(pulse);
}


} // namespace rov
