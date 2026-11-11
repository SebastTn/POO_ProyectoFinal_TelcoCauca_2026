#ifndef TRAMA_H
#define TRAMA_H

#include <string>
#include "ITransmisible.h"

class Trama : public ITransmisible {
private:
    std::string idNodo;
    std::string tipoSensor;
    double valor;

public:
    Trama(const std::string& _idNodo, const std::string& _tipoSensor, double _valor);
    std::string getIdNodo() const;
    std::string getTipoSensor() const;
    double getValor() const;
    std::string serializar() const override;
    std::string resumen() const;
    static Trama deserializar(const std::string& texto);
};

#endif
