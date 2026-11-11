#include "SensorIoT.h"

SensorIoT::SensorIoT(const std::string& _tipoSensor, double _valorLectura)
    : tipoSensor(_tipoSensor), valorLectura(_valorLectura) {}

std::string SensorIoT::getTipoSensor() const { return tipoSensor; }
double SensorIoT::getValorLectura() const { return valorLectura; }
void SensorIoT::setValorLectura(double _valorLectura) { valorLectura = _valorLectura; }
