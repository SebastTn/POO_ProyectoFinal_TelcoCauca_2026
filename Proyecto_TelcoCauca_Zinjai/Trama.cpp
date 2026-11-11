#include "Trama.h"
#include "ExcepcionNodoRed.h"
#include <sstream>

Trama::Trama(const std::string& _idNodo, const std::string& _tipoSensor, double _valor)
    : idNodo(_idNodo), tipoSensor(_tipoSensor), valor(_valor) {}

std::string Trama::getIdNodo() const { return idNodo; }
std::string Trama::getTipoSensor() const { return tipoSensor; }
double Trama::getValor() const { return valor; }

std::string Trama::serializar() const {
    std::ostringstream salida;
    salida << idNodo << "|" << tipoSensor << "|" << valor;
    return salida.str();
}

std::string Trama::resumen() const {
    return idNodo + " | " + tipoSensor + " | " + std::to_string(valor);
}

Trama Trama::deserializar(const std::string& texto) {
    std::stringstream ss(texto);
    std::string id, tipo, valStr;
    if (std::getline(ss, id, '|') && std::getline(ss, tipo, '|') && std::getline(ss, valStr)) {
        try {
            double v = std::stod(valStr);
            return Trama(id, tipo, v);
        } catch (...) {
            throw ExcepcionNodoRed("Valor numérico inválido en trama: " + valStr);
        }
    }
    throw ExcepcionNodoRed("Trama invalida, formato incorrecto: " + texto);
}
