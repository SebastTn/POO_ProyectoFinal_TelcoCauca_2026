#ifndef SERVIDORCENTRAL_H
#define SERVIDORCENTRAL_H

#include "SocketCompat.h"

class ServidorCentral {
private:
    int puertoTCP;
    int puertoUDP;
    TipoSocket socketTCP;
    TipoSocket socketUDP;
    int tramasRecibidas;

public:
    ServidorCentral(int _puertoTCP, int _puertoUDP);
    ~ServidorCentral();
    void iniciar();
    void aceptarClientes(int cantidad);
    void atenderCliente(TipoSocket cliente);
    void recibirTelemetriaUDP(int cantidad);
    int getTramasRecibidas() const;
};

#endif
