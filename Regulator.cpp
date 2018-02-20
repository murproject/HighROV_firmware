
#include "Regulator.h"
#include "RovDataStore.h"
#include <stdint.h>
#include "RovMagics.h"
namespace rov {

Regulator::Regulator(){

}

void Regulator::setParams(float disaredParms_) {

		m_disaredParams = disaredParms_;
}

Regulator::~Regulator(){

}

HPilotRegulator::HPilotRegulator(){

}

void HPilotRegulator::calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_) {

		int16_t y = store_.getControl().axisY;
		int16_t x = store_.getControl().axisX;
		int16_t w = store_.getControl().axisW;

		pthr_[HorizontalThruster::FRONT_LEFT] = constrain(y + x + w, -100, 100);
		pthr_[HorizontalThruster::FRONT_RIGHT] = constrain(y - x - w, -100, 100);
		pthr_[HorizontalThruster::BACK_LEFT] = constrain(y - x + w, -100, 100);
		pthr_[HorizontalThruster::BACK_RIGHT] = constrain(y + x - w, -100, 100);
}

HPilotRegulator::~HPilotRegulator(){

}

VPilotRegulator::VPilotRegulator(){

}

void VPilotRegulator::calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_) {

		for (int i = 0; i < size_; i++) {
			pthr_[i] = store_.getControl().axisZ;
		}
}

VPilotRegulator::~VPilotRegulator(){

}

AutoDepthRegulator::AutoDepthRegulator() : m_previos_depth(0.0f)
	{

}

void AutoDepthRegulator::calculate(const RovDataStore & store_, int8_t * pthr_, uint32_t size_) {

		float pwr = 0;
		float Kp = 3.14;
		float kd = 0.3;
		float err = (store_.getControl().desiredDepth - store_.getTelimetry().depth);

		pwr = err * Kp;
		pwr += ((err - (store_.getControl().desiredDepth - m_previos_depth)) * kd);

		for (int i = 0; i < size_; i++) {
			pthr_[i] = pwr;
		}
}

AutoDepthRegulator::~AutoDepthRegulator(){

}


} // namespace rov
