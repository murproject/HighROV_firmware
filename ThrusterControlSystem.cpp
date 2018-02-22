
#include "ThrusterControlSystem.h"
#include "RovDataStore.h"
#include "Regulator.h"
#include <stdint.h>
#include <Arduino.h>

namespace rov {

ThrusterControlSystem::ThrusterControlSystem(){

}

void ThrusterControlSystem::init() {

		m_horizontal[0].init(HorizontalThrusterConfig::FRONT_LEFT_PIN);
		m_horizontal[1].init(HorizontalThrusterConfig::FRONT_RIGHT_PIN);
		m_horizontal[2].init(HorizontalThrusterConfig::BACK_LEFT_PIN);
		m_horizontal[3].init(HorizontalThrusterConfig::BACK_RIGHT_PIN);

		m_vertical[0].init(VerticalThrusterConfig::FRONT_PIN);
		m_vertical[1].init(VerticalThrusterConfig::BACK_PIN);
		delay(100);
}

void ThrusterControlSystem::update(const RovDataStore & store_) {

	if (store_.getControl().debugFlag) {
		debug_thruster(store_.getControl());
		return;
	}

	static AutoDepthRegulator adreg;
	int8_t hpwr[HORIZONTAL_THRUSTER_SIZE] = { 0 };
	int8_t vpwr[VERTICAL_THRUSTER_SIZE] = { 0 };

	if (store_.getControl().regulators & 0x1 && store_.getControl().desiredDepth != 0.0f) {
		adreg.setParams(store_.getControl().desiredDepth);
		adreg.calculate(store_, hpwr, VERTICAL_THRUSTER_SIZE);
	}
	else {
		VPilotRegulator vpr;
		vpr.calculate(store_, vpwr, VERTICAL_THRUSTER_SIZE);
	}

	HPilotRegulator hpr;
	hpr.calculate(store_, hpwr, VERTICAL_THRUSTER_SIZE);

	for (int i = 0; i < VERTICAL_THRUSTER_SIZE; i++) {
		m_vertical[i].setPower(vpwr[i]);
	}
	//Serial.println(hpwr[0]);
	for (int i = 0; i < HORIZONTAL_THRUSTER_SIZE; i++) {
		m_horizontal[i].setPower(hpwr[i]);
	}

}

void ThrusterControlSystem::commit(RovDataStore & store_) {

		store_.getTelimetry().regulatorsFeedback = store_.getControl().regulators;
}

ThrusterControlSystem::~ThrusterControlSystem(){

}

Thruster * ThrusterControlSystem::getHorizontal() {

		return m_horizontal;
}

Thruster * ThrusterControlSystem::getVertical() {

		return m_vertical;
}

void ThrusterControlSystem::debug_thruster(const RovControl & ctrl)
{
	m_horizontal[0].setPower(ctrl.thrusterPower[0]);
	m_horizontal[1].setPower(ctrl.thrusterPower[1]);
	m_horizontal[2].setPower(ctrl.thrusterPower[2]);
	m_horizontal[3].setPower(ctrl.thrusterPower[3]);

	m_vertical[0].setPower(ctrl.thrusterPower[4]);
	m_vertical[1].setPower(ctrl.thrusterPower[5]);
}


} // namespace rov
