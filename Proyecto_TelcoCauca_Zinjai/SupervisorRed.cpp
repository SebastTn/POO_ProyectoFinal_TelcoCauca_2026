#include "SupervisorRed.h"
#include "ExcepcionNodoRed.h"
#include "Registro.h"
#include <mutex>

void SupervisorRed::supervisarNodo(NodoRedInteligente* nodo, int& nodosSanos) {
    try {
        if (nodo == nullptr) {
            throw ExcepcionNodoRed("Puntero nulo de nodo pasado al supervisor.");
        }
        nodo->verificarLectura();
        {
            std::lock_guard<std::mutex> lock(mtx_contador);
            ++nodosSanos;
        }
        registrarEventoSeguro("Nodo supervisado correctamente: " + nodo->getDireccionIP() + " (" + nodo->getTipoSensor() + ")");
    }
    catch (const ExcepcionNodoRed& e) {
        registrarEventoSeguro("EXCEPCION NODO RED: " + std::string(e.what()));
    }
    catch (const std::exception& e) {
        registrarEventoSeguro("EXCEPCION EN HILO SUPERVISOR: " + std::string(e.what()));
    }
}
