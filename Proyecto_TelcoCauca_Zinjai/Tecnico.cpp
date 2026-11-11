#include "Tecnico.h"
#include <iostream>

Tecnico::Tecnico(int _idTecnico, const std::string& _nombre, const std::string& _especialidad)
    : idTecnico(_idTecnico), nombre(_nombre), especialidad(_especialidad) {}

int Tecnico::getIdTecnico() const { return idTecnico; }
std::string Tecnico::getNombre() const { return nombre; }
std::string Tecnico::getEspecialidad() const { return especialidad; }
void Tecnico::setNombre(const std::string& _nombre) { nombre = _nombre; }
void Tecnico::setEspecialidad(const std::string& _especialidad) { especialidad = _especialidad; }

void Tecnico::mostrarInformacion() const {
    std::cout << "Tecnico [ID: " << idTecnico << " | Nombre: " << nombre
              << " | Especialidad: " << especialidad << "]" << std::endl;
}
