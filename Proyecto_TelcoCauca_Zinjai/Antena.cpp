#include "Antena.h"
#include <iostream>

Antena::Antena(int _idAntena, double _frecuenciaMHz, const std::string& _tecnologia, Tecnico* _responsable)
    : idAntena(_idAntena), frecuenciaMHz(_frecuenciaMHz), tecnologia(_tecnologia),
      responsableMantenimiento(_responsable) {}

int Antena::getIdAntena() const { return idAntena; }
double Antena::getFrecuenciaMHz() const { return frecuenciaMHz; }
std::string Antena::getTecnologia() const { return tecnologia; }
Tecnico* Antena::getResponsable() const { return responsableMantenimiento; }
void Antena::setResponsable(Tecnico* _responsable) { responsableMantenimiento = _responsable; }

void Antena::mostrarInformacion() const {
    std::cout << "Antena [ID: " << idAntena << " | Frecuencia: " << frecuenciaMHz
              << " MHz | Tecnologia: " << tecnologia << " | Responsable: ";
    if (responsableMantenimiento != nullptr) {
        std::cout << responsableMantenimiento->getNombre();
    } else {
        std::cout << "Sin asignar";
    }
    std::cout << "]" << std::endl;
}
