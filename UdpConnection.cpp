
#include "UdpConnection.h"
#include "RovDataTypes.h"

namespace rov {

bool UdpConnection::parsePayload(const uint8_t * payload, unsigned long size, RovControl & out) {

		RovControl::RovControlErrorCode er = out.fromRovControlMsg(payload, size);
		if (er != RovControl::RovControlErrorCode::NoError) {
			Serial.print("UDP connection error: ");
			Serial.println(RovControl::fromErrorToString(er));
			return false;
		}
		return true;
}

UdpConnection::UdpConnection() :
		m_self_ip(192, 168, 1, 5),
		m_remote_ip(192, 168, 1, 4),
		m_self_port(3020),
		m_remote_port(3010)
	{

		//m_mac[0] = 0xDE;	m_mac[1] = 0xAD;
		//m_mac[2] = 0xBE;	m_mac[3] = 0xEF;
		//m_mac[4] = 0xFE;	m_mac[5] = 0xED;
}

void UdpConnection::init() {

		Ethernet.begin(m_mac, m_self_ip);
		m_udp.begin(m_self_port);
		delay(100);
}

bool UdpConnection::existRecvMsg() {

		return m_size_last_msg = m_udp.parsePacket();
}

bool UdpConnection::recvControlFromPayload(RovControl & out) {

		RovControl control;
		uint8_t packet[sizeof(RovControl) + 2];
		if (!m_size_last_msg) return false;

		IPAddress remote = m_udp.remoteIP();

		m_udp.read((char *)packet, sizeof(RovControl) + 2);
		return parsePayload(packet, m_size_last_msg, out);
}

void UdpConnection::sendRovTelemetry(RovTelimetry & telemetry) {

		uint8_t msg[30];
		size_t msg_size = telemetry.toRovTelemetryMsg(msg);
		m_udp.beginPacket(m_remote_ip, m_remote_port);
		m_udp.write(msg, msg_size);
		m_udp.endPacket();
}


} // namespace rov
