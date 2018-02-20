
#include "RovDataStore.h"

namespace rov {

RovDataStore::RovDataStore(){

}

RovDataStore::~RovDataStore(){

}

void RovDataStore::setTelimetry(const RovTelimetry & tel_) {

		m_telimetry = tel_;
}

RovTelimetry & RovDataStore::getTelimetry() {

		return m_telimetry;
}

const RovTelimetry & RovDataStore::getTelimetry() const {

		return m_telimetry;
}

void RovDataStore::setControl(const RovControl & control_) {

		m_control = control_;
}

RovControl & RovDataStore::getControl() {

		return m_control;
}

const RovControl & RovDataStore::getControl() const {

		return m_control;
}


} // namespace rov
