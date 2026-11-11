#include "Torre.h"
#include "Antena.h"
#include <iostream>

Torre::Torre(int _idTorre, const std::string& _ubicacion, double _alturaMetros)
    : idTorre(_idTorre), ubicacion(_ubicacion), alturaMetros(_alturaMetros) {}

Torre::~Torre() {}

void Torre::agregarAntena(Antena* _antena) {
    if (_antena != nullptr) {
        listaAntenas.push_back(_antena);
    }
}

void Torre::mostrarInformacion() const {
    std::cout << "Torre [ID: " << idTorre << " | Ubicacion: " << ubicacion
              << " | Altura: " << alturaMetros << " m | Antenas: " << listaAntenas.size() << "]" << std::endl;
    for (std::size_t i = 0; i < listaAntenas.size(); ++i) {
        std::cout << "  ";
        listaAntenas[i]->mostrarInformacion();
    }
}
