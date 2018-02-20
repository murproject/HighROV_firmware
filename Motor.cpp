
#include "Motor.h"
#include <Arduino.h>
namespace rov {

Motor::Motor(uint8_t pin1, uint8_t pin2) :
		m_left(pin1), m_right(pin2)
	{


}

void Motor::init() {

		pinMode(m_left, OUTPUT);
		pinMode(m_right, OUTPUT);
}

void Motor::setPower(int8_t power) {

		if (power == 0) {
			setPin(LOW, LOW);
		}
		else if (power > 0) {
			setPin(LOW, HIGH);
		}
		else if (power < 0) {
			setPin(HIGH, LOW);
		}
}

Motor::~Motor(){

}

void Motor::setPin(int l, int r) {

		digitalWrite(m_left, l);
		digitalWrite(m_right, r);
}


} // namespace rov
