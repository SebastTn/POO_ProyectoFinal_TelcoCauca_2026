#ifndef ROUTERWIFI_H
#define ROUTERWIFI_H

#include "DispositivoComunicacion.h"

class RouterWiFi : public DispositivoComunicacion {
private:
    int canalesActivos;

public:
    RouterWiFi(const std::string& _id, int _canales, const std::string& _ip);
    void transmitir() override;
};

#endif
