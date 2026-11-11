#ifndef SWITCHFIBRA_H
#define SWITCHFIBRA_H

#include "DispositivoComunicacion.h"

class SwitchFibra : public DispositivoComunicacion {
private:
    int puertosSFP;

public:
    SwitchFibra(const std::string& _id, int _puertos, const std::string& _ip);
    void transmitir() override;
};

#endif
