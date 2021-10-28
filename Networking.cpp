#include "Networking.h"
#include "Config.h"

void Networking::init() {
    Ethernet.begin(inst().mac, inst().m_self_ip);
    inst().Udp.begin(inst().m_self_port);
}

void Networking::read_write_udp(rov::RovTelimetry &tel, rov::RovControl &ctrl) {
    uint8_t buffer[128];
    int size = inst().read(buffer, 128);
    Serial.println(size);
    if (size) {

        ctrl.fromRovControlMsg(buffer, size);
        size = tel.toRovTelemetryMsg(buffer);
        // tel.ammeter += 1;
        inst().write(buffer, size);
    }
}


Networking & Networking::inst() {
    static Networking net;
    return net;
}

int Networking::read(uint8_t * buffer, int size) {
    int packetSize = Udp.parsePacket();

    if (packetSize) {
        Serial.println(packetSize);
        Udp.read(buffer, UDP_TX_PACKET_MAX_SIZE);
        return packetSize;
    }
    return 0;
}

void Networking::write(uint8_t * buffer, int size) {
    Udp.beginPacket(m_remote_ip, m_remote_port);
    Udp.write(buffer, size);
    Udp.endPacket();
}

Networking::Networking() {
    auto &sp = config::networking::selfip;
    m_self_ip = IPAddress(sp[0], sp[1], sp[2], sp[3]);
    m_self_port = config::networking::self_port;

    auto &rp = config::networking::remoteip;
    m_remote_ip = IPAddress(rp[0], rp[1], rp[2], rp[3]);
    m_remote_port = config::networking::remote_port;
}


