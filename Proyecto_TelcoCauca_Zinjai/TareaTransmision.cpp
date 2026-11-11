#include "TareaTransmision.h"
#include "Registro.h"
#include <stdexcept>
#include <mutex>

void tareaTransmisionHilo(DispositivoComunicacion* dev, int& exitosas) {
    try {
        if (dev == nullptr) {
            throw std::invalid_argument("ERROR: Puntero nulo pasado al hilo.");
        }
        dev->transmitir();
        {
            std::lock_guard<std::mutex> lock(mtx_contador);
            ++exitosas;
        }
        registrarEventoSeguro("Transmision exitosa del dispositivo: " + dev->getId() + " (" + dev->getTipo() + ")");
    }
    catch (const std::exception& e) {
        registrarEventoSeguro(std::string("EXCEPCION EN HILO: ") + e.what());
    }
}
