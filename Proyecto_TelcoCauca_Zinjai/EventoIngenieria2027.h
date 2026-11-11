#ifndef EVENTOINGENIERIA2027_H
#define EVENTOINGENIERIA2027_H

#include <string>
#include <vector>

class EventoIngenieria2027 {
private:
    std::string nombre;
    std::string fecha;
    std::string lugar;
    std::string descripcion;

public:
    EventoIngenieria2027(const std::string& _nombre, const std::string& _fecha,
                         const std::string& _lugar, const std::string& _descripcion);
    std::string resumen() const;
};

void procesarAgendaEventos2027(const std::vector<EventoIngenieria2027>& agenda);

#endif
