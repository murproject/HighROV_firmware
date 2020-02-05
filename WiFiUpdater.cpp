#include "WiFiUpdater.h"
#include "Config.h"
#include <WiFiNINA.h>
#include <ArduinoOTA.h>

namespace {
    void printWifiStatus() {
        // print the SSID of the network you're attached to:
        Serial.print("SSID: ");
        Serial.println(WiFi.SSID());

        // print your WiFi shield's IP address:
        IPAddress ip = WiFi.localIP();
        Serial.print("IP Address: ");
        Serial.println(ip);

        // print the received signal strength:
        long rssi = WiFi.RSSI();
        Serial.print("signal strength (RSSI):");
        Serial.print(rssi);
        Serial.println(" dBm");
    }
}

void WiFiUpdater::init() {
    WiFi.begin(config::wifi::ssid, config::wifi::pass);

    ArduinoOTA.begin(WiFi.localIP(), "HighROV", config::wifi::pass_for_update, InternalStorage);
    ::printWifiStatus();
}

void WiFiUpdater::check_updates() {
    ArduinoOTA.poll();
}

void WiFiUpdater::set_before_callback(void(*fn)()) {
    ArduinoOTA.beforeApply(fn);
}
