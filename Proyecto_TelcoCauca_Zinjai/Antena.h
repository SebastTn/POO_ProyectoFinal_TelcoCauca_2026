#ifndef ANTENA_H
#define ANTENA_H

#include <string>
#include "Tecnico.h"

class Antena {
private:
    int idAntena;
    double frecuenciaMHz;
    std::string tecnologia;
    Tecnico* responsableMantenimiento;

public:
    Antena(int _idAntena, double _frecuenciaMHz, const std::string& _tecnologia, Tecnico* _responsable);
    int getIdAntena() const;
    double getFrecuenciaMHz() const;
    std::string getTecnologia() const;
    Tecnico* getResponsable() const;
    void setResponsable(Tecnico* _responsable);
    void mostrarInformacion() const;
};

#endif
