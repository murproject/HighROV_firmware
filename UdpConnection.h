#ifndef ROV_UDPCONNECTION_H
#define ROV_UDPCONNECTION_H


#include "RovDataStore.h"
#include <SPI.h>
#include <Ethernet.h>

namespace rov {

class UdpConnection {
  private:
    uint8_t m_mac[6]=  {
			0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
		};

    IPAddress m_self_ip;

    IPAddress m_remote_ip;

    unsigned int m_self_port;

    unsigned int m_remote_port;

    EthernetUDP m_udp;

    unsigned long m_size_last_msg;

    bool parsePayload(const uint8_t * payload, unsigned long size, RovControl & out);


  public:
    UdpConnection();

    void init();

    bool existRecvMsg();

    bool recvControlFromPayload(RovControl & out);

    void sendRovTelemetry(RovTelimetry & telemetry);

};

} // namespace rov
#endif
