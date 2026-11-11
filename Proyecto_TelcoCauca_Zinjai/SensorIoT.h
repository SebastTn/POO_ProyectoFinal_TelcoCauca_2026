#ifndef SENSORIOT_H
#define SENSORIOT_H

#include <string>

class SensorIoT {
private:
    std::string tipoSensor;
    double valorLectura;

public:
    SensorIoT(const std::string& _tipoSensor, double _valorLectura);
    std::string getTipoSensor() const;
    double getValorLectura() const;
    void setValorLectura(double _valorLectura);
};

#endif
