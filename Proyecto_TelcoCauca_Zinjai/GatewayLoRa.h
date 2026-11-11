#ifndef GATEWAYLORA_H
#define GATEWAYLORA_H

#include "DispositivoComunicacion.h"

class GatewayLoRa : public DispositivoComunicacion {
private:
    float frecuenciaMHz;

public:
    GatewayLoRa(const std::string& _id, float _freq, const std::string& _ip);
    void transmitir() override;
};

#endif
