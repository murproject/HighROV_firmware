
#include "PayloadSystem.h"
#include "RovDataStore.h"
#include "PayloadTool.h"
#include "AllPayload.h"
namespace rov {

PayloadSystem::PayloadSystem(){

		m_tools[0] = new ManipulatorPayload();
		m_tools[1] = new RotaryCamera();
}

void PayloadSystem::init() {

		for (int i = 0; i < PAYLOAD_SIZE; i++) {
			m_tools[i]->init();
		}
}

void PayloadSystem::update(const RovDataStore & store_) {

		for (int i = 0; i < PAYLOAD_SIZE; i++) {
			m_tools[i]->update(store_);
		}
}

void PayloadSystem::commit(RovDataStore & store_) {

		for (int i = 0; i < PAYLOAD_SIZE; i++) {
			m_tools[i]->commit(store_);
		}
}

PayloadSystem::~PayloadSystem(){

}


} // namespace rov
