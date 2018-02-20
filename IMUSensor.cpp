
#include "IMUSensor.h"
#include "RovDataTypes.h"
#include <Arduino.h>

namespace rov {

	enum status
	{
		kStatus_Idle,
		kStatus_Cmd,
		kStatus_LenLow,
		kStatus_LenHigh,
		kStatus_CRCLow,
		kStatus_CRCHigh,
		kStatus_Data,
	};

	typedef enum
	{
		kItemKeyStatus = 0x80,   /* key status           size: 4 */
		kItemID = 0x90,   /* user programed ID    size: 1 */
		kItemUID = 0x91,   /* Unique ID            size: 4 */
		kItemIPAdress = 0x92,   /* ip address           size: 4 */
		kItemAccRaw = 0xA0,   /* raw acc              size: 3x2 */
		kItemAccRawFiltered = 0xA1,
		kItemAccLinear = 0xA2,
		kItemAccCalibrated = 0xA3,
		kItemGyoRaw = 0xB0,   /* raw gyro             size: 3x2 */
		kItemGyoRawFiltered = 0xB1,
		kItemGyoCalibrated = 0xB3,
		kItemMagRaw = 0xC0,   /* raw mag              size: 3x2 */
		kItemMagRawFiltered = 0xC1,
		kItemMagCalibrated = 0xC3,
		kItemAtdE = 0xD0,   /* eular angle          size:3x2 */
		kItemAtdQ = 0xD1,   /* att q,               size:4x4 */
		kItemTemp = 0xE0,
		kItemPressure = 0xF0,   /* pressure             size:1x4 */
		kItemEnd = 0xFF,
	}ItemID_t;


	static void crc16_update(uint16_t *currectCrc, const uint8_t *src, uint32_t lengthInBytes)
	{
		uint32_t crc = *currectCrc;
		uint32_t j;
		for (j = 0; j < lengthInBytes; ++j)
		{
			uint32_t i;
			uint32_t byte = src[j];
			crc ^= byte << 8;
			for (i = 0; i < 8; ++i)
			{
				uint32_t temp = crc << 1;
				if (crc & 0x8000)
				{
					temp ^= 0x1021;
				}
				crc = temp;
			}
		}
		*currectCrc = crc;
	}


	uint32_t IMUSensor::packetDecode(uint8_t c)
	{
		static uint16_t CRCReceived = 0; /* CRC value received from a frame */
		static uint16_t CRCCalculated = 0;  /* CRC value caluated from a frame */
		static uint8_t status = kStatus_Idle; /* state machine */
		static uint8_t crc_header[4] = { 0x5A, 0xA5, 0x00, 0x00 };

		switch (status)
		{
		case kStatus_Idle:
			if (c == 0x5A)
				status = kStatus_Cmd;
			break;
		case kStatus_Cmd:
			if (c == 0xA5)
				status = kStatus_LenLow;
			break;
		case kStatus_LenLow:
			RxPkt.payload_len = c;
			crc_header[2] = c;
			status = kStatus_LenHigh;
			break;
		case kStatus_LenHigh:
			RxPkt.payload_len |= (c << 8);
			crc_header[3] = c;
			status = kStatus_CRCLow;
			break;
		case kStatus_CRCLow:
			CRCReceived = c;
			status = kStatus_CRCHigh;
			break;
		case kStatus_CRCHigh:
			CRCReceived |= (c << 8);
			RxPkt.ofs = 0;
			CRCCalculated = 0;
			status = kStatus_Data;
			break;
		case kStatus_Data:
			RxPkt.buf[RxPkt.ofs++] = c;
			if (RxPkt.ofs >= RxPkt.payload_len)
			{
				/* calculate CRC */
				crc16_update(&CRCCalculated, crc_header, 4);
				crc16_update(&CRCCalculated, RxPkt.buf, RxPkt.ofs);

				/* CRC match */
				if (CRCCalculated == CRCReceived)
				{
				
					updateEuler(&RxPkt);
				}
				status = kStatus_Idle;
			}
			break;
		default:
			status = kStatus_Idle;
			break;
		}
	}
	void IMUSensor::updateEuler(Packet_t * pkt)
	{
		if (pkt->buf[0] == kItemID) /* user ID */
		{
			ID = pkt->buf[1];
		}
		if (pkt->buf[2] == kItemAccRaw)  /* Acc raw value */
		{
			memcpy(AccRaw, (uint8_t *)pkt->buf[3], 6);
		}

		if (pkt->buf[9] == kItemGyoRaw)  /* gyro raw value */
		{
			memcpy(GyoRaw, (uint8_t *)pkt->buf[10], 6);
		}

		if (pkt->buf[16] == kItemMagRaw)  /* mag raw value */
		{
			memcpy(MagRaw, (uint8_t *)pkt->buf[17], 6);
		}
		if (pkt->buf[23] == kItemAtdE)  /* atd E */
		{
			float val = ((float)(int16_t)(pkt->buf[24] + (pkt->buf[25] << 8))) / 100;
			if (!isnan(val)) {
				Eular[0] = ((float)(int16_t)(pkt->buf[24] + (pkt->buf[25] << 8))) / 100;
			}
			val = ((float)(int16_t)(pkt->buf[26] + (pkt->buf[27] << 8))) / 100;
			if (!isnan(val)) {
				Eular[1] = ((float)(int16_t)(pkt->buf[26] + (pkt->buf[27] << 8))) / 100;
			}
			val = ((float)(int16_t)(pkt->buf[28] + (pkt->buf[29] << 8))) / 10;
			if (!isnan(val)) {
				Eular[2] = ((float)(int16_t)(pkt->buf[28] + (pkt->buf[29] << 8))) / 10;
			}
			m_isUpdated = true;
		}

	}

	IMUSensor::IMUSensor()
	{
	}
	void IMUSensor::init()
	{
		Serial3.begin(115200);
	}
	void IMUSensor::update()
	{
		if (Serial3.available()) {
			delay(3);
			while (Serial3.available())
			{
				char ch = Serial3.read();
				packetDecode(ch);
			}
		}
	}
	void IMUSensor::commit(RovTelimetry & tel_)
	{
		if (m_isUpdated) {
			tel_.yaw = getYaw();
			tel_.pitch = getPitch();
			tel_.roll = getRoll();
			m_isUpdated = false;
		}
	}
	float IMUSensor::getPitch() const
	{
		return Eular[0];
	}
	float IMUSensor::getRoll() const
	{
		return Eular[1];
	}
	float IMUSensor::getYaw() const
	{
		return Eular[2];
	}
	void IMUSensor::update_int()
	{

		
	}
} // namespace rov
