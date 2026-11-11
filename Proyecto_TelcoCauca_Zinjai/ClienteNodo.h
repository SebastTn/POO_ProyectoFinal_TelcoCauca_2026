#ifndef CLIENTENODO_H
#define CLIENTENODO_H

#include <string>

class ClienteNodo {
private:
    std::string idNodo;
    std::string tipoSensor;
    double valor;
    int puertoTCP;
    int puertoUDP;
    bool tramaCorrupta;

public:
    ClienteNodo(const std::string& _idNodo, const std::string& _tipoSensor, double _valor,
                int _puertoTCP, int _puertoUDP, bool _tramaCorrupta);
    void ejecutar(int& tramasEnviadas);
};

#endif
