#ifndef NODOREDINTELIGENTE_H
#define NODOREDINTELIGENTE_H

#include <iostream>
#include <string>
#include "DispositivoRed.h"
#include "SensorIoT.h"

class NodoRedInteligente : public DispositivoRed, public SensorIoT {
private:
    int cargaProcesamiento;

public:
    NodoRedInteligente(const std::string& _ip, const std::string& _mac,
                       const std::string& _tipoSensor, double _valor, int _carga);
    int getCargaProcesamiento() const;
    void verificarLectura() const;
    NodoRedInteligente operator+(const NodoRedInteligente& otro) const;
    friend std::ostream& operator<<(std::ostream& os, const NodoRedInteligente& nodo);
};

#endif
