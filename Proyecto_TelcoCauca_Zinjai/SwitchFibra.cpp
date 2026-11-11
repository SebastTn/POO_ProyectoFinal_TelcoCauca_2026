#include "SwitchFibra.h"
#include <thread>
#include <chrono>

SwitchFibra::SwitchFibra(const std::string& _id, int _puertos, const std::string& _ip)
    : DispositivoComunicacion(_id, "Switch Fibra Optica", _ip), puertosSFP(_puertos) {}

void SwitchFibra::transmitir() {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
}
