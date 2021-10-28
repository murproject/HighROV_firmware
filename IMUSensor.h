// IMUSensor.h

#ifndef _IMUSENSOR_h
#define _IMUSENSOR_h

#include "Arduino.h"

namespace Imu {
	class IMUSensor {
	private:
#define MAX_PACKET_LEN          (128)

		typedef struct
		{
			uint32_t ofs;
			uint8_t buf[MAX_PACKET_LEN] = {0};
			uint16_t payload_len;
			uint16_t len;
		}Packet_t;

		Packet_t RxPkt;
		uint8_t ID;
		int16_t AccRaw[3] = {0};
		int16_t GyoRaw[3] = {0};
		int16_t MagRaw[3] = {0};
		float Eular[3] = {0.0};
		int32_t Pressure;

		uint32_t packetDecode(uint8_t c);
		void updateEuler(Packet_t *pkt);
		bool m_isUpdated;

	public:
		IMUSensor();
		void init();
		void update();
		// void commit(RovTelimetry & tel_);
		float getPitch() const;
		float getRoll() const;
		float getYaw() const;
		void update_int();
	};

}
#endif

