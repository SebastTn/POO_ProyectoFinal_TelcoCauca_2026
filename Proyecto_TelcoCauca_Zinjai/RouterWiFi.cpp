#include "RouterWiFi.h"
#include <thread>
#include <chrono>

RouterWiFi::RouterWiFi(const std::string& _id, int _canales, const std::string& _ip)
    : DispositivoComunicacion(_id, "Router WiFi 6", _ip), canalesActivos(_canales) {}

void RouterWiFi::transmitir() {
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
}
