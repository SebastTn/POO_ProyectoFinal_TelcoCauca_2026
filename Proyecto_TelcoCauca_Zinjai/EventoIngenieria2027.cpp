#include "EventoIngenieria2027.h"
#include "Registro.h"
#include <thread>
#include <chrono>
#include <stdexcept>

EventoIngenieria2027::EventoIngenieria2027(const std::string& _nombre, const std::string& _fecha,
                                             const std::string& _lugar, const std::string& _descripcion)
    : nombre(_nombre), fecha(_fecha), lugar(_lugar), descripcion(_descripcion) {}

std::string EventoIngenieria2027::resumen() const {
    return nombre + " | " + fecha + " | " + lugar + " | " + descripcion;
}

void procesarAgendaEventos2027(const std::vector<EventoIngenieria2027>& agenda) {
    try {
        if (agenda.empty()) {
            throw std::runtime_error("La agenda de eventos 2027 esta vacia.");
        }
        for (std::size_t i = 0; i < agenda.size(); ++i) {
            registrarEventoSeguro("EVENTO 2027 -> " + agenda[i].resumen());
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    catch (const std::exception& e) {
        registrarEventoSeguro(std::string("EXCEPCION EN AGENDA: ") + e.what());
    }
}
