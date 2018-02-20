
#include "Rov.h"

namespace rov {

Rov::Rov(){

}

Rov::~Rov(){

}

void Rov::init() {

		m_connection.init();
		m_thrusterSystem.init();
		m_sensors.init();
		m_payloads.init();
		delay(200);
}

void Rov::run() {

		if (m_connection.existRecvMsg()) {
			RovControl rc;
			if (m_connection.recvControlFromPayload(rc)) {
				m_dataStore.setControl(rc);
			}
		}

		m_sensors.sensorsUpdate();
		m_sensors.dataCommit(m_dataStore.getTelimetry());

		m_thrusterSystem.update(m_dataStore);
		m_thrusterSystem.commit(m_dataStore);

		m_payloads.update(m_dataStore);
		m_payloads.commit(m_dataStore);

		m_connection.sendRovTelemetry(m_dataStore.getTelimetry());
}



} // namespace rov
