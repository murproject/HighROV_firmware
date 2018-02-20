	#pragma once

#include "UdpConnection.h"
#include "ThrusterControlSystem.h"
#include "RovDataStore.h"
#include "SensorsContainer.h"
#include "PayloadSystem.h"

namespace rov {

	class Rov
	{
	public:
		Rov();
		~Rov();
		void init();
		void run();
	private:
		RovDataStore m_dataStore;
		UdpConnection m_connection;
		ThrusterControlSystem m_thrusterSystem;
		SensorsContainer m_sensors;
		PayloadSystem m_payloads;
	};

}